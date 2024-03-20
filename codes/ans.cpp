#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#define  N  510000
#define  NN  1100000
using  namespace  std;
struct  node
{
	int  lc,rc,l,r,c;
}tr[NN];int  len;
void  bt(int  l,int  r)
{
	len++;int  now=len;
	tr[now].l=l;tr[now].r=r;
	if(l<r)
	{
		int  mid=(l+r)>>1;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
	}
}
inline  int  mymax(int  x,int  y){return  x>y?x:y;}
int  change(int  now,int  x,int  k,int  type/*type=0表示代替，type=1表示取max*/)//返回的是x的值
{
	if(tr[now].l==tr[now].r){int  ans=tr[now].c;type==0?tr[now].c=k:tr[now].c=mymax(tr[now].c,k);return  ans;}
	int  mid=(tr[now].l+tr[now].r)/2,lc=tr[now].lc,rc=tr[now].rc,ans=0;
	if(x<=mid)ans=change(lc,x,k,type);
	else  ans=change(rc,x,k,type);
	tr[now].c=mymax(tr[lc].c,tr[rc].c);
	return  ans;
}
bool  findans(int  now,int  l,int  r,int  k/*参数*/)//返回是否包含区间
{
	if(tr[now].l==l  &&  tr[now].r==r)return  tr[now].c>=k;
	int  mid=(tr[now].l+tr[now].r)/2,lc=tr[now].lc,rc=tr[now].rc;
	if(r<=mid)return  findans(lc,l,r,k);
	else  if(mid<l)return  findans(rc,l,r,k);
	else  return  findans(lc,l,mid,k)|findans(rc,mid+1,r,k);
}
//线段树
class  fhq//fhq treap万岁 
{
	public:
		int  size[N],vio[N],root[N],key[N],son[N][2];
		inline  void  pushup(int  x){size[x]=size[son[x][0]]+size[son[x][1]];}
		void  spilt(int  now,int  k,int  &x,int  &y)
		{
			if(!now)x=0,y=0;
			else
			{
				if(key[now]<=k)x=now,spilt(son[x][1],k,son[x][1],y),pushup(x);
				else  y=now,spilt(son[y][0],k,x,son[y][0]),pushup(y),pushup(y);
			}
		}
		int  merge(int  x,int  y)
		{
			if(!x  ||  !y)return  x+y;
			if(vio[x]<=vio[y])son[x][1]=merge(son[x][1],y);
			else  son[y][0]=merge(x,son[y][0]),x^=y^=x^=y;
			pushup(x);return  x;
		}
		void  first_do(int  x)
		{
			for(int  i=1;i<=x;i++)size[i]=1,vio[i]=rand(),key[i]=i;
		}
		void  add(int  &rt,int  id/*编号*/)
		{
			if(!rt)rt=id;
			else
			{
				int  x,y;spilt(rt,id,x,y);
				rt=merge(merge(x,id),y);
			}
		}
		void  del(int  &rt,int  id)//从根为rt的树中分离id 
		{
			int  x,y,z;spilt(rt,id-1,x,y);spilt(y,id,y,z);
			rt=merge(x,z);
		}
		int  findqian(int  &rt,int  k/*查找k的前驱*/)
		{
			if(rt==0)return  0;
			int  x=rt,ans=0;
			while(x)
			{
				if(key[x]>=k)x=son[x][0];
				else  if(key[x]<k)ans=x,x=son[x][1];
			}
			return  ans;
		}
		int  findhou(int  &rt,int  k/*查找k的前驱*/)
		{
			if(rt==0)return  0;
			int  x=rt,ans=0;
			while(x)
			{
				if(key[x]>k)ans=x,x=son[x][0];
				else  if(key[x]<=k)x=son[x][1];
			}
			return  ans;
		}
}zjj;
int  to[N][2],n,m;
int  a[N],b[N];
int  main()
{
	freopen("tmp.in","r",stdin);
	freopen("ans.out","w",stdout);
	srand(999);
	scanf("%d%d",&n,&m);
	zjj.first_do(n);bt(1,n);
	for(int  i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		to[i][0]=b[i];to[b[i]][1]=i;
	}
	for(int  i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		zjj.add(zjj.root[a[i]],i);
	}
	for(int  i=1;i<=n;i++)
	{
		for(int  j=0;j<=1;j++)
		{
			int  x=zjj.findhou(zjj.root[to[a[i]][j]],i);//找到符合对数的数字。
			if(x)change(1,x,i,1);
		}
	}
	//建树
	for(int  i=1;i<=m;i++)
	{
		int  type,l,r;scanf("%d%d%d",&type,&l,&r);
		if(type==2)
		{
			if(findans(1,l,r,l)==true)printf("Yes\n");
			else  printf("No\n");
		}//短短的询问
		else
		{
			int  x=0;
			for(int  j=0;j<=1;j++)x=mymax(x,zjj.findqian(zjj.root[to[r][j]],l));//代替数字 
			x=change(1,l,x,0);//表示替代原来的位置，并且获取到现在的位置
			//以新的"l"为r的区间
			int  y=zjj.findhou(zjj.root[a[l]],l);
			if(y)change(1,y,x,1);
			//以旧的"l"为r的区间
			zjj.del(zjj.root[a[l]],l);zjj.add(zjj.root[r],l);
			//平衡树换点
			for(int  j=0;j<=1;j++)
			{
				int  xx=to[a[l]][j];//表示与他有关的 
				y=zjj.findhou(zjj.root[xx],l);
				if(y)
				{
					int  z=0;
					for(int  k=0;k<=1;k++)z=mymax(z,zjj.findqian(zjj.root[to[xx][k]],y));//重新去找
					change(1,y,z,0);
				}
			}
			//以旧的"l"为l的区间
			for(int  j=0;j<=1;j++)
			{
				x=zjj.findhou(zjj.root[to[r][j]],l);//代替数字 
				if(x)change(1,x,l,1);
			}
			//以新的"l"为l的区间
			a[l]=r;
		}
	}
	return  0;
}
