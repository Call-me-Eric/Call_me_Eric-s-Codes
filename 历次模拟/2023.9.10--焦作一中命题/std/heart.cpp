#include<bits/stdc++.h>
using namespace std;
const int N = 830;
int n,m;
int a[N][N],b[N][N],row[N],col[N];
int p[2][N][N];struct IO{
    static const int S=1<<21;
    char buf[S],*p1,*p2;int st[105],Top;
    ~IO(){clear();}
    inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
    inline void pc(const char c){Top==S&&(clear(),0);buf[Top++]=c;}
    inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    inline IO&operator >> (char&x){while(x=gc(),x==' '||x=='\n'||x=='\r');return *this;}
    template<typename T>inline IO&operator >> (T&x){
        x=0;bool f=0;char ch=gc();
       while(!isdigit(ch)){if(ch=='-') f^=1;ch=gc();}
        while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=gc();
        f?x=-x:0;return *this;
    }
    inline IO&operator << (const char c){pc(c);return *this;}
    template<typename T>inline IO&operator << (T x){
        if(x<0) pc('-'),x=-x;
        do{st[++st[0]]=x%10,x/=10;}while(x);
        while(st[0]) pc('0'+st[st[0]--]);return *this;
    }
}fin,fout;
void solve()
{
	fin>>n>>m;
	for(int i=1;i<=n;i++)row[i]=0;
	for(int i=1;i<=m;i++)col[i]=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		fin>>a[i][j];
		b[i][j]=0;
		if(a[i][j]==0)row[i]++,col[j]++;
	} 
	int res=0;
	for(int i=1;i<=n;i++)res=max(res,row[i]);
	for(int i=1;i<=m;i++)res=max(res,col[i]);
	fout<<res;fout.pc('\n');
	for(int c=0;c<=1;c++)
	for(int i=1;i<=max(n,m);i++)
	for(int j=1;j<=res;j++)
	p[c][i][j]=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(a[i][j]==0)
	{
		int x=1,y=1;
		while(p[0][i][x])x++;
		while(p[1][j][y])y++;
		if(x==y)
		{
			b[i][j]=x;
			p[0][i][x]=j;
			p[1][j][y]=i;
			continue;
		}
		int c=0,d=1,u=i,v=j;
		while(1)
		{
			int w=p[d][v][x];
			p[c][u][x]=v;
			p[d][v][x]=u;
			if(c==0)b[u][v]=x;
			if(c==1)b[v][u]=x;
			if(!w)
			{
				p[d][v][y]=0;
				break;
			}
			swap(x,y);
			swap(c,d);
			u=v;v=w;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			fout<<b[i][j];
			fout.pc(' ');
		}
		fout.pc('\n');
	}
}
int main()
{
	freopen("heart.in","r",stdin);
	freopen("heart.out","w",stdout);
	int T;
	fin>>T;
	while(T--)
	{
		solve();
	}
	return 0;
} 

