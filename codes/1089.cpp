#include<iostream>
using namespace std;
int main (){
	int n,t;
	cin>>n;
	if(n<0){
		cout<<'-';
		n*=-1;
	}
	while(n%10==0) n/=10;
	while(n){
		t=n%10;
		n/=10;
		cout<<t; 
	}
	
	return 0;
}
