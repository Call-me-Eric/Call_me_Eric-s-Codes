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
const int N=1e6+5;
int n, m;
int prm[N]; int v[N];
namespace task1{
	vector<int> div;
	int cur[N], res[N], ans;
	inline void dfs(int x){
		if(x>=n/div[0]){
			int cnt=0;
			for(int i=1; i<=n; ++i) cnt+=cur[i];
			if(cnt<=m&&cnt>ans){
				ans=cnt; 
				for(int i=1; i<=n; ++i) res[i]=cur[i];
			}
			return ;
		}
		if(cur[x]){
			dfs(x+1);
			return ;
		}
		for(auto t:div){
			if(x<=n/t){
				bool flg=1;
				for(int i=x; i<=n; i+=n/t) if(cur[i]) {flg=0; break;}
				if(flg){
					for(int i=x; i<=n; i+=n/t) cur[i]=1;
					dfs(x+1);
					for(int i=x; i<=n; i+=n/t) cur[i]=0;
				}
			}
		}
		dfs(x+1);
	}
	void solve(){
		for(int i=2; i<n; ++i) if(n%i==0) div.push_back(i);
		for(auto t:div){
			for(int i=1; i<=n; i+=n/t) cur[i]=1;
			dfs(2);
			for(int i=1; i<=n; i+=n/t) cur[i]=0;
		}
		for(int i=1; i<=n; ++i) printf("%d", res[i]);
	}
}
inline bool check_sub2(){
	int c=v[n], x=n/c;
	while(x!=1){
		if(v[x]==0){
			if(x!=c) return false;
			return true;
		}
		if(v[x]!=c) return false;
		x/=v[x];
	}
	return true;
}

namespace task2{
	int res[N], ans;
	void solve(){
		int c=v[n];
		for(int x=c; x<n; x*=c){
			int t=m/(n/x);
			if(t*(n/x)>ans){
				ans=t*(n/x);
				for(int i=0; i<n; ++i){
					if((i%x)<=t-1) res[i]=1;
					else res[i]=0;
				}
			}
		}
		for(int i=0; i<n; ++i) printf("%d", res[i]);
		putchar('\n');
	}
}
int main(){
	freopen("ur.in", "r", stdin);
	freopen("ur.out", "w", stdout);
	read(n); read(m);
	if(n==m){
		for(int i=1; i<=n; ++i) putchar('1');
		return 0;
	}
	if(m<=1){
		for(int i=1; i<=n; ++i) putchar('0');
		return 0;
	}
	for(int i=2; i<=n; ++i){
		if(!v[i]) prm[++prm[0]]=i;
		for(int j=1; j<=prm[0]&&i*prm[j]<=n; ++j){
			v[i*prm[j]]=prm[j];
			if(i%prm[j]==0) break;
		}
	}
	if(!v[n]){
		for(int i=1; i<=n; ++i) putchar('0');
		return 0;
	}
	if(!v[n/v[n]]){
		int x=v[n], y=n/v[n];
		int t1=m/(n/x), t2=m/(n/y);
		if(t1*(n/x)>t2*(n/y)){
			//printf("%d\n", t1*(n/x));
			for(int i=0; i<n; ++i){
				if((i%x)<=t1-1) putchar('1');
				else putchar('0');
			}
		}
		else{
			//printf("%d\n", t2*(n/y));
			for(int i=0; i<n; ++i){
				if((i%y)<=t2-1) putchar('1');
				else putchar('0');
			}
		}
		return 0;
	}
	if(check_sub2()){
		task2::solve();
		return 0;
	}
	if(n<=36){
		task1::solve();
		return 0;
	}
	return 0;
}
