#include<bits/stdc++.h>
#define TT int
using namespace std;
inline TT read(){
	char ch = getchar();TT x = 0, f = 1;
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}
int T, n, m;
const int maxn = 4 * 1e5;
int top[maxn],d[maxn];
struct node{
	int x, y;
}deedge[maxn];
struct edge{
	int to, nxt;
}e[maxn];
int tot = 0, first[maxn];
void add(int u,int v){
	e[++tot].nxt = first[u];
	e[tot].to = v;
	first[u] = tot;
	d[v]++;
}
bool top_sort(){
	int u, sum = 0;
	queue<int> que;
	for(int i = 1;i <= n;i++)if(!d[i])que.push(i);
	while(!que.empty()){
		u = que.front();
		que.pop();
		top[u] = ++sum;
		for(int i = first[u];i;i = e[i].nxt){
			d[e[i].to]--;
			if(!d[e[i].to])que.push(e[i].to);
		}
	}
	if(sum != n)return false;
	else return true;
}
signed main(){
	T = read();
	while(T--){
		tot = 0;
		int t, x, y, cnt = 0;
		n = read();m = read();
		for(int i = 1;i <= n;i++){
			top[i] = first[i] = d[i] = 0;
		}
		for(int i = 1;i <= m;i++){
			t = read();x = read();y = read();
			if(t){
				add(x,y);
			}
			else{
				node tmp;
				tmp.x = x;
				tmp.y = y;
				deedge[++cnt] = tmp;
			}
		}
		if(top_sort()){
			puts("YES");
			for(int i = 1;i <= n;i++){
				for(int j = first[i];j;j = e[j].nxt){
					printf("%d %d\n",i,e[j].to);
				}
			}
			for(int i = 1;i <= cnt;i++){
				if(top[deedge[i].x] > top[deedge[i].y]){
					printf("%d %d\n",deedge[i].y,deedge[i].x);
				}
				else printf("%d %d\n",deedge[i].x,deedge[i].y);
			}
		}
		else puts("NO");
	}
	return 0;
}

