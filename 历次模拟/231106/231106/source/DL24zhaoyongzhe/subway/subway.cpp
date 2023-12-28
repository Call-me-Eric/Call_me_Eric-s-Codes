#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f=  1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f  =-1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
bool st;
const int maxn = 510, maxm = maxn * maxn + 10;
int n, k;
struct node{
	int first, second;
	node(int f = 0,int s = 0):first(f),second(s){}
	friend bool operator < (node a,node b){return a.first != b.first ? a.first < b.first : a.second < b.second;}
	friend bool operator > (node a,node b){return a.first != b.first ? a.first > b.first : a.second > b.second;}
};
int staid[maxn][1 << 8], subwayid[maxn], totpoint;
//node temp[maxm];

int head[maxm], tot;
struct edge{
	int to, nexte;long long wei;
	edge(int to = 0,int ne = 0,long long we = 0):to(to),nexte(ne),wei(we){}
}e[maxm * 50];
void add(int u,int v,long long w){e[++tot] = edge(v,head[u],w);head[u] = tot;}
bool book1[1 << 8][1 << 8];
long long a[9][maxn], b[9][maxn];
long long dis[maxm];bool book[maxm];
int m[9], from[9][1100], to[9][1100], wei[9][1100];
priority_queue<node, vector<node>, greater<node> > que;

bool ed;
signed main(){
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
//	cerr << "MEMORY cost " << (&st - &ed) / 1024 / 1024 << endl;
	n = read(); k = read();
	for(int sta = 0;sta < (1 << k);sta++)
		for(int u = 1;u <= n;u++){
			staid[u][sta] = ++totpoint;
//			printf("staid[%d][%d]=%d\n",u,sta,totpoint);
//			temp[totpoint] = node(u,sta);
		}
	
//	int tmp1 = totpoint;
	for(int tmp = 1;tmp <= k;tmp++){
		for(int i = 1;i <= n;i++){a[tmp][i] = read();}
		for(int i = 1;i <= n;i++){b[tmp][i] = read();}
		m[tmp] = read();
		for(int i = 1;i <= m[tmp];i++)
			from[tmp][i] = read(), to[tmp][i] = read(), wei[tmp][i] = read();
	}
	for(int sta = 0;sta < (1 << k);sta++){
		for(int sub = 0;sub < k;sub++){
			if((sta & (1 << sub)) && (!book1[sta][sta ^ (1 << sub)])){
				book1[sta][sta ^ (1 << sub)] = 1;
				for(int i = 1;i <= n;i++){
					subwayid[i] = ++totpoint;
//					printf("sta=%d,i=%d,sub=%d,id=%d\n",sta,i,sub + 1,totpoint);
//					temp[totpoint] = node(i,sta + 100 * sub + 100);
				}
				for(int u = 1;u <= n;u++){
					add(staid[u][sta],subwayid[u],a[sub + 1][u]);
					add(subwayid[u],staid[u][sta ^ (1 << sub)],b[sub + 1][u]);
//					tot += 2;
				}
				sub++;
				for(int i = 1;i <= m[sub];i++){
					add(subwayid[from[sub][i]],subwayid[to[sub][i]],wei[sub][i]);
					add(subwayid[to[sub][i]],subwayid[from[sub][i]],wei[sub][i]);
//					tot += 2;
				}sub--;
			}
		}
	}
	
//	cerr << "totpoint = " << totpoint << "  tot = " << tot << endl;
	
	memset(dis,0x3f,sizeof(dis));
	dis[staid[1][(1 << k) - 1]] = 0;que.push(node(0,staid[1][(1 << k) - 1]));
	while(!que.empty()){
		int u = que.top().second;que.pop();if(book[u])continue;book[u] = 1;
//		printf("u = %d,dis=%lld\n",u,dis[u]);
//		printf("%s[%d][%d]\n",u<tmp1?"staid":"subwayid",temp[u].first,temp[u].second);
		for(int i = head[u];i;i = e[i].nexte){
			int v = e[i].to;long long w = e[i].wei;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
//				printf("%s[%d][%d] -> %s[%d][%d] = %lld\n",u<=tmp1?"staid":"subid",temp[u].first,temp[u].second,
//					v<=tmp1?"staid":"subid",temp[v].first, temp[v].second, w);
				
				que.push(node(dis[v],v));
			}
		}
	}
	
	long long ans = 0x3f3f3f3f3f3f3f3f;
	for(int sta = 0;sta < (1 << k);sta++){
		ans = min(ans,dis[staid[n][sta]]);
//		printf("dis[staid[%d][%d]]=%lld\n",n,sta,dis[staid[n][sta]]);
//		for(int i = 1;i <= n;i++)printf("dis[staid[%d][%d]]=%lld\n",i,sta,dis[staid[i][sta]]);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
