#include<bits/stdc++.h>
using namespace std;
const int dx[8] = {-3,-2, 0, 2, 3, 2, 0,-2};
const int dy[8] = { 0, 2, 3, 2, 0,-2,-3,-2};
int a[10][10];
bool limit[10][10];
int stx = 3, sty = 3;
int edx = 4, edy = 2;
int b[1000][1000];
inline int read(){
	int x = 0, f =1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
void dfs(int x,int y,int cnt){
	if(cnt == 26){
		if(a[edx][edy] != 25)return;
		for(int i = 1;i <= 5;i++)
			for(int j = 1;j <= 5;j++)
				printf("%c%2d%s",",{"[j == 1],a[i][j],j == 5 ? "},\n" : "");
		puts("");
		exit(0);
	}
	for(int i = 0;i < 8;i++){
		int nx = x + dx[i], ny = y + dy[i];
		if(nx < 1 || nx > 5 || ny < 1 || ny > 5 || a[nx][ny] || limit[nx][ny])continue;
		a[nx][ny] = cnt;
		dfs(nx,ny,cnt + 1);
		a[nx][ny] = 0;
	}
}
void preworkfunction(){
	freopen("tmp.out","w",stdout);
	a[stx][sty] = 1;dfs(stx,sty,2);
}
void checker(){
	freopen("out.out","r",stdin);
	vector<int> vec;vec.clear();int x  = 0;
	while(scanf("%d",&x) != EOF){vec.push_back(x);}
	int n = sqrt((int)vec.size()),pointer = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			b[i][j] = vec[pointer];pointer++;
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			if(b[i][j] > n * n || b[i][j] < 1)printf("out of limit on (%d,%d)\n",i,j);
			bool chk = false;
			for(int k = 0;k < 8;k++){
				int nx = i + dx[k], ny = j + dy[k];
				if(nx < 1 || nx > n || ny < 1 || ny > n)continue;
				chk |= (b[nx][ny] - 1 == ((b[i][j]) % (n * n)));
			}
			if(!chk)printf("no path on (%d,%d)\n",i,j);
		}
	}
	cerr << "size = " << vec.size() << endl;
}
namespace solve{
	bool stmemory;
	const int maxn = 1e4 + 10,maxm = 1e6 + 10, INF = 0x3f3f3f3f ,maxN = 2e5 + 10;
	int n, m;
	
	int head[maxN], tot = 1;
	struct edge{
		int to, nexte, cap, flow;
		edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
	}e[maxm];
	void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
	void addd(int u,int v,int cap){add(u,v,cap);add(v, u, 0);}
	int total, mx;
	
	int dep[maxN], cur[maxN];
	int dfs(int u,int flow,int T){
		// printf("%lld\n",u);
		if(u == T)return flow;
		int rest = 0, tmp = 0;
		for(int i = cur[u];i && flow;i = e[i].nexte){
			cur[u] = i; int v = e[i].to;
			if(e[i].cap - e[i].flow > 0 && (dep[v] == dep[u] + 1)){
				tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
				if(tmp == 0)dep[v] = INF;
				e[i].flow += tmp; e[i ^ 1].flow -= tmp;
				flow -= tmp;rest += tmp;
				if(!flow)return rest;
			}
		}
		return rest;
	}
	bool bfs(int S,int T){
		queue<int> que;
		for(int i = 1;i <= total;i++){dep[i] = INF;cur[i] = 0;}
		que.push(S);dep[S] = 1; cur[S] = head[S];
		while(!que.empty()){
			int u = que.front(); que.pop();
			for(int i = head[u];i;i = e[i].nexte){
				int v = e[i].to;
				if(e[i].cap - e[i].flow > 0 && dep[v] == INF){
					que.push(v);
					cur[v] = head[v];
					dep[v] = dep[u] + 1;
					if(v == T)return 1;
				}
			}
		}
		return 0;
	}
	int Dinic(int S,int T){
		int mxflow = 0;
		while(bfs(S,T)){mxflow += dfs(S,INF,T);}
		return mxflow;
	}
	int a[maxn], b[maxn], w[maxn], l[maxn], r[maxn], p[maxn];
	int id[maxn][2];
	bool edmemory;
	vector<int> tmp;
	signed main(){
		cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << "Mib cost\n";
		n = read();int S = ++total;int T = ++total, sum = 0;mx = 1e9;
		for(int i = 1;i <= n;i++){id[i][0] = ++total;id[i][1] = ++total;}
		for(int i = 1;i <= n;i++){
			a[i] = read(); b[i] = read(); w[i] = read(); l[i] = read();r[i] = read();p[i] = read();
			tmp.push_back(a[i]);sum += b[i] + w[i];
		}
		sort(tmp.begin(),tmp.end());tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
		mx = tmp.size();
		for(int i = 1;i <= n;i++){
			a[i] = lower_bound(tmp.begin(),tmp.end(),a[i]) - tmp.begin();
			l[i] = upper_bound(tmp.begin(),tmp.end(),l[i]) - tmp.begin();
			r[i] = upper_bound(tmp.begin(),tmp.end(),r[i]) - tmp.begin();
			addd(S,id[i][0],b[i]);addd(id[i][0],id[i][1],INF);addd(id[i][1],T,w[i]);
			int virt = ++total;addd(id[i][0],virt,p[i]);
			for(int j = 1;j < i;j++){
				if(l[i] <= a[j] && a[j] <= r[i]){
					addd(virt,id[j][1],INF);
				}
			}
		}
		printf("%d\n",sum - Dinic(S,T));
//	for(int i = 2;i <= tot;i += 2){
//		printf("%lld -> %lld , cap = %lld, flow = %lld\n",e[i ^ 1].to,e[i].to,e[i].cap,e[i].flow);
//	}
//	printf("S = %lld, T = %lld\n",S,T);
//	for(int i = 1;i <= n;i++){
//		printf("i = %lld:0 = %lld, 1 = %lld\n",i,id[i][0],id[i][1]);
//	}	
		return 0;
	}
};
struct node{
	int x, y, val;
	node(int x = 0,int y = 0,int val = 0):x(x),y(y),val(val){}
	friend bool operator < (node a,node b){
		return a.y != b.y ? a.y > b.y : a.x != b.x ? a.x < b.x : a.val < b.val;
	}
};
set<node> st;
signed main(){
//	checker();
//	limit[4][1]  = limit[4][4] = 1;
//	preworkfunction();
//	solve::main();
	// st.insert(node(1, 3));
	// st.insert(node(3, 1));
	// st.insert(node(3, 3));
	// auto x = st.lower_bound(node(2,2)), y = st.lower_bound(node(3,3));
	// printf("%d %d\n",y->x,y->y);
	// y++;
	// printf("%d %d\n",y->x,y->y);
	printf("%d\n",(-1) ^ 1); 
	
	return 0;
}
