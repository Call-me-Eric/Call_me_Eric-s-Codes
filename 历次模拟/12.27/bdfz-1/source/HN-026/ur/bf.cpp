#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const double PI=acos(-1);
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=(x<<1)+(x<<3)+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
int n,k;
bool ava[100];
int main(){
	for(int n=1;n<=30;++n){
		double uni=(PI+PI)/n;
		for(int i=0;i<=n;++i) ava[i]=0;
		for(int s=0;s<(1<<n);++s){
			double x=0,y=0;
			for(int i=0;i<n;++i)
				if(s>>i&1){
					x+=cos(uni*i);
					y+=sin(uni*i);
				}
			if(abs(x)<1e-10&&abs(y)<1e-10)
				ava[__builtin_popcount(s)]=1;
		}
		for(int i=0;i<=n;++i) if(ava[i]) printf("%d ",i);
		putchar('\n');
	}
	return 0;
}
