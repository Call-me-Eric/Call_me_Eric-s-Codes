#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+5;
int head[maxn];
int to[maxn];
int nxt[maxn];
int cd[maxn];
int rd[maxn];
int cntt[maxn];
const int mod=1e9+7;
int cnt;
int res;
int n,m;
int vis[maxn];
void add(int x,int y){
	to[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
signed main(){
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
		cd[x]++;
		cd[y]++;
		if(cd[x]>=2){
			for(int i=2;i<cd[x];i++){
				cntt[i]+=(cd[x]-(i-1));
			}
			cntt[cd[x]]++;
		}
		if(cd[y]>=2){
			for(int i=2;i<cd[y];i++){
				cntt[i]+=(cd[y]-(i-1));
			}
			cntt[cd[y]]++;
		}
	}
	int ans=cntt[2];
	for(int i=3;i<=n-1;i++){
		ans=(ans^cntt[i]%mod);
	}
	cout<<ans;
	return 0;
}

