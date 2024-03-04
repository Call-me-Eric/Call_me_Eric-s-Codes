#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
const int N=2e6+5;
const ll inf=0x3f3f3f3f3f3f3f3f;
inl int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int n,m,cnt,vis[N],tot;
ll ans=inf;
struct node{
	int v,id;
	friend bool operator<(node a,node b){return a.v<b.v;}
}a[N];
inl void add(int x){
	if(!vis[a[x].id])tot++;
	vis[a[x].id]++;
}
signed main(){
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		m=read();
		for(int j=1;j<=m;j++)a[++cnt].v=read(),a[cnt].id=i;
	}
	sort(a+1,a+cnt+1);
	int l=1,r=0;
	while(r<cnt){
		while(tot<n&&r<cnt)add(++r);
		if(tot!=n&&r==cnt)break;
		while(vis[a[l].id]!=1)vis[a[l++].id]--;
		ans=min(ans,1ll*a[r].v-a[l].v);
		vis[a[l++].id]--;tot--;
	}
	printf("%lld\n",ans);
	return 0;
}

