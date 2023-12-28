#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(1);i>=(b);--i)
using namespace std;
const int Maxn=1e6;

inline void Divide(int x)
{
	printf("%d: ",x);
	for(int i=2,k=x;i<=k;i++) if(k%i==0)
		while(k%i==0) printf("%d ",i),k/=i;	
	printf("\n");
}

int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);	
	
	Divide(36079),Divide(35207);
	return 0;
} 
