#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char getc() {
	static char *p1, *p2, buf[1<<20];
	return p1==p2?(p2=(p1=buf)+fread(buf, 1, 1<<20, stdin), p1==p2?10:*p1++):*p1++;
}
inline void read(char *s) {
	char c; while (!isdigit(c=getc()));
	while (isdigit(c)) *s++=c, c=getc();
	*s++='\0';
}
inline int read() {
	int f=1, r=0; char c=getc();
	while (!isdigit(c)) f^=c=='-', c=getc();
	while (isdigit(c)) r=r*10+c-48, c=getc();
	return f?r:-r;
}
const int N=150007, mod=998244353;
inline void inc(int &x, int y) {x+=y; if (x>=mod) x-=mod;}
const string str[22]={"11","19","41","61","89","409","449","499","881","991","6469","6949","9001","9049","9649","9949","60649","666649","946669","60000049","66000049","66600049"};
const int len[22]={2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 6, 6, 8, 8, 8};	
const string S="046891";
const int to[10]={0, 5, -1, -1, 1, -1, 2, -1, 3, 4};
int tot, trans[N][6], cnt[N]; ll state[N];
map<ll, int> id;
int a[22], b[22], dp[102][N];
int n;
char s[N];
inline int solve() {
	int ans=0, u=1;
	for (int i=1; i<=n; i++) {
		int x=s[i]-'0';
		for (int j=0; j<x; j++) {
			if (!~to[j]) continue;
			int v=trans[u][to[j]];
			if (v) inc(ans, dp[n-i][v]);
		}
		if (!~to[x]) {u=0; break;}
		u=trans[u][to[x]]; if (!u) break;
	}
	ans+=u>0;
	return ans;
}
inline void work() {
	read(s+1), n=strlen(s+1);
	for (int i=n; i; i--) {
		if (s[i]=='0') s[i]='9';
		else {s[i]--; break;}
	}
	int ans=mod-solve();
	read(s+1), n=strlen(s+1), inc(ans, solve());
	printf("%d\n", ans);
}
int main() {
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	//tot++;
	//for (int i=0; i<4; i++) trans[1][i]=1;
	queue<int> q; q.push(++tot);
	while (!q.empty()) {
		int u=q.front(); q.pop(); ll tmp=state[u];
		for (int i=21; ~i; i--) a[i]=tmp%len[i], tmp/=len[i];
		//trans[u][5]=1;
		for (int i=0; i<6; i++) {
			bool ok=true;
			for (int j=0; j<22; j++) {
				b[j]=a[j];
				if (str[j][b[j]]==S[i]) {
					b[j]++;
					ok&=b[j]<len[j];
				}
			}
			if (!ok) continue;
			ll x=0;
			for (int j=0; j<22; j++) x=x*len[j]+b[j];
			if (!id.count(x)) id[x]=++tot, state[tot]=x, q.push(tot);
			trans[u][i]=id[x], cnt[u]+=trans[u][i]==u;
		}
	}
	for (int x=1; x<=tot; x++) dp[0][x]=1;
	for (int l=1; l<=100; l++)
		for (int x=1; x<=tot; x++)
			for (int j=0; j<6; j++) {
				int y=trans[x][j];
				if (y) inc(dp[l][x], dp[l-1][y]);
			}
	//cerr<<tot<<endl;
	for (int T=read(); T; T--) work();
	return 0;
}
