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
int n,m;
char a[]={'!','(','0','w','0',')'},s[N];
int ans;
inline void dfs(int x,int now,int lim){
	if(now>5){++ans;return;}
	if(x>lim) return;
	ff(i,x,lim-5+now){
		if(s[i]==a[now]) dfs(i+1,now+1,lim);
	}
}
signed main(){
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","w",stdout);
	n=read(),m=read();
	scanf("%s",s+1);
	char ch,x;
	int l,r;
	ff(o,1,m){
		ch=getchar();
		while(ch>'C'||ch<'A') ch=getchar();
	//	cout<<"!"<<ch<<endl;
		l=read();
		if(ch=='A') x=getchar(),s[l]=x;
		else if(ch=='B'){
			r=read(),x=getchar();
			ff(i,l,r) s[i]=x;
		}
		else{
			r=read(),ans=0;
			dfs(l,1,r);
			printf("%d\n",ans);
		}
	}
	return 0;
}
