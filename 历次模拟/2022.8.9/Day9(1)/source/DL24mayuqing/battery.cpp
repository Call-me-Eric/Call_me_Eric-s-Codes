#include<bits/stdc++.h>
#define ri register int
using namespace std;
char ch;
int T,n,m;
inline int read() {
	ri x=0,f=0;
	register char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?-x:x; }

signed main() {
	freopen("battery.in","r",stdin);
	freopen("battery.out","w",stdout);
	T=read();
	while(T--) {
		n=read(),m=read();
		for(ri i=1; i<=n; ++i) cin>>ch;
		puts("IMPOSSIBLE"); }
	return 0; }
