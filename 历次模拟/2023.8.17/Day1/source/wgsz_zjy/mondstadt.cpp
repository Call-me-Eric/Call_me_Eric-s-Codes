#include<bits/stdc++.h>
#define F(i0,i1,i2) for(int i0=i1;i0<=i2;++i0)
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
using namespace std;
inline int rd(){
	int f=0,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return f?-x:x;
}
const int N=5e3+7,mod=1e9+7;
int Pow(int a,int b){int ans=1;for(;b;b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;return ans;}
int d[N],n,m;
int c[N][N];
void prew(){
	c[0][0]=1;
	F(i,1,n-1){
		for(int j=0;j<=i;++j){
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
		}
	}
}
int ans[N];
signed main(){
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
	n=rd(),m=rd();
	F(i,1,m){
		int x=rd(),y=rd();
		d[x]++;
		d[y]++;
	}
	prew();
	F(i,1,n){
		F(j,2,d[i]){
			ans[j]+=c[d[i]][j];
		}
	}
	int ant=0;
	F(i,2,n-1)ant^=ans[i];
	cout<<ant<<'\n';
	return 0;
}

