#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
char ch[maxn];
bool book[maxn * 2];
struct SAM{
	struct node{
		int link, len, siz;
		unordered_map<char,int> nxt;
	}d[maxn * 2];
	int a[maxn * 2], cf[maxn], tot, last;
	void build(){tot = last = 0;d[0].link = -1;}
	void insert(char ch){
		int cur = ++tot;d[cur].siz = 1;
		d[cur].len = d[last].len + 1;
		int p = last;
		while(p != -1 && !d[p].nxt[ch]){d[p].nxt[ch] = cur;p = d[p].link;}
		if(p == -1){d[cur].link = 0;}
		else{
			int q = d[p].nxt[ch];
			if(d[p].len + 1 == d[q].len){d[cur].link = q;}
			else{
				int clone = ++tot;
				d[clone].link = d[q].link;
				d[clone].nxt = d[q].nxt;
				d[clone].len = d[p].len + 1;
				while(p != -1 && d[p].nxt[ch] == q){d[p].nxt[ch] = clone;p = d[p].link;}
				d[q].link = d[cur].link = clone;
			}
		}
		last = cur;
	}
	void build(char *s){
		build();
		int len = strlen(s + 1);
		for(int i = 1;i <= len;i++)insert(s[i]);
		for(int i = 0;i <= tot;i++)cf[d[i].len]++;cf[0] = 0;
		for(int i = 1;i <= len;i++)cf[i] += cf[i - 1];
		for(int i = 0;i <= tot;i++)a[cf[d[i].len]--] = i;
		for(int i = tot;i;i--){int p = a[i];d[d[p].link].siz += d[p].siz;}
	}
	int query(char *s){
		int ans = 0;
		int p = 0, len = strlen(s + 1), dep = 0;
		vector<int> vec;vec.clear();
		for(int i = 1;i < len * 2;i++){
			char ch = s[(i - 1) % len + 1];
			while(p != -1 && !d[p].nxt[ch]){p = d[p].link;dep = d[p].len;}
			if(p != -1){
				p = d[p].nxt[ch];dep++;
				while(dep > len){dep--;if(dep <= d[d[p].link].len)p = d[p].link;}
				if(dep >= len && !book[p]){ans += d[p].siz;book[p] = 1;vec.push_back(p);}
			}
			else p = 0;
		}
		for(int u : vec)book[u] = false;
		return ans;
	}
}sam;
signed main(){
	scanf("%s",ch + 1);sam.build(ch);
	for(int T = read();T;T--){
		scanf("%s",ch + 1);
		printf("%d\n",sam.query(ch));
	}
	return 0;
}
