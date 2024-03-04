#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e6+5;
int n;
int val[maxn];
int f[maxn][3];
int cnt;
int head[maxn];
int to[maxn];
int nxt[maxn];
void add(int x,int y){
	to[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
void dfs(int x,int fa){
	int minn=0x7fffffff;
	int cnt=0;
	f[x][0]=val[x];
	f[x][1]=0;
	for(int i=head[x];i;i=nxt[i]){
		if(to[i]==fa) continue;
		dfs(to[i],x);
		cnt++;
		f[x][2]+=min(f[to[i]][0],f[to[i]][2]);
		f[x][1]+=min(f[to[i]][0],f[to[i]][2]);
		f[x][0]+=min(f[to[i]][0],min(f[to[i]][1],f[to[i]][2]));
	}
	if(!cnt) f[x][0]=val[x],f[x][1]=0,f[x][2]=minn;
//	f[x][2]=minn;
//	cout<<x<<" "<<cnt<<" "<<f[x][0]<<" "<<f[x][1]<<" "<<f[x][2]<<'\n';
}
signed main(){
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
//	memset(f,0x3f3f3f,sizeof(f));
	for(int i=1;i<=n;i++){
		cin>>val[i];
	}
	for(int i=1;i<n;i++){
		 int x,y;
		 cin>>x>>y;
		 add(x,y);
		 add(y,x);
	}
	dfs(1,0);
	cout<<min(min(f[1][0],f[1][1]),f[1][2]);
	return 0;
}

