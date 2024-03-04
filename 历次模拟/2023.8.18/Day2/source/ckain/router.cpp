#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define int long long
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

const int N=1e6+5, inf=1e15;

int n, a[N];
vector<int> e[N];

int F[N][3];//没有被子树覆盖 被子树覆盖 被自己覆盖 

void dfs(int u, int fa){
	F[u][2]=a[u];
	int mndif=inf, flag=0;
	for(int v:e[u]) if(v!=fa){
		dfs(v, u);
		//F[u][0]
		F[u][0]+=F[v][1];
		//F[u][1]
		if(F[v][2]<=F[v][1]) flag=1, F[u][1]+=F[v][2], mndif=0;
		else if(!flag) F[u][1]+=F[v][1], mndif=min(mndif, F[v][2]-F[v][1]);
		//F[u][2]
		F[u][2]+=min({F[v][0], F[v][1], F[v][2]});
	}
	if(mndif==inf) F[u][1]=inf;
	else if(!flag) F[u][1]+=mndif;
}

signed main(){
	freopen("router.in", "r", stdin);
	freopen("router.out", "w", stdout);
	n=rd();
	for(int i=1; i<=n; i++) a[i]=rd();
	for(int i=1, u, v; i<n; i++){
		u=rd(), v=rd();
		e[u].push_back(v), e[v].push_back(u);
	}
	dfs(1, 0);
	
	printf("%lld\n", min(F[1][1], F[1][2]));
	return 0;
}
