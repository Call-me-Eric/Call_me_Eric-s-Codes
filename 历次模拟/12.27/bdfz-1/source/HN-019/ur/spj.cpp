#include<iostream>
#include<cstdio>
#include<cmath>
#include<cassert>
#define N 1000000
#define eps 1e-7
using namespace std;
int gcd(int x,int y)
{
	if (!y) return x;
	return gcd(y,x%y);
}
const double Pi=asin(1)*2;
int n,w[N+1];
double s1[N+1],s2[N+1],res1,res2;
bool used[N+1];
int main()
{
	cin>>n;
	freopen("ur.out","r",stdin);
	char c;
	for (int i=0;i<n;++i) s1[i]=sin(2*Pi*i/n),s2[i]=cos(2*Pi*i/n);
	for (int i=0;i<n;++i)
	{
		cin>>c;
		if (c=='1') res1+=s1[i],res2+=s2[i];
	}
	assert(abs(res1)<eps&&abs(res2)<eps);
	return 0;
}
