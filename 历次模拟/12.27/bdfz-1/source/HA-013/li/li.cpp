#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef __int128 lint;
typedef double dou;
typedef long double ld;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mapa make_pair
template <typename _T> inline void read(_T &x){
	x=0; char c=getchar(); bool f=0;
	for(; c<'0'||c>'9'; c=getchar()) f|=(c=='-');
	for(; c>='0'&&c<='9'; c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
const int N=2e5+5;
int n, m;
vector<int> e[N];
#define deg(x) (int)e[x].size()
int circle=0; ll chain=0;
int vis[N];
inline int dfs(int x){
	vis[x]=1;
	int ret=1;
	for(auto y:e[x]) if(!vis[y]) ret+=dfs(y);
	return ret;
}
int main(){
	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);
	read(n); read(m);
	for(int i=1, x, y; i<=m; ++i){
		read(x); read(y);
		e[x].emplace_back(y);
		e[y].emplace_back(x);
	}
	for(int i=1; i<=n; ++i) if(deg(i)>3){
		printf("-1\n");
		return 0;
	}
	for(int i=1; i<=n; ++i) if(deg(i)==3){
		bool flg=1;
		for(auto x:e[i]) {
			vis[x]=1;
			if(deg(x)>1) {flg=0; break;};
		}
		if(flg==0){
			printf("-1\n");
			return 0;
		}
		circle+=3;
	}
	for(int i=1; i<=n; ++i) if(deg(i)==1&&!vis[i]){
		int cur=dfs(i);
		chain+=(ll)cur*(cur+1)/2;
	}
	for(int i=1; i<=n; ++i) if(deg(i)==2&&!vis[i]){
		int cur=dfs(i);
		circle+=cur;
	}
	int cd0=0;
	for(int i=1; i<=n; ++i) if(deg(i)==0) ++cd0;
	if(circle==0){
		printf("0 %lld\n", chain+cd0);
	}
	else{
		printf("1 %d\n", circle);
	}
	return 0;
}
