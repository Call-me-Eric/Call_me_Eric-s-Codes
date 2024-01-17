#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int deg[200001];
bool vis[200001];
long long xs;
int s,cnt;
vector<int>g[200001];
int sq[200001];
void dfs(int x){
	vis[x]=1;
	sq[++cnt]=x;
	int i;
	for(i=0;i<g[x].size();i++){
		int y=g[x][i];
		if(vis[y])continue;
		dfs(y);
	}
}
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	int i,j,n,m;
	scanf("%d%d",&n,&m);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		deg[x]++;deg[y]++;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(i=1;i<=n;i++){
		cnt=0;
		if(vis[i])continue;
		dfs(i);
		int cnt1=0,cnt2=0,cnt3=0;
		for(j=1;j<=cnt;j++){
			if(deg[sq[j]]==1)cnt1++;
			else if(deg[sq[j]]==2)cnt2++;
			else if(deg[sq[j]]==3)cnt3++;
			else if(deg[sq[j]])s=-1;
			else if(s==0)xs++;
		}
		if(cnt==1)continue;
		if(cnt!=4&&cnt3)s=-1;
		if(cnt3&&cnt1!=3)s=-1;
		if(s==-1)break;
		if(cnt3)cnt3=cnt1=0,cnt2=3;
		if(cnt1&&s==0)xs+=1ll*cnt*(cnt+1)/2;
		if(!cnt1){
			if(s==0)s=1,xs=0;
			xs+=cnt2;
		}
	}
	if(s==-1)printf("-1\n");
	else printf("%d %lld\n",s,xs);
}
