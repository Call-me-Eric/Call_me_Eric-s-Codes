#include<bits/stdc++.h>
using namespace std;
const int M=255,MM=62555;
int r,g,b,m,n;
int head[M],ver[2*MM],nxt[2*MM],edge[2*MM],tot=1;
map<int,bool>v[35][35][35];
queue<int>q;
bool vv[2*MM],vm[M];
void add(int x,int y,int z)
{
    tot++;
    nxt[tot]=head[x];
    head[x]=tot;
    ver[tot]=y,edge[tot]=z;
}
void dfs(int x,int sr,int sg,int sb,int now)
{
    if(sr==r&&sg==g&&sb==b&&now==(1<<n)-1)
    {
        printf("YES\n");
        for(int i=1;i<=m;i++)
        {
            if(vv[i]) printf("1");
            else printf("0");
        }
        exit(0);
    }
    if(v[sr][sg][sb].count(now)) return;
    v[sr][sg][sb][now]=1;
    for(int i=2;i<=n;i++)
        if(!((now>>(i-1))&1))
            for(int j=head[i];j;j=nxt[j])
            {
                int y=ver[j],z=edge[j];
                if(vv[j/2]) continue;
                if((now>>(y-1))&1)
                {
                    if(z==1)
                    {
                        if(sr+1>r) continue;
                        vv[j/2]=1,dfs(y,sr+1,sg,sb,now|(1<<(i-1))),vv[j/2]=0;
                    }
                    else if(z==2)
                    {
                        if(sg+1>g) continue;
                        vv[j/2]=1,dfs(y,sr,sg+1,sb,now|(1<<(i-1))),vv[j/2]=0;
                    }
                    else
                    {
                        if(sb+1>b) continue;
                        vv[j/2]=1,dfs(y,sr,sg,sb+1,now|(1<<(i-1))),vv[j/2]=0;
                    }
                }
            }
}
int main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    int x,y,z;
    char c;
    scanf("%d%d%d%d",&r,&g,&b,&m),n=r+g+b+1;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d %c",&x,&y,&c);
        if(c=='r') z=1;
        else if(c=='g') z=2;
        else z=3;
        add(x,y,z),add(y,x,z);
    }
    if(n<=30)
    {
        dfs(1,0,0,0,1),printf("NO");
        return 0;
    }
    int sr=0,sg=0,sb=0,now,flag=0;
    vm[1]=1;
    for(int i=head[1];i;i=nxt[i]) q.push(i);
    while(q.size())
    {
        now=q.front(),y=ver[now],z=edge[now];
        q.pop(),flag=0;
        if(vv[now/2]||vm[y]) continue;
        if(z==1&&sr+1<=r) sr++,flag=1;
        else if(z==2&&sg+1<=g) sg++,flag=1;
        else if(z==3&&sb+1<=b) sb++,flag=1;
        if(flag)
        {
            vv[now/2]=1,vm[y]=1;
            for(int i=ver[y];i;i=nxt[i]) q.push(i);
        }
    }
    if(sr==r&&sg==g&&sb==b)
    {
        printf("YES\n");
        for(int i=1;i<=m;i++)
        {
            if(vv[i]) printf("1");
            else printf("0");
        }
    }
    else printf("NO");
    return 0;
}