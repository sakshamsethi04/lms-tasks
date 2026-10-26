#include <iostream>
using namespace std;

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

int main(){
    int leftcommand=300;
    int rightcommand=-269;
    cout<<clampValue(leftcommand,255)<<endl;
    cout<<clampValue(rightcommand,255);
    
}