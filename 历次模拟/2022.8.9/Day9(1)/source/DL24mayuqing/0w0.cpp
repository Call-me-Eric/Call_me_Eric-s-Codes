#include<bits/stdc++.h>
#define ri register int
using namespace std;
char ch,cc,c[6000];
int n,m,x,y;
inline int read() {
	ri x=0,f=0;
	register char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?-x:x; }

inline void change(int x,char y) {
	c[x]=y;
	return; }

inline void modify(int x,int y,int z) {
	for(ri i=x; i<=y; ++i) c[i]=z;
	return; }

inline void st(int l,int r) {
	int len=r-l+1;
	printf("%d\n",len*(len+1)/2);
	return; }

signed main() {
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","w",stdout);
	n=read(),m=read();
	scanf("%s",c);
	for(ri i=1; i<=m; ++i) {
		scanf("%c",ch);
		if(ch=='C') x=read(),y=read(),st(x,y);
		else if(ch=='A') x=read(),scanf("%c",cc),change(x,cc);
		else x=read(),y=read(),scanf("%c",cc),modify(x,y,cc); }
	return 0; }
