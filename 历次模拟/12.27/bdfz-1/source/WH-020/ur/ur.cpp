#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,K;
bool s[N];
inline void Max(int &a,int &b,int c,int d){
	if(a<c)a=c,b=d;
}
int main(){
	freopen("ur.in","r",stdin);freopen("ur.out","w",stdout);
	scanf("%d%d",&n,&K);
	int ans=0,id=-1;
	for(int i=1;i*i<=n;i++)if(n%i==0){
		if(i>1)Max(ans,id,K/i*i,i);
		if(i<n)Max(ans,id,K/(n/i)*(n/i),n/i);
	}
	if(id==-1){
		for(int i=1;i<=n;i++)putchar('0');return 0;
	}
	for(int i=1;i<=n;i+=n/id){
		for(int j=i;j<=i+K/id-1;j++)s[j]=1;
	}
	for(int i=1;i<=n;i++)putchar(s[i]+'0');puts("");
}

/*

g++ -o ur.exe ur.cpp -O2 -lm -std=c++14 -Wall -Wextra
./ur.exe<ur1.in

*/