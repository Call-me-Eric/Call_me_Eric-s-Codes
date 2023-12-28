#include<cstdio>
#include<cstring>
#define N 1030
#define M 2040121
#define LL long long
using namespace std;
struct node{int next,to;}edge[M];bool vis[N],t[1<<10];int tot,l[N],link[N],ans;
void add(int u,int v){edge[++tot].to=v;edge[tot].next=l[u];l[u]=tot;return;}
int n,m,cnt;
char s[12]; 
inline LL read()
{
    char c;LL f=0,d=1;
    while((c=getchar())<48||c>57)if(c=='-')d=-1;f=(f<<3)+(f<<1)+c-48;
    while((c=getchar())>=48&&c<=57)f=(f<<3)+(f<<1)+c-48;
    return d*f;
}
inline int find(int p)
{
    for(int i=l[p];i;i=edge[i].next)
     if(!vis[edge[i].to])
    {
        vis[edge[i].to]=1;
        int q=link[edge[i].to];
        link[edge[i].to]=p;
        if(!q||find(q)) return true;
        link[edge[i].to]=q;
    }
    return false;
}
int main()
{
	while(n=read(),m=read(),n||m)
	{
		memset(t,0,sizeof t);tot=0;memset(l,0,sizeof l);cnt=0;
		memset(link,0,sizeof link);//多测不清空，亲人两行泪
		for(register int i=1;i<=m;i++)
		{
			scanf("%s",s);int tmp=0,pos=-1;
			for(register int j=0;j<n;j++) if(s[j]=='1') tmp+=1<<j;else if(s[j]=='*') pos=j;//将其状态压缩
			t[tmp]=true;//标记有这个数
			if(pos!=-1) t[tmp^(1<<pos)]=true;//如果有*号，把另外一种情况也考虑上
		}
		for(register int i=0;i<(1<<n);i++) if(t[i])
		{
			cnt++;//cnt表示实际的串数
			for(register int j=0;j<n;j++) if(t[i^(1<<j)]) add(i,i^(1<<j));//与和它只有一位不同的串连边
		}
		ans=0;
		for(register int i=0;i<(1<<n);i++) memset(vis,0,sizeof(vis)),ans+=find(i);
		printf("%d\n",cnt-ans/2);
    printf("n = %d\n", cnt);
    for(int i = 0;i < (1 << n);i++){
		if(!t[i])continue;
        printf("i = %d, a[i] = %d, match[i]=%d\n",i,i,link[i]);
    }
	}
}
