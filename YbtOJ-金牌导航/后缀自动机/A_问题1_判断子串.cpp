#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
struct SAM{
	struct node{
		int len, link;
		unordered_map<char,int> nxt;
	}d[maxn * 2];
	int tot, last;
	void insert(char ch){
		int cur = ++tot, p = last;
		d[cur].len = d[last].len + 1;last = cur;
		while(p != -1 && !d[p].nxt[ch]){d[p].nxt[ch] = cur;p = d[p].link;}
		if(p == -1){d[cur].link = 0;}
		else{
			int q = d[p].nxt[ch];
			if(d[q].len == d[p].len + 1){d[cur].link = q;}
			else{
				int clone = ++tot;
				d[clone] = d[q];d[clone].len = d[p].len + 1;
				while(p != -1 && d[p].nxt[ch] == q){d[p].nxt[ch] = clone;p = d[p].link;}
				d[q].link = d[cur].link = clone;
			}
		}
	}
	void build(char *s){
		d[0].link = -1;int len = strlen(s + 1);
		for(int i = 1;i <= len;i++)insert(s[i]);
	}
	bool search(char *s){
		int p = 0, len = strlen(s + 1);
		for(int i = 1;i <= len;i++){
			if(!d[p].nxt[s[i]])return 0;
			p = d[p].nxt[s[i]];
		}
		return 1;
	}
	void DEBUG(){
		for(int i = 0;i <= tot;i++){
			printf("p = %d\n",i);
			for(int j = 'a';j <= 'z';j++){
				if(d[i].nxt[j]){
					printf("%c -> %d\n",j,d[i].nxt[j]);
				}
			}
		}
	}
}sam;
char ch[maxn];
signed main(){
	scanf("%s",ch + 1);sam.build(ch);
	scanf("%s",ch + 1);
	puts(sam.search(ch) ? "Yes" : "No");
//	sam.DEBUG();
	return 0;
}
