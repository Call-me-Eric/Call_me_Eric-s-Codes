#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int head[maxn];
int to[maxn];
int nxt[maxn];
int cnt;
const int mod=998244353;
int n,k;
int col[maxn];
void add(int x,int y){
	to[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
//unordered_map<int,int>mp;
//int ans=0;
//void dfs(int x,int f,int now){
//	if(head[x]==1) ans++;
//	for(int i=head[x];i;i=nxt[i]){
//		int v=to[i];
//		if(v==f) continue;
//		
//	}
//	for(int i=1;i<=k;i++){
//		
//	}
//}
vector<int>now;
int ans=0;
bool check(){
	for(int i=1;i<=n;i++){
		if(now[i-1]!=col[i]&&col[i]!=0) return 0;
		for(int j=head[i];j;j=nxt[j]){
			int v=to[j];
			if(now[v-1]==now[i-1]){
				return 0; 
			} 
		}
	}
	return 1;
}
void dfs(int x){
	if(x>n){
		if(check()) ans++;
		return;
	}
	for(int i=1;i<=k;i++){
		now.push_back(i);
		dfs(x+1);
		now.pop_back();
	}
}
signed main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>col[i];
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}	
	dfs(1);
	cout<<ans;
	return 0;
}

