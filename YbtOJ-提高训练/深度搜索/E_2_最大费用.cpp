#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}
int n, m;
const int maxn = 41;
int a[maxn], rest[maxn],ans;
struct cmp{bool operator()(int a,int b){return a > b;}};
void dfs(int step,int total){
	ans = max(ans,total);
	if(step > n){return;}
	if(total + rest[step] < ans)return;
	for(int i = step;i <= n;i++){
		if(total + a[i] < m)dfs(i + 1,total + a[i]);
		else if(total + a[i] == m){printf("%d\n",m);exit(0);}
	}
}
signed main(){
	n = read(); m = read();
	for(int i = 1;i <= n;i++){a[i] = read();}
	sort(a + 1, a + 1 + n,cmp());
	for(int i = n;i >= 0;i--){rest[i] = rest[i + 1] + a[i];}
	dfs(0,0);printf("%d\n",ans);
	return 0;
}
