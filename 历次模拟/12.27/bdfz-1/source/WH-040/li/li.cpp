#include<bits/stdc++.h>
using namespace std;

int n,m,sum;
pair<int,int> E[1000005];
vector<int> id[1000005];
int vis[1000005];
vector<int> G[1000005];

void dfs(int x,int f,int& cntv,int& cnte){
	if(vis[x])return;
	vis[x]=1;
	cntv++;
	for(int y:G[x]){
		if(y==f)continue;
		dfs(y,x,cntv,cnte);
		cnte++;
	}
}




int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	scanf("%d %d",&n,&m);
	sum+=n;
	for(int i=1;i<=m;++i)
		scanf("%d %d",&E[i].first,&E[i].second),id[E[i].first].push_back(i),id[E[i].second].push_back(i);
	for(int i=1;i<=n;++i){
		if(id[i].size()>3){
			printf("-1\n");
			return 0;
		}
	}
	for(int o=1;o<=10;++o){
		int ln=n;
		n=m;
		m=0;
		sum+=n;
		for(int i=1;i<=ln;++i){
			for(int j=0;j<(int)id[i].size();++j){
				for(int k=j+1;k<(int)id[i].size();++k){
					E[++m]={id[i][j],id[i][k]};
				}
			}
		}
		for(int i=1;i<=n;++i)
			id[i].clear();
		for(int i=1;i<=m;++i)
			id[E[i].first].push_back(i),id[E[i].second].push_back(i);
			for(int i=1;i<=n;++i){
				if(id[i].size()>2){
					printf("-1\n");
					return 0;
				}
			}
	}
	for(int i=1;i<=m;++i)
		G[E[i].first].push_back(E[i].second),G[E[i].second].push_back(E[i].first);
	long long ans0=sum;
	int ans1=0;
	for(int i=1;i<=n;++i){
		if(vis[i])continue;
		int cntv=0,cnte=0;
		dfs(i,0,cntv,cnte);
//		cerr<<cntv<<' '<<cnte<<'\n';
		if(cntv+1==cnte)
			ans1+=cntv;
		else
			ans0+=1ll*(cntv-1)*cntv/2;
	}
	if(ans1)
		printf("%d %d\n",1,ans1);
	else
		printf("%d %lld\n",0,ans0);
}
