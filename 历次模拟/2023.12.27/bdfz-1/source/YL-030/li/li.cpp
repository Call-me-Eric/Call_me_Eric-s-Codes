#include<bits/stdc++.h>
#define int long long
inline int read()
{	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c&15),c=getchar();
	return f?-x:x;
}
using namespace std;
struct bb
{	int nextt,to;
}op[400005];
int n,m,head[200005],rd[200005],cnt,tot,dot,ans1,ans2;
bool bj[200005];
vector<int> ls; 
inline void add(int x,int y)
{	op[++cnt].nextt=head[x];
	op[cnt].to=y;
	head[x]=cnt;
	rd[y]++;
}
void dfs(int x)
{	bj[x]=1;
	tot+=rd[x];
	dot++;
	ls.push_back(rd[x]);
	for(register int i=head[x],y;i;i=op[i].nextt)
	{	y=op[i].to; 
		if(bj[y])continue;
		dfs(y);
	}
	return ;
}
signed main()
{	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	n=read(),m=read();
	for(register int i=1,x,y;i<=m;++i)
	{	x=read(),y=read();
		add(x,y),add(y,x);
	}
	for(register int i=1;i<=n;++i)
		if(rd[i]>=4)
		{	printf("-1");
			return 0;
		}
	for(register int i=1;i<=n;++i)
		if(!bj[i])
		{	tot=dot=0;
			ls.clear();
			dfs(i);
			if(tot>2*dot)
			{	printf("-1");
				return 0;
			}
			else if(tot==2*dot&&dot!=0)
			{	for(register int j=0;j<ls.size();++j)
					if(ls[j]!=2)
					{	printf("-1");
						return 0;
					}
				ans1+=dot;
			}
			else if(tot==2*dot-2)
			{	bool flag=0;
				for(register int i=0;i<ls.size();++i)
					if(ls[i]>2)
					{	if(ls.size()!=4)
						{	printf("-1");
							return 0;
						}
						else
						{	ans1+=3;
							flag=1;
							break;
						}
					}
				if(flag)continue;
				ans2+=(dot+1)*dot/2;
			}
		}
	if(ans1)printf("1 %lld",ans1);
	else printf("0 %lld",ans2);
	return 0;
}
