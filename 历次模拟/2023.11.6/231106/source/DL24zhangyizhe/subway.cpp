# include <bits/stdc++.h>

using namespace std;

# define ll long long
# define PII pair< int , int >
# define MP make_pair
# define fi first
# define se second
# define pb push_back

int read()
{
# define C ch = getchar()
	int x = 0; char C;
	for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
	return x;
}

const int N = 505 , M = 1e3 + 5 , K = 1e6;
int n , k , m[N];
int ecnt , head[N*16] , to[K] , nxt[K] , w[K] , S , T;
int a[10][N] , b[10][N];

void AddEdge(int u , int v , int W)
{
	nxt[++ecnt] = head[u] , head[u] = ecnt , to[ecnt] = v , w[ecnt] = W;
}

int id(int t , int u , int opt)
{
	return (t - 1) * n * 2 + u + opt * n;
}

bool vis[(N<<1)*8][(1<<9)+5];
ll dis[(N<<1)*8][(1<<9)+5] , ans = 1e18;

struct node
{
	int u , s;
	ll v;
	node() {}
	node(int u , int s , ll v) : u(u) , s(s) , v(v) {}
	bool operator < (const node &rhs) const {return v > rhs.v;}
} ;

priority_queue< node > Q;

int arcid(int x)
{
	return (x - 1) / (2 * n) + 1;
}

void Di()
{
	for(int i = S; i <= T; i++) for(int j = 0; j < (1 << k + 1); j++) dis[i][j] = 1e18;
	dis[0][0] = 0;
	Q.push(node(0 , 0 , 0));
	while(!Q.empty())
	{
		int u = Q.top().u , s = Q.top().s; Q.pop();
//		cout << u << ' ' << s << ' ' << dis[u][s] << endl;
		if(vis[u][s]) continue ;
		vis[u][s] = 1;
		for(int i = head[u]; i; i = nxt[i])
		{
			int v = to[i];
			int p = arcid(u) , q = arcid(v);
//			cout << v << endl;
//			cout << u << ' ' << v << ' ' << p << ' ' << q << endl;
			if(p == q || u == S || v == T)
			{
				if(dis[v][s | (1 << q - 1)] > dis[u][s] + w[i])
				{
					dis[v][s | (1 << q - 1)] = dis[u][s] + w[i];
					Q.push(node(v , s | (1 << q - 1) , dis[v][s | (1 << q - 1)]));
				}
			}
			else
			{
//				cout << s << ' ' << q << '*' << endl;
				if((s & (1 << q - 1)) == 0) 
				{
					if(dis[v][s | (1 << q - 1)] > dis[u][s] + w[i])
					{
						dis[v][s | (1 << q - 1)] = dis[u][s] + w[i];
						Q.push(node(v , s | (1 << q - 1) , dis[v][s | (1 << q - 1)]));
					}
				}
			}
		}
	}
}

int main()
{
	freopen("subway.in" , "r" , stdin);
	freopen("subway.out" , "w" , stdout);
	n = read() , k = read();
	S = 0 , T = 2 * n * k + 1;
	for(int t = 1; t <= k; t++)
	{
		for(int i = 1; i <= n; i++) a[t][i] = read() , AddEdge(id(t , i , 0) , id(t , i , 1) , a[t][i]);
		for(int i = 1; i <= n; i++) b[t][i] = read();
		m[t] = read();
		for(int i = 1 , u , v , w; i <= m[t]; i++)
		{
			u = read() , v = read() , w = read();
			AddEdge(id(t , u , 1) , id(t , v , 1) , w) , AddEdge(id(t , v , 1) , id(t , u , 1) , w);
//			cout << id(t , u , 1) << ' ' << id(t , v , 1) << endl;
		}
	}
	for(int i = 1; i <= k; i++) for(int j = 1; j <= k; j++) if(i ^ j)
	{
		for(int u = 1; u < n; u++)
		{
			AddEdge(id(i , u , 1) , id(j , u , 0) , b[i][u]);
		}
	}
	for(int i = 1; i <= k; i++) AddEdge(S , id(i , 1 , 0) , 0) , AddEdge(id(i , n , 1) , T , b[i][n]);
//	for(int i = 1; i <= T; i++) cout << i << ' ' << arcid(i) << endl;
	Di();
	for(int i = 0; i < (1 << k + 1); i++) ans = min(ans , dis[T][i]);
	cout << ans;  
	return 0;
}
