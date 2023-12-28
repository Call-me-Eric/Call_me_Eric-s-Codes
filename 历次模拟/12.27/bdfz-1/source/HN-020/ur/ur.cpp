//Code by juju527.
#include<bits/stdc++.h>
typedef long long ll;
typedef double db;
#define pii pair<int,int>
#define fi first
#define se second
#define vec vector<int>
#define eb emplace_back
using namespace std;
const int maxn=1e6+5;
const db eps=1e-9,pai=acos(-1.0);
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
bool bj[maxn];
int len,pr[maxn],minp[maxn];
void init(int n){
	for(int i=2;i<=n;i++){
		if(!bj[i])pr[++len]=i,minp[i]=i;
		for(int j=1;j<=len&&1ll*i*pr[j]<=n;j++){
			bj[i*pr[j]]=1;minp[i*pr[j]]=pr[j];
			if(i%pr[j]==0)break;
		}
	}
	return ;
}
bool ans[maxn];
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	int n,k,N,res=0;
	n=read();k=read();
	if(n<=20){
		int S=(1<<n)-1,res=0,st=0;
		for(int s=0;s<=S;s++){
			if(__builtin_popcount(s)>k)continue;
			db x=0,y=0;
			for(int i=0;i<n;i++)if((s>>i)&1)x+=cos(2*pai*i/n),y+=sin(2*pai*i/n);
			if(fabs(x)<eps&&fabs(y)<eps)
				if(__builtin_popcount(s)>res)
					res=__builtin_popcount(s),st=s;
		}
		for(int i=0;i<n;i++)if((st>>i)&1)putchar('1');else putchar('0');
		puts("");
		return 0;
	}
	init(n);N=n;
	while(n>1){
		int v=k/minp[n]*minp[n];
		if(v>res){
			res=v;
			for(int i=0;i<N;i++)ans[i]=0;
			for(int i=0;i<k/minp[n];i++)
				for(int j=i;j<N;j+=N/minp[n])
					ans[j]=1;
		}
		n/=minp[n];
	}
	for(int i=0;i<N;i++)printf("%d",ans[i]);
	puts("");
	return 0;
}
