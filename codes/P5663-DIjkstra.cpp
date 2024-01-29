#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
int e[10001][10001];
const int inf = 999999999;
int n, m;
int q, u[10001], v[10001], minn;
int book[10001], dis[40001];
int main(){
	scanf("%d%d%d",&n, &m, &q);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			if(i == j)e[i][j] = 0;
			else e[i][j] = inf;
		}
	}
	memset(book,0,sizeof(int));
	
	for(int i = 1;i <= m;i ++){
		scanf("%d%d",&u[i], &v[i]);
		e[u[i]][v[i]] = e[v[i]][u[i]] = 1;
	}
	for(int i = 1;i <= n;i++){
		dis[i] = e[1][i];
	}
	book[1] = 1;
	int u1 = 0;
	for(int i = 1;i <= n - 1;i++){
		minn = inf;
		for(int j = 1;j <= m;j++){
			if(!book[j] && dis[j] < minn){
				minn = dis[j];
				u1 = j;
			}
		}
		book[u1] = 1;
		for(int j = 1;j <= n;j++){
			if(e[u1][j] != inf)
				if(dis[j] > dis[u1] + e[u1][j] ){
					dis[j] = dis[u1] + e[u1][j];
				}
		}
	}
	int a = 0,l = a, dis1 = 0,dis2 = 0;
	for(int i = 1;i <= q;i++){
		scanf("%d%d",&a,&l);
		dis1 = dis[a] % 2;
		dis2 = l % 2;
		if(l >= dis[a] && dis1 == dis2)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

