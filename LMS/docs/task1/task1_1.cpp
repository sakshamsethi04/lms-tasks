#include <iostream>
using namespace std;
int positions[5]={-2,-1,0,1,2};
double calc_centroid(double arr []){
    
double numr=0;
double denom=0;
for(int i=0; i<5; i++){
    double temp=arr[i]*positions[i];
    numr+=temp;
    denom+=arr[i];

}
if(denom==0) return 0;
else return numr/denom;
}


int main(){

    double readings[5]={3,5,10,5,2};
    cout<<calc_centroid(readings);
}