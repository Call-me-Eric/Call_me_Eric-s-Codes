#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
vector<pair<int,int> > S;
int res = 1;bool book[310];
void dfs(int u){
	if(u == S.size()){
		int tmp = 0;
		for(int i = 1;i <= 300;i++){if(!book[i]){tmp = i;break;}}
		res = max(res,tmp);
		return;
	}
	book[S[u].first] ^= 1;dfs(u + 1); book[S[u].first] ^= 1;
	book[S[u].second] ^= 1;dfs(u + 1); book[S[u].second] ^= 1;
}
unsigned long long solve(){res = 0;dfs(0);return res;}
signed main(){
	freopen("mex.in","r",stdin);
	freopen("mex.out","w",stdout);
	int n,T,seed1,seed2,p;
	unsigned long long ans = 0;
	n = read(); T = read(); seed1  =read(); seed2 = read(); p = read();
	for(int i = 1;i <= n;i++){
		int a, b;
		if (i <= T)a = read(), b = read();
		else a = (1ll * ans * i ^ seed1) % p + 1, b = (1ll * ans * i ^ seed2) % p + 1;
		if(a > 300)a = 301;if(b > 300)b = 301;
		S.push_back(make_pair(a, b));
		ans = (ans ^ (1ll * solve() * i));
	}
	printf("%llu\n",ans);
	return 0;
}
