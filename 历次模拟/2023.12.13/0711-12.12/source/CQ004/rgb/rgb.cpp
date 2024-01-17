#include<bits/stdc++.h>
#define pass void("from python import pass");
using namespace std;
int n,m;
int k[3];
int f[400];
int u[40000],v[40000],w[40000],h[40000];
vector<int>e[400];
mt19937_64 g;
void dfs(int x)
{
    f[x]=1;
    for(int i:e[x])
    {
        int y=u[i]^v[i]^x;
        if(!f[y])
        {
            h[i]=1;
            k[w[i]]--;
            dfs(y);
        }
    }
}
void paint(int x,int s,unsigned long long c)
{
    f[x]=c;
    for(int i:e[x])
    {
        int y=u[i]^v[i]^x;
        if(h[i]&&!f[y])
        {
            paint(y,s,w[i]==s?g():c);
        }
    }
}
int cut(int x,int z,int s,int from)
{
    if(x==z)
    {
        return 1;
    }
    for(int i:e[x])
    {
        int y=u[i]^v[i]^x;
        if(h[i]&&y!=from)
        {
            int res=cut(y,z,s,x);
            if(res==1&&w[i]==s)
            {
                h[i]=0;
                k[s]++;
                return 2;
            }
            if(res)
            {
                return res;
            }
        }
    }
    return 0;
}
int main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    scanf("%d%d%d%d",&k[0],&k[1],&k[2],&m);
    n=k[0]+k[1]+k[2]+1;
    for(int i=0;i<m;i++)
    {
        char c;
        scanf("%d%d %c",&u[i],&v[i],&c);
        if(c=='g')
        {
            w[i]=1;
        }
        if(c=='b')
        {
            w[i]=2;
        }
        e[u[i]].push_back(i);
        e[v[i]].push_back(i);
    }
    dfs(1);
    while(k[0]||k[1]||k[2])
    {
        int l,r;
        for(int i=0;i<3;i++)
        {
            if(k[i]>0)
            {
                l=i;
            }
            if(k[i]<0)
            {
                r=i;
            }
        }
        memset(f,0,sizeof f);
        paint(1,r,g());
        for(int i=0;i<m;i++)
        {
            if(w[i]==l&&f[u[i]]!=f[v[i]])
            {
                cut(u[i],v[i],r,0);
                h[i]=1;
                k[l]--;
                goto nex;
            }
        }
        for(int i=0;i<m;i++)
        {
            if(w[i]==(3^l^r)&&f[u[i]]!=f[v[i]])
            {
                cut(u[i],v[i],r,0);
                h[i]=1;
                k[3^l^r]--;
                memset(f,0,sizeof f);
                paint(1,3^l^r,g());
                for(int i=0;i<m;i++)
                {
                    if(w[i]==l&&f[u[i]]!=f[v[i]])
                    {
                        cut(u[i],v[i],3^l^r,0);
                        h[i]=1;
                        k[l]--;
                        goto nex;
                    }
                }
                printf("NO\n");
                return 0;
            }
        }
        printf("NO\n");
        return 0;
    nex:
        pass
    }
    printf("YES\n");
    for(int i=0;i<m;i++)
    {
        printf("%d",h[i]);
    }
    printf("\n");
    return 0;
}