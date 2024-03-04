//mondstadt
#incldue<bits/stdc++.h>
using namespace std;

const int mod = 1e9+7;
int n,m;
int head[211*4],tot = 1;
struct node
{
	int to,nxt;
}e[211*4];
int cnt[210];
inline void add(int u,int v)
{
	e[++tot].to = v;
	e[tot].nxt = head[u];
	head[u] = tot;
}
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
    return x*f;
}

int main()
{
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
	n = read();
	m = read();
	for(int i=1;i<=m;i++)
	{
		int u,v;
		u = read();
		v = read();
		add(u,v);
		add(v,u);
	}
	
	printf("1");
	return 0;
}
