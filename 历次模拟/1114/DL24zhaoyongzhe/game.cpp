#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
int n, L, R;
priority_queue<int,vector<int>,less<int> > que;
signed main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	n = read();L = read(); R = read();
	for(int i = 1;i <= n;i++)que.push(read());
	int minn = 0, maxx = 0;bool flag = false;
	while(!que.empty() && !flag){
		maxx += que.top();que.pop();
		minn += que.top();que.pop();
		if(maxx > R){flag = 1;break;}
	}
	if(maxx > R || minn < L)puts("Alice");
	else puts("Bob");
	return 0;
}
