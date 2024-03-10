#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3 ) + (ch ^ 48);ch = getchar();}
	return x * f;
}
inline void write(int x){if(!x)return;write(x / 10);putchar('0' + (x % 10));}
const int maxn = 5e3 + 10, mod = 1e9 + 7;

int n, a[maxn];
int mp[maxn], maxnum;

int trie[2][maxn * 100][22], tot[2],ed[2][maxn * 10];
void insert(int *arr,int len,int pos){
	int u = 1;
	for(int i = 1;i <= len;i++){
		int v = arr[i];
		if(!trie[pos][u][v])trie[pos][u][v] = ++tot[pos];
		u = trie[pos][u][v];
	}
	ed[pos][u]++;
}
bool query(int *arr,int len,int pos){
	int u = 1;
	for(int i = 1;i <= len;i++){
		int v = arr[i];
		if(!trie[pos][u][v])return true;
		u = trie[pos][u][v];
	}
	return ed[pos][u] == 0;
}

int ans = 0;
int arr1[maxn],tot1;
int arr2[maxn],tot2;
void dfs1(int x){
	if(x == tot1 + 1){
		if(query(arr2,tot2,1)){
			insert(arr2,tot2,1);
			ans += 1;
			if(ans > mod)ans -= mod;
		}
		return;
	}
	arr2[++tot2] = arr1[x]; dfs1(x + 1);tot2--;dfs1(x + 1);
}
void dfs(int x){
	if(x == n + 1){
//		puts("arr1=");
//		for(int i = 1;i <= tot1;i++)printf("%lld ",arr1[i]);
//		puts("");
		if(query(arr1,tot1,0)){
			insert(arr1,tot1,0);
			memset(trie[1],0,sizeof(trie[1]));tot2 = 0;
			memset(ed[1],0,sizeof(ed[1]));tot[1] = 1;
			dfs1(1);
		}
		return;
	}
	arr1[++tot1] = a[x]; dfs(x + 1); tot1--;dfs(x + 1);
}

signed main(){
	freopen("nest.in","r",stdin);
	freopen("nest.out","w",stdout);
	n = read();
	for(int i = 1;i <= n;i++)mp[a[i] = read()]++;
	for(int i = 1;i <= 5000;i++){if(mp[i])mp[i] = ++maxnum;}
	for(int i = 1;i <= n;i++)a[i] = mp[a[i]];
	tot[0] = 1;dfs(1);
	printf("%lld\n",ans % mod);
	return 0;
}
