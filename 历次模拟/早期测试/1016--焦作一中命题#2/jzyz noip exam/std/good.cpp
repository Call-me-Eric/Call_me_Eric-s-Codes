#include<bits/stdc++.h>
#define ll long long 
#define uit unsigned int 
using namespace std;
const int N=4010;
int n,m,A[N],stk[N],top=0,ls[N],rs[N],sz[N];ll lw[N],rw[N],f[N][N];
void DP(int x){
	sz[x]=1;
	if(ls[x]){
		DP(ls[x]);
		for(int i=min(m,sz[x]);i>=0;i--){
			for(int j=min(m,min(sz[ls[x]],m-i));j>=0;j--){
				f[x][i+j]=max(f[x][i+j],f[x][i]+f[ls[x]][j]+1ll*j*(m-j)*lw[x]);
			}
		}
		sz[x]+=sz[ls[x]];
	}
	if(rs[x]){
		DP(rs[x]);
		for(int i=min(m,sz[x]);i>=0;i--){
			for(int j=min(m,min(sz[rs[x]],m-i));j>=0;j--){
				f[x][i+j]=max(f[x][i+j],f[x][i]+f[rs[x]][j]+1ll*j*(m-j)*rw[x]);
			}
		}
		sz[x]+=sz[rs[x]];
	}
}
int main(){
	freopen("good.in","r",stdin);
	freopen("good.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int i=1;i<=n;i++){
		int now=top;
		while(now&&A[i]<A[stk[now]]) --now;
		if(now){
			rs[stk[now]]=i;
			rw[stk[now]]=A[i]-A[stk[now]];
		}
		if(now<top){
			ls[i]=stk[now+1];
			lw[i]=A[stk[now+1]]-A[i];
		}
		stk[++now]=i;top=now;
	}
	DP(stk[1]);
	printf("%lld\n",f[stk[1]][m]);
	return 0;
}
