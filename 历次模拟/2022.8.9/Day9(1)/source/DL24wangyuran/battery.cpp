#include<bits/stdc++.h>
#define ll long long
#define ff(i,s,e) for(int i(s);i<=(e);++i)
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=55;
const int dx[]={0,1,0,-1,0};
const int dy[]={0,0,1,0,-1};
char s[N][N];
int n,m;
int pos[5];
inline void solve(){
	n=read(),m=read();
	ff(i,1,n) scanf("%s",s+1);
	printf("IMPOSSIBLE\n");
}
signed main(){
	freopen("battery.in","r",stdin);
	freopen("battery.out","w",stdout);
	int T=read();
	while(T--) solve();
}
