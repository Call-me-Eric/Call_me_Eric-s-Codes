#include<bits/stdc++.h>
#define int long long
using namespace std;
double cal(double a,double b,double c,double d){
	return 1.0*(a-b)*(c-d);
}
double call(double a,double b,double c,double d,double e,double f,double g,double h){
	return cal(1.0*a*b,1.0*c*d,1.0*e*f,1.0*h*g);
}

signed main(){
	freopen("sumeru.in","r",stdin);
	freopen("sumeru.out","w",stdout);
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		double a11,a12,a13,a21,a22,a23,a31,a32,a33,a41,a42,a43,new1,new2,new3,new4;
		cin>>a11>>a12>>a13>>a21>>a22>>a23>>a31>>a32>>a33>>a41>>a42>>a43;
		double ans3=1.0*(call(a13,a42,a12,a43,a21,a12,a11,a22)-call(a12,a41,a11,a42,a13,a22,a23,a12))/(call(a13,a32,a12,a33,a21,a12,a11,a22)-call(a31,a12,a11,a32,a21,a22,a23,a12));	
		double ans2=1.0*((1.0*a13*a42-1.0*a12*a43)-(1.0*a13*a32-1.0*a12*a33))/(1.0*a13*a22-a23*a12);
		double ans1=1.0*(a41-a31*ans2-a21*ans2)/a11;
		if(ans1>0.0&&ans2>0.0&&ans3>0.0){
			cout<<"YES"<<'\n';
		}
		else{
			cout<<"NO"<<'\n';
		}
	}
	return 0;
}

