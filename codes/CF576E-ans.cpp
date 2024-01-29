#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int N=5e5+10,K=55;
vector<int>e[N<<2];
int pos[N],top,u[N],v[N],a[N],c[N],n,m,k,q,f[K][N<<1],height[K][N<<1];
int find(int c,int x){return f[c][x]==x?x:find(c,f[c][x]);}
struct node{int c,x,y,add;}stk[N];
void merge(int c,int x,int y)
{
	if(x==y) return ;
    if(height[c][x]>height[c][y]) swap(x,y);
    stk[++top]=node{c,x,y,height[c][x]==height[c][y]};
    f[c][x]=y;height[c][y]+=height[c][x]==height[c][y];
}
void update(int p,int l,int r,int nl,int nr,int k)
{
	if(nl<=l&&r<=nr){e[p].push_back(k);return ;}
	int mid=l+r>>1;
	if(nl<=mid) update(p<<1,l,mid,nl,nr,k);
	if(nr>mid) update(p<<1|1,mid+1,r,nl,nr,k);
}
void solve(int p,int l,int r)
{
	int back=top,mid=l+r>>1;
	for(auto i:e[p])
	{
		int fx=find(c[i],u[a[i]]),fy=find(c[i],v[a[i]]);
		merge(c[i],find(c[i],u[a[i]]),find(c[i],v[a[i]]+n));
		merge(c[i],find(c[i],u[a[i]]+n),find(c[i],v[a[i]]));
	}
	if(l==r)
	{
		if(find(c[r],u[a[r]])==find(c[r],v[a[r]])) puts("NO"),c[r]=pos[a[r]]; 
		else puts("YES"),pos[a[r]]=c[r];
	}
	else solve(p<<1,l,mid),solve(p<<1|1,mid+1,r);
	while(top>back)
	{
		int c=stk[top].c,x=stk[top].x,z=stk[top].add;top--;
		height[c][f[c][x]]-=z;f[c][x]=x;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int j=1;j<=k;j++)
	    for(int i=1;i<=n;i++)
	        f[j][i]=i,f[j][i+n]=i+n;
	for(int i=1;i<=m;i++) scanf("%d%d",&u[i],&v[i]),pos[i]=q+1;
	for(int i=1;i<=q;i++) scanf("%d%d",&a[i],&c[i]);
	int cnt=0;
	for(int i=q;i>=0;i--)
	{
		if(i+1<pos[a[i]]) update(1,1,q,i+1,pos[a[i]]-1,i);
		//i+1是因为如果判断i时直接把它加进来，这时的颜色是新的颜色，但后面撤销的就是原来的颜色，就会产生错误 
		pos[a[i]]=i;
	}
	memset(pos,0,sizeof(pos));solve(1,1,q);
	return 0;
}
