
int ir1=34;
int ir2=35;
int ir3=32;
int ir4=33;
int ir5=25;
int enA=14;
int enB=13;
int in1=27;
int in2=26;
int in3=12;
int in4=11;
int weights[5]={-2,-1,0,1,2};
int sensors[5]={ir1,ir2,ir3,ir4,ir5};
float centroid;
float error;
float basespeed=150;
float P;
float integral=0.0;
float I;
float Ki=0.5;
float Kd=2.0;
float D;
float U;
float Kp=20;
int sensorMin[5] = {4095,4095,4095,4095,4095};
int sensorMax[5] = {0,0,0,0,0};
float lastKnownPosition = 0;
bool hasSeenLine = false;
float totalStrength = 0;
float errorlater=0;
unsigned long previousTimee=0;

class control{
    public:

        void initiallize(){
            pinMode(ir1,INPUT);
            pinMode(ir2,INPUT);
            pinMode(ir3,INPUT);
            pinMode(ir4,INPUT);
            pinMode(ir5,INPUT);
            pinMode(enA,OUTPUT);
            pinMode(enB,OUTPUT);
            pinMode(in1,OUTPUT);
            pinMode(in2,OUTPUT);
            pinMode(in3,OUTPUT);
            pinMode(in4,OUTPUT);
        }

        float calculate_centroid(){
            float readings[5];
            for(int i=0; i<5; i++){
                readings[i] = analogRead(sensors[i]);
            }

            float numr=0;
            float denom=0;
            totalStrength=0;

            for(int i=0; i<5; i++){
                if(sensorMax[i] - sensorMin[i] < 50){
                    continue;
                }

                float strength = (readings[i] - sensorMin[i]) /
                                 (float)(sensorMax[i] - sensorMin[i]);

                strength = constrain(strength, 0.0, 1.0);
                numr += strength * weights[i];
                denom += strength;
            }

            totalStrength=denom;

            if(denom < 0.05){
                return 0;
            }

            return numr / denom;
        }

        float calculate_proportional(float error,float kp){
            return kp*error;
        }

        float calculate_integral(float error,float dt) {
            integral += error * dt;
            integral = constrain(integral, -10, 10);
            return Ki * integral;
        }

        float calculate_derivative(float errornow,float errorlater,float dt){
            if(dt<=0){
                return 0;
            }
            float D=Kd*(errornow-errorlater)/dt;
            return D;
        }

        void setmotor(int speed, int en, int a , int b){
            speed=constrain(speed,-255,255);
            if(speed>0){
                digitalWrite(a,HIGH);
                digitalWrite(b,LOW);
                analogWrite(en,abs(speed));
            }
            if(speed<0){
                digitalWrite(a,LOW);
                digitalWrite(b,HIGH);
                analogWrite(en,abs(speed));
            }
            if(speed==0){
                digitalWrite(a,LOW);
                digitalWrite(b,LOW);
                analogWrite(en,0);
            }
        }

        int clampValue(int command,int maxmagnitude){
            if(command>maxmagnitude){
                command=maxmagnitude;
                return command;
            }
            else if(command<-maxmagnitude){
                command=-maxmagnitude;
                return command;
            }
            else return command;
        }

        void calibrate() {
            unsigned long start = millis();
            while (millis() - start < 5000) {
                for (int i = 0; i < 5; i++) {
                    int reading = analogRead(sensors[i]);
                    if (reading < sensorMin[i]) {
                        sensorMin[i] = reading;
                    }
                    if (reading > sensorMax[i]) {
                        sensorMax[i] = reading;
                    }
                }
                delay(5);
            }
        }
};

control obj1;

void setup(){
    Serial.begin(115200);
    obj1.initiallize();
    obj1.calibrate();
    previousTimee=micros();

    for(int i=0; i<5; i++){
        Serial.print("Sensor ");
        Serial.print(i+1);
        Serial.print(" min: ");
        Serial.print(sensorMin[i]);
        Serial.print(" max: ");
        Serial.println(sensorMax[i]);
    }
}

void loop(){
    unsigned long now=micros();
    float dt=(now-previousTimee)/1000000.0;
    previousTimee=now;

    centroid=obj1.calculate_centroid();

    if (totalStrength >= 0.1) {
        if(abs(centroid)>0.05 || !hasSeenLine){
            lastKnownPosition = centroid;
        }
        hasSeenLine = true;
    }
    else {
        if (!hasSeenLine || abs(lastKnownPosition)<=0.05) {
            obj1.setmotor(0, enA, in1, in2);
            obj1.setmotor(0, enB, in3, in4);
            Serial.println("Line lost: stopped");
        }
        else if (lastKnownPosition < 0) {
            obj1.setmotor(-100, enA, in1, in2);
            obj1.setmotor(100, enB, in3, in4);
            Serial.println("Line lost: rotating left");
        }
        else {
            obj1.setmotor(100, enA, in1, in2);
            obj1.setmotor(-100, enB, in3, in4);
            Serial.println("Line lost: rotating right");
        }

        integral=0;
        errorlater=0;
        return;
    }

    error=0-centroid;
    P=obj1.calculate_proportional(error,Kp);
    I=obj1.calculate_integral(error,dt);
    D=obj1.calculate_derivative(error,errorlater,dt);
    errorlater=error;
    U=P+I+D;

    int leftspeed=obj1.clampValue(basespeed-U,255);
    int rightspeed=obj1.clampValue(basespeed+U,255);

    Serial.println("cntroid:");
    Serial.print(centroid);
    Serial.println("strength:");
    Serial.print(totalStrength);
    Serial.println("error");
    Serial.print(error);
    Serial.println("p:");
    Serial.print(P);
    Serial.println("i:");
    Serial.print(I);
    Serial.println("d:");
    Serial.print(D);
    Serial.println("left:");
    Serial.print(leftspeed);
    Serial.println("right:");
    Serial.println(rightspeed);

    obj1.setmotor(leftspeed,enA,in1,in2);
    obj1.setmotor(rightspeed,enB,in3,in4);
}