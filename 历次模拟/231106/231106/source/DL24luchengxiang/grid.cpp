#include<bits/stdc++.h>
using namespace std;
#define inl inline
#define ll long long
#define int ll
const int N=5e2+5;
const int M=2e3+5;
const int inf=0x3f3f3f3f3f3f3f3f;
const int mod=1e9+7;
inl int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
inl void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inl void writei(int x){write(x);putchar(' ');}
inl void writel(int x){write(x);putchar('\n');}
int n,q,a[N][N],ans,x,y;
int dx[5]={0,1,1,-1,-1};
int dy[5]={0,1,-1,1,-1};
struct node{
	int x,y,t;
};
inl bool check(int x,int y){return x>=1&&x<=n&&y>=1&&y<=n;}
inl int bfs(int sx,int sy,int px,int py){
	queue<node>q;q.push((node){sx,sy,0});
	int ans=0;
	while(!q.empty()){
		int x=q.front().x,y=q.front().y,t=q.front().t;q.pop();
		ans++;if(a[x][y]<t||(x==px&&y==py))continue;
		for(int i=1;i<=4;i++)if(check(x+dx[i],y+dy[i]))q.push({x+dx[i],y+dy[i],a[x][y]+1});
	}
	cerr<<ans<<endl;
	return ans;
}
signed main(){
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=read();
	q=read();
	while(q--){
		int x=read(),y=read(),ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				ans+=bfs(i,j,x,y);
		writel(ans);
	}
	return 0;
}


