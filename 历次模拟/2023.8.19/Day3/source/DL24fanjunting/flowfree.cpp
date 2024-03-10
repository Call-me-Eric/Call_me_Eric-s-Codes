#include<bits/stdc++.h>
using namespace std;
const int maxn=20;
int vis[maxn][maxn];
struct node{
	int frx,fry,tox,toy;
}p[maxn];
struct nodee{
	int x,y;
};
int anslen[maxn];
vector<nodee>answ[maxn];
int n,m;
void dfs(int x,int y,int now,int stp){
	vis[x][y]=1;
	answ[now].push_back(nodee{x,y});
	if(x==p[now].tox&&y==p[now].toy){
		anslen[now]=stp;
		return;
	}
	if(x<p[now].tox){
		if(x+1<=n&&((!vis[x+1][y])||(x+1==p[now].tox&&y==p[now].toy))){
			dfs(x+1,y,now,++stp);
			return;
		}
		else{
			if(!vis[x-1][y]&&x-1>0){
				dfs(x-1,y,now,++stp);
				return;
			}
		}
	}
	if(y<p[now].toy){
		if(y+1<=n&&(!vis[x][y+1]||(y+1==p[now].toy&&x==p[now].tox))){
			dfs(x,y+1,now,++stp);
			return;
		}
		else{
			if(!vis[x][y-1]&&y-1>0){
				dfs(x,y-1,now,++stp);
				return;
			}
		}
	}
	if(x>p[now].tox){
		if(x-1>0&&(!vis[x-1][y]||(y==p[now].toy&&x-1==p[now].tox))){
			dfs(x-1,y,now,++stp);
			return;
		}
		else{
			if(!vis[x+1][y]&&x+1<=n){
				dfs(x+1,y,now,++stp);
				return;
			}
		}
	}
	if(y>p[now].tox){
		if(y-1>0&&(!vis[x][y-1]||(y-1==p[now].toy&&x==p[now].tox))){
			dfs(x,y-1,now,++stp);
			return;
		}
		else{
			if(!vis[x][y+1]&&y+1<=n){
				dfs(x,y+1,now,++stp);
				return;
			}
		}
	}
	
}
signed main(){
	freopen("flowfree.in","r",stdin);
	freopen("flowfree.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>p[i].frx>>p[i].fry>>p[i].tox>>p[i].toy;
		vis[p[i].frx][p[i].fry]=1;
		vis[p[i].tox][p[i].toy]=1;
	}
	for(int i=1;i<=m;i++){
		dfs(p[i].frx,p[i].fry,i,1);
	}
	for(int i=1;i<=m;i++){
		cout<<anslen[i]<<'\n';
		for(int j=0;j<anslen[i];j++){
			cout<<answ[i][j].x<<" "<<answ[i][j].y<<'\n';
		}
	}
	return 0;
}

