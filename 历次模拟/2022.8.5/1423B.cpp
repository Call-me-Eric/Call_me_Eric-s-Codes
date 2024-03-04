#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<vector>
#define TT int
using namespace std;
inline TT read(){
	TT x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}
int n, m;
struct node{
	int u, w;
};
const int maxn = 1e4 * 3,maxm = 1e5 * 3;
vector<node> E[maxn];
int match[maxn];
bool book[maxn];
bool dfs(int x,int d){
	for(int j = 0,len = E[x].size();j < len;j++){
		node i = E[x][j];
		if(!book[i.u]){
			book[i.u] = 1;
			if(i.w <= d &&(!match[i.u] || dfs(match[i.u],d))){
				match[i.u] = x;
				return true;
			}
		}
	}
	return false;
}
bool check(int d){
	int cnt = 0;
	memset(match,0,sizeof(match));
	for(int i = 1;i <= n;i++){
		memset(book,0,sizeof(book));
		if(dfs(i,d))cnt++;
	}
	if(cnt == n)return true;
	else return false;
}
signed main(){
	int u, v, w;
	int l = 0,r = 0;
	n = read(); m = read();
	for(int i = 1;i <= m;i++){
		u = read(); v = read(); w = read();
		E[u].push_back(node{v,w});E[v].push_back(node{u,w});
		r = max(w,r);
	}
	int ans = -1;
	while(l < r){
		int mid = (l + r) >> 1;
		if(check(mid)) {
			ans = mid;
			r = mid;
		}
		else l = mid + 1;
	}
	printf("%d\n",ans);
	return 0;
}

