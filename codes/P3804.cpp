#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	int x = 0,f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
char ch[maxn];
int n, cf[maxn * 2], a[maxn * 2];
struct SAM{
	int tot, last, rt;
	struct node{
		int link, len, siz;
		unordered_map<char,int> nxt;
	}d[maxn * 2];
	void init(){rt = tot = last = 0;d[rt].link = -1;d[rt].nxt.clear();}
	void insert(char ch){
		int cur = ++tot;d[cur].siz = 1;
		d[cur].len = d[last].len + 1;
		int p = last;
		while(p != -1 && !d[p].nxt[ch]){
			d[p].nxt[ch] = cur;p = d[p].link;
		}
		if(p == -1){d[cur].link = 0;last = cur;return;}
		int q = d[p].nxt[ch];
		if(d[q].len == d[p].len + 1){d[cur].link = q;last = cur;return;}
		int clone = ++tot;
		d[clone] = d[q];d[clone].len = d[p].len + 1;d[clone].siz = 0;
		while(p != -1 && d[p].nxt[ch] == q){d[p].nxt[ch] = clone;p = d[p].link;}
		d[cur].link = d[q].link = clone;
		last = cur;
	}
	ll calc(){
		ll ans = -1;
		for(int i = 0;i <= tot;i++){cf[d[i].len]++;}cf[0] = 0;
		for(int i = 1;i <= n;i++)cf[i] += cf[i - 1];
		for(int i = 0;i <= tot;i++)a[cf[d[i].len]--] = i;
		for(int i = tot;i;i--){
			int p = a[i];
//printf("a[%d] = %d,link = %d,siz = %d\n",i,a[i],d[p].link,d[p].siz);
			d[d[p].link].siz += d[p].siz;
			if(d[p].siz > 1){ans = max(ans,(ll)d[p].siz * d[p].len);}
		}
		return ans;
	}
	void DEBUG(){
		for(int p = 0;p <= tot;p++){
			printf("p = %d:\nlink = %d,siz = %d,len = %d\n",p,d[p].link,d[p].siz,d[p].len);
			for(char j = 'a';j <= 'z';j++){
				if(d[p].nxt[j]){
					printf("%c -> %d\n",j,d[p].nxt[j]);
				}
			}
		}
	}
}sam;
signed main(){
//	freopen("P3804_1.in","r",stdin);
	scanf("%s",ch + 1); n = strlen(ch + 1);
	sam.init();
	for(int i = 1;i <= n;i++){sam.insert(ch[i]);}
	printf("%lld\n",sam.calc());
//	sam.DEBUG();
	return 0;
}
