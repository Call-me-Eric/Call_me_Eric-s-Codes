/*
5 7
1 2 2
1 3 2
1 4 3
2 3 1
2 5 3
3 5 2
4 5 4
*/
#include <cstdio>
#include <iostream>
using namespace std;
const int maxm = 1000;
const int maxn = 100;
int num = 0;
int head[maxn*2];
struct Edge{
	int next;
	int to;
	int dis;
}edge[maxm*2];
void add_edge(int from, int to, int dis){
	edge[++num].next = head[from];
	edge[num].to = to;
	edge[num].dis = dis;
	head[from] = num;
}
int main(){
	int n, m, u, v, d;
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		cin >> u >> v >> d;
		add_edge(u, v, d);
		add_edge(v, u, d);
	}
	cout << "head:" << endl;
	for(int i = 1; i <= n; i++) 
		cout << head[i] << ' ';
	cout << endl;
	cout << "edge:" << endl;
	for(int i = 1; i <= 2 * m; i++)
		cout  << i << ' '<< edge[i].to << ' '<< edge[i].dis << endl;
	return 0;
}
