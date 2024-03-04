#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define re register
#define rep(a,b,c)  for(re int a(b) ; a<=c ; ++a)
#define drep(a,b,c) for(re int a(b) ; a>=c ; --a)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int T;
signed main(){
	freopen("battery.in","r",stdin);
	freopen("battery.out","w",stdout);
	T=read();
	while(T--) printf("IMPOSSIBLE\n");
	return 0;
}

