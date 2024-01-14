#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 250 + 10;
int a[maxn][maxn];
int n, m;
int mxn[maxn], mxm[maxn];
bool ml[maxn * maxn], mr[maxn * maxn];
queue<pair<int,int> > que;
signed main(){
	n = read(); m = read();int posx = 0, posy = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			int x = read();
			mxn[i] = max(x,mxn[i]);
			mxm[j] = max(x,mxm[j]);
		}
	}
	for(int i = 1;i <= n;i++)ml[mxn[i]] = 1;
	for(int i = 1;i <= m;i++)mr[mxm[i]] = 1;
	for(int i = n * m;i;i--){
		if(ml[i] || mr[i]){
			posx += ml[i];posy += mr[i];
			a[posx][posy] = i;
		}
		else{a[que.front().first][que.front().second] = i;que.pop();}
		if(ml[i])for(int j = posy - 1;j;j--){que.push(make_pair(posx,j));}
		if(mr[i])for(int j = posx - 1;j;j--){que.push(make_pair(j,posy));}
	}
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			printf("%d%c",a[i][j]," \n"[j == m]);
	return 0;
}
