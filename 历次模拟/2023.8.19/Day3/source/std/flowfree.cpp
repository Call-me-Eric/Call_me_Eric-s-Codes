#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<map>

using namespace std;

int n,m,axis[300][4],stack[300],tag[100][100],ans[100][100],link[100][100][5],bx[5],by[5],nxt[100][100][2];

map<long long,long long> f[301];

int calc(long long status,int x)
{
	return (status>>(x*4))&15;
}

long long color(long long status,int x,int y)
{
	long long max=(1ll)<<62;
	max--;
	max^=(15ll)<<(x*4);
	return (status&max)|(((long long)y)<<(x*4));;
}

int find(long long status,int p)
{
	int size=0;
	for (int a=0;a<=n;a++)
	{
		int x=status&15;
		status>>=4;
		if (x==1) stack[++size]=a;
		if (x==2)
		{
			if (a==p) return stack[size];
			if (stack[size]==p) return a;
			size--;
		}
	}
	return -1;
}

void dfs(int a,int b,int c,long long s1)
{
	if (!a) return;

	int b1=calc(s1,b-1);
	int b2=calc(s1,b);
	if (b1)
	{
		link[a][b][4]=true;
		link[a][b-1][3]=true;
	}
	if (b2)
	{
		link[a-1][b][1]=true;
		link[a][b][2]=true;
	}
	
	if (b==1) s1>>=4;
	s1=f[c][s1];
	c--;
	b--;
	if (!b) b=n,a--;
	dfs(a,b,c,s1);
}

int main()
{
	freopen("flowfree.in","r",stdin);
	freopen("flowfree.out","w",stdout);

	bx[1]=1;bx[2]=-1;by[3]=1;by[4]=-1;
	scanf("%d%d",&n,&m);
	for (int a=1;a<=m;a++)
		scanf("%d%d%d%d",&axis[a][0],&axis[a][1],&axis[a][2],&axis[a][3]);
	for (int a=1;a<=m;a++)
	{
		tag[axis[a][0]][axis[a][1]]=a+2;
		tag[axis[a][2]][axis[a][3]]=a+2;
	}
	f[0][0]=-1;
	int size=0;
	for (int a=1,c=1;a<=n;a++)
		for (int b=1;b<=n;b++,c++)
		{
			map<long long,long long>::iterator it=f[c-1].begin();
			for (;it!=f[c-1].end();it++)
			{
				size++;
				long long status=it->first;
				if (b==1) 
				{
					int x=calc(status,n);
					if (x) 
					{
						continue;
					}
					status=status<<4;
				}
				int bit1=calc(status,b-1);
				int bit2=calc(status,b);
				if (tag[a][b])
				{
					if (bit1 && bit2) continue;
					if (bit1 || bit2)
					{
						int bit,x;
						if (bit1) bit=bit1,x=b-1;
						else bit=bit2,x=b;
						if (bit>2)
						{
							if (bit!=tag[a][b]) continue;
							long long newstatus=color(status,b,0);
							newstatus=color(newstatus,x,0);
							f[c][newstatus]=status;
						}
						else
						{
							int p=find(status,x);
							long long newstatus=color(status,p,tag[a][b]);
							newstatus=color(newstatus,x,0);
							f[c][newstatus]=status;
						}
					}
					else
					{
						long long newstatus;
						if (b!=n)
						{
							newstatus=color(status,b,tag[a][b]);
							f[c][newstatus]=status;
						}
						newstatus=color(status,b-1,tag[a][b]);
						f[c][newstatus]=status;
					}
				}
				else
				{
					if (bit1 && bit2)
					{
						long long newstatus=color(status,b-1,0);
						newstatus=color(newstatus,b,0);
						if (bit1<=2)
						{
							if (bit2<=2)
							{
								int p1=find(status,b-1);
								int p2=find(status,b);
								if (p1>p2) swap(p1,p2);
								if (p1==b-1 && p2==b) continue;
								newstatus=color(newstatus,p1,1);
								newstatus=color(newstatus,p2,2);
								f[c][newstatus]=status;
							}
							else
							{
								int p=find(status,b-1);
								newstatus=color(newstatus,p,bit2);
								f[c][newstatus]=status;
							}
						}
						else
						{
							if (bit2<=2)
							{
								int p=find(status,b);
								newstatus=color(newstatus,p,bit1);
								f[c][newstatus]=status;
							}
							else
							{
								if (bit1!=bit2) continue;
								f[c][newstatus]=status;
							}
						}
					}
					else
					{
						if (!bit1 && !bit2)
						{
							if (b==n) continue;
							long long newstatus=color(status,b-1,1);
							newstatus=color(newstatus,b,2);
							f[c][newstatus]=status;
						}
						else
						{
							int bit,x;
							if (bit1) bit=bit1,x=b-1;
							else bit=bit2,x=b;
							long long newstatus;
							if (b!=n)
							{
								newstatus=color(status,b,bit);
								newstatus=color(newstatus,b-1,0);
								f[c][newstatus]=status;
							}
							newstatus=color(status,b-1,bit);
							newstatus=color(newstatus,b,0);
							f[c][newstatus]=status;
						}
					}
				}
			}
		}
	if (f[n*n].count(0)) 
	{
		dfs(n,n,n*n-1,f[n*n][0]);
        for (int a=1;a<=n;a++)
            for (int b=1;b<=n;b++)
                if (tag[a][b] && !ans[a-1][b-1])
                    for (int x=a,y=b,lx=0,ly=0;;)
                    {
                        ans[x-1][y-1]=tag[a][b]-2;
                        bool find=false;
                        for (int c=1;c<=4 && !find;c++)
                        {
                            int xx=x+bx[c];
                            int yy=y+by[c];
                            if (link[x][y][c] && (xx!=lx || yy!=ly))
                            {
                                nxt[x][y][0]=xx;
                                nxt[x][y][1]=yy;
                                find=true;
                                lx=x;ly=y;
                                x=xx;y=yy;
                            }
                        }
                        if (!find) break;
                    }
		for (int a=1;a<=m;a++)
		{
			int cnt=0;
			for (int x=axis[a][0],y=axis[a][1];x && y;)
			{
				cnt++;
				int xx=nxt[x][y][0];
				int yy=nxt[x][y][1];
				x=xx;
				y=yy;
			}
			if (cnt==1)
			{
				cnt=0;
				swap(axis[a][0],axis[a][2]);
				swap(axis[a][1],axis[a][3]);
				for (int x=axis[a][0],y=axis[a][1];x && y;)
				{
					cnt++;
					int xx=nxt[x][y][0];
					int yy=nxt[x][y][1];
					x=xx;
					y=yy;
				}
			}
			printf("%d\n",cnt);
			for (int x=axis[a][0],y=axis[a][1];x && y;)
			{
				printf("%d %d\n",x,y);
				cnt++;
				int xx=nxt[x][y][0];
				int yy=nxt[x][y][1];
				x=xx;
				y=yy;
			}
		}
	}

	return 0;
}
