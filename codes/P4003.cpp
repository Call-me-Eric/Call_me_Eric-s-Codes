#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f =1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}

const int maxn = 5e4 + 10, maxm = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m;
int head[maxn], tot = 1;
struct edge{
	int to, nexte, cap,flow, cost;
	edge(int t = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0):to(t),nexte(ne),cap(ca),flow(fl),cost(co){}
}e[maxm * 2];
inline void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
inline void addd(int u,int v,int cap,int cost){add(u,v,cap,cost);add(v,u,0,-cost);}

int pre[maxn];
bool book[maxn];
int dis[maxn];
int total;
bool SPFA(int S,int T){
	queue<int> que;
	for(int i = 1;i <= total;i++)dis[i] = INF;
	memset(book,0,sizeof(book));
	memset(pre,0,sizeof(pre));
	que.push(S);book[S] = true;dis[S] = 0;
	while(!que.empty()){
		int u = que.front();que.pop();book[u] = false;
//		printf("head:%d\n",u);
		for(int i = head[u];i;i = e[i].nexte){
			int v = e[i].to;
//			printf("%d ->%d,%d %d %d %d %d\n",i,e[i].to,e[i].cap,e[i].flow,dis[v],dis[u],e[i].cost);
			if((e[i].cap > e[i].flow) && (dis[v] > dis[u] + e[i].cost)){
				pre[v] = i;dis[v] = dis[u] + e[i].cost;
				if(!book[v]){que.push(v);book[v] = true;}
			}
		}
	}
	return pre[T] != 0;
}
pair<int,int> MCMF(int S,int T){
	int mincost = 0, maxflow = 0;
	while(SPFA(S,T)){
		int fl = INF;
		for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
			fl = min(fl,e[i].cap - e[i].flow);
			// printf("%d %d\n",fl,e[i ^ 1].to);
		}
		mincost += fl * dis[T];maxflow += fl;
		for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
			e[i].flow += fl;
			e[i ^ 1].flow -= fl;
		}
	}
	return make_pair(mincost, maxflow);
}
vector<vector<int> >id[4];
//0=l,1=d,2=r,3=u
const int dx[4] = { 0, 1, 0,-1};
const int dy[4] = {-1, 0, 1, 0};
signed main(){
	n = read();m = read();int S = ++total;
	for(int k = 0;k < 4;k++){
		id[k].resize(n + 1);
		for(int i = 1;i <= n;i++){
			id[k][i].resize(m + 1);
			for(int j = 1;j <= m;j++){
				id[k][i][j] = ++total;
//				printf("(%d,%d,%d) = %d\n",i,j,k,id[k][i][j]);
			}
		}
	}
	int T = ++total, res = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if((i + j) & 1){
				for(int k = 0;k < 4;k++){
					int nx = dx[k] + i,ny = dy[k] + j;
					if(nx < 1 || nx > n || ny < 1 || ny > m)continue;
					addd(id[k][i][j],id[(k + 2) % 4][nx][ny],1,0);
				}
			}
			int opt = read();
			int x[4] = {(opt >> 3) & 1,(opt >> 2) & 1,(opt >> 1) & 1,opt & 1};
			int sum = x[0] + x[1] + x[2] + x[3];
//			printf("(%d,%d) : %d %d %d %d\n",i,j,x[0],x[1],x[2],x[3]);
			res += sum;
			if(sum == 0)continue;
			if(sum == 1){
				int p = 0;if(x[1])p = 1;if(x[2])p = 2;if(x[3])p = 3;
				if((i + j) & 1){
					addd(S,id[p][i][j],1,0);
					addd(id[p][i][j],id[(p + 1) % 4][i][j],1,1);
					addd(id[p][i][j],id[(p + 2) % 4][i][j],1,2);
					addd(id[p][i][j],id[(p + 3) % 4][i][j],1,1);
				}
				else{
					addd(id[p][i][j],T,1,0);
					addd(id[(p + 1) % 4][i][j],id[p][i][j],1,1);
					addd(id[(p + 2) % 4][i][j],id[p][i][j],1,2);
					addd(id[(p + 3) % 4][i][j],id[p][i][j],1,1);
				}
			}
			if(sum == 2){
				int p = x[1], q = x[3] + 2;
				if(!x[p]){p = 2, q = 3;}
				if(!x[q]){p = 0, q = 1;}
				if((i + j) & 1){
					addd(S,id[p][i][j],1,0);
					addd(S,id[q][i][j],1,0);
				}
				else{
					addd(id[p][i][j],T,1,0);
					addd(id[q][i][j],T,1,0);
				}
				if(q - p == 2)continue;
				if((i + j) & 1){
					addd(id[p][i][j],id[(p + 2) % 4][i][j],1,1);
					addd(id[q][i][j],id[(q + 2) % 4][i][j],1,1);
				}
				else{
					addd(id[(p + 2) % 4][i][j],id[p][i][j],1,1);
					addd(id[(q + 2) % 4][i][j],id[q][i][j],1,1);
				}
			}
			if(sum == 3){
				int p = 0;if(!x[1])p = 1;if(!x[2])p = 2;if(!x[3])p = 3;
				for(int k = 0;k < 4;k++){
					if(k == p)continue;
					if((i + j) & 1){addd(S,id[k][i][j],1,0);}
					else{addd(id[k][i][j],T,1,0);}
				}
				if((i + j) & 1){
					addd(id[(p + 1) % 4][i][j],id[p][i][j],1,1);
					addd(id[(p + 2) % 4][i][j],id[p][i][j],1,2);
					addd(id[(p + 3) % 4][i][j],id[p][i][j],1,1);
				}
				else{
					addd(id[p][i][j],id[(p + 1) % 4][i][j],1,1);
					addd(id[p][i][j],id[(p + 2) % 4][i][j],1,2);
					addd(id[p][i][j],id[(p + 3) % 4][i][j],1,1);
				}
			}
			if(sum == 4){
				for(int k = 0;k < 4;k++){
					if((i + j) & 1){addd(S,id[k][i][j],1,0);}
					else{addd(id[k][i][j],T,1,0);}
				}
			}
		}
	}
	auto ans = MCMF(S,T);
	if(ans.second != res / 2){puts("-1");}
	else{printf("%d\n",ans.first);}
//	for(int u = 1;u <= total;u++){
//		printf("u = %d\n",u);
//		for(int i = head[u];i;i = e[i].nexte){
//			printf("-> %d,cap = %d, flow = %d, cost = %d\n",e[i].to,e[i].cap,e[i].flow,e[i].cost);
//		}
//	}
	return 0;
}
