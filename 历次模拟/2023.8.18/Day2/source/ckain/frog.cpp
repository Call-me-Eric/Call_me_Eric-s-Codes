#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define int long long
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

const int N=50005;

int n, a[N][5], f[N], F[N];

signed main(){
	freopen("frog.in", "r", stdin);
	freopen("frog.out", "w", stdout);
	n=rd();
	for(int i=1; i<=n; i++){
		for(int j=0; j<5; j++) a[i][j]=rd();
		f[i]=rd();
	}
	for(int i=1; i<=n; i++){
		F[i]=f[i];
		int mx=0;
		for(int j=i-1; j; j--){
			//printf("* %lld %lld\n", i, j);
			bool flag=1;
			for(int k=0; k<5; k++){
				//printf("%lld %lld\n", a[i][k], a[j][k]);
				if(a[j][k]>a[i][k]){
					flag=0;
					break;
				}
			}
			if(flag==1) mx=max(mx, F[j]);
		}
		F[i]+=mx;
	}
	for(int i=1; i<=n; i++) printf("%lld\n", F[i]);
	return 0;
}
