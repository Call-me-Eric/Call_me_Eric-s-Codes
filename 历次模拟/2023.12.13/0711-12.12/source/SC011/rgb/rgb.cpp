#include<bits/stdc++.h>
using namespace std;
const int N=1001;
int n,n1,n2,n3,m,m1,m2,m3,w,fa[N];
bool h[N*N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
struct road
{
    int x,y,t;
    road() {}
    road(int x,int y,int t):x(x),y(y),t(t) {}
}a0[N*N];
vector<road> a1,a2,a3,a4,a[N];
vector<int> b;
bool dfs(int x,int y,int fa)
{
    if(x==y) return true;
    for(auto i:a[x])
    {
        if(i.x==fa) continue;
        b.push_back(i.t);
        if(dfs(i.x,y,x)) return true;
        b.pop_back();
    }
    return false;
}
void dfs2(int x,int fa)
{
    for(auto i:a[x])
    {
        if(i.x==fa) continue;
        h[i.t]=true;
        dfs2(i.x,x);
    }
}
void add(int t)
{
    // printf("add %d %d\n",a0[t].x,a0[t].y);
    a[a0[t].x].push_back(road(a0[t].y,0,t));
    a[a0[t].y].push_back(road(a0[t].x,0,t));
}
void del(int t)
{
    // printf("del %d %d\n",a0[t].x,a0[t].y);
    vector<road> z=a[a0[t].x];
    a[a0[t].x].clear();
    for(auto i:z)
    {
        if(i.t!=t) a[a0[t].x].push_back(i);
    }
    z=a[a0[t].y];
    a[a0[t].y].clear();
    for(auto i:z)
    {
        if(i.t!=t) a[a0[t].y].push_back(i);
    }
}
void solve(int x)
{
    for(int i=1;i<=n;++i) fa[i]=i,a[i].clear();
    for(auto i:a2)
    {
        fa[find(i.x)]=find(i.y);
        add(i.t);
    }
    for(auto i:a3)
    {
        if(find(i.x)!=find(i.y))
        {
            fa[find(i.x)]=find(i.y);
            add(i.t);
        }
        else
        {
            if(x==0)
            {
                b.clear();
                dfs(i.x,i.y,0);
                for(auto j:b)
                {
                    if(a0[j].t==2)
                    {
                        del(j);
                        break;
                    }
                }
                add(i.t);
            }
            else --x;
        }
    }
    int y1=0,y2=0,y3=0;
    a4.clear();
    for(int i=1;i<=n;++i)
    {
        for(auto j:a[i])
        {
            if(j.x==a0[j.t].y)
            {
                a4.push_back(road(a0[j.t].x,a0[j.t].y,j.t));
            }
        }
        a[i].clear();
    }
    // printf("clear\n");
    // printf(":\n");
    for(int i=1;i<=n;++i) fa[i]=i;
    for(auto i:a1)
    {
        if(find(i.x)!=find(i.y))
        {
            fa[find(i.x)]=find(i.y);
            // printf("%d %d %d %d\n",i.x,i.y,a0[i.t].t,y1);
            add(i.t);
            ++y1;
        }
    }
    vector<road> z;
    // printf("0:\n");
    for(auto i:a4)
    {
        if(find(i.x)!=find(i.y))
        {
            // printf("%d %d %d %d %d\n",i.x,i.y,a0[i.t].t,y2,y3);
            fa[find(i.x)]=find(i.y);
            add(i.t);
            if(a0[i.t].t==2) ++y2;
            else ++y3;
        }
        else z.push_back(i);
    }
    // printf("%d %d %d %d\n",y1,y2,y3,n);
    if(y2>n2)
    {
        // printf("2:\n");
        a4=z;
        z.clear();
        for(auto i:a4)
        {
            if(y2==n2)
            {
                z.push_back(i);
                continue;
            }
            if(a0[i.t].t==2)
            {
                z.push_back(i);
                continue;
            }
            // printf("%d %d %d %d %d\n",i.x,i.y,a0[i.t].t,y2,y3);
            b.clear();
            dfs(i.x,i.y,0);
            bool u=false;
            for(auto j:b)
            {
                if(a0[j].t==2)
                {
                    del(j);
                    z.push_back(road(a0[j].x,a0[j].y,j));
                    --y2;
                    add(i.t);
                    ++y3;
                    u=true;
                    break;
                }
            }
            if(!u) z.push_back(i);
        }
    }
    if(y3>n3)
    {
        // printf("3:\n");
        a4=z;
        z.clear();
        for(auto i:a4)
        {
            if(y3==n3)
            {
                z.push_back(i);
                continue;
            }
            if(a0[i.t].t==3)
            {
                z.push_back(i);
                continue;
            }
            // printf("%d %d %d %d %d\n",i.x,i.y,a0[i.t].t,y2,y3);
            b.clear();
            dfs(i.x,i.y,0);
            bool u=false;
            for(auto j:b)
            {
                if(a0[j].t==3)
                {
                    del(j);
                    z.push_back(road(a0[j].x,a0[j].y,j));
                    --y3;
                    add(i.t);
                    ++y2;
                    u=true;
                    break;
                }
            }
            if(!u) z.push_back(i);
        }
    }
    // printf("%d %d %d %d\n",y1,y2,y3,n);
    // printf("1:\n");
    // printf("%d %d %d\n",y1,y2,y3);
    a4=z;
    z.clear();
    for(auto i:a4)
    {
        if((a0[i.t].t==2&&y2==n2)||(a0[i.t].t==3&&y3==n3)) continue;
        // printf("%d %d %d %d %d %d\n",i.x,i.y,a0[i.t].t,y1,y2,y3);
        b.clear();
        dfs(i.x,i.y,0);
        for(auto j:b)
        {
            if(a0[j].t==1)
            {
                del(j);
                --y1;
                add(i.t);
                if(a0[i.t].t==2) ++y2;
                else ++y3;
                break;
            }
        }
    }
    // printf("%d %d %d %d\n",y1,y2,y3,n);
    if(y1==n1&&y2==n2&&y3==n3)
    {
        dfs2(1,0);
        printf("YES\n");
        for(int i=1;i<=m;++i)
        {
            if(h[i]) printf("1");
            else printf("0");
        }
        exit(0);
    }
}
int main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    scanf("%d%d%d%d",&n1,&n2,&n3,&m);
    n=n1+n2+n3+1;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        char z[10];
        scanf("%d%d%s",&x,&y,z);
        a0[i].x=x,a0[i].y=y;
        if(z[0]=='r') a1.push_back(road(x,y,i)),a0[i].t=1;
        else if(z[0]=='g') a2.push_back(road(x,y,i)),a0[i].t=2;
        else if(z[0]=='b') a3.push_back(road(x,y,i)),a0[i].t=3;
    }
    for(int i=1;i<=n;++i) fa[i]=i;
    vector<road> z=a1;
    a1.clear();
    for(auto i:z)
    {
        if(find(i.x)!=find(i.y))
        {
            fa[find(i.x)]=find(i.y);
            ++m1;
            a1.push_back(i);
        }
    }
    for(int i=1;i<=n;++i) fa[i]=i;
    z=a2;
    a2.clear();
    for(auto i:z)
    {
        if(find(i.x)!=find(i.y))
        {
            fa[find(i.x)]=find(i.y);
            ++m2;
            a2.push_back(i);
        }
    }
    for(int i=1;i<=n;++i) fa[i]=i;
    z=a3;
    a3.clear();
    for(auto i:z)
    {
        if(find(i.x)!=find(i.y))
        {
            fa[find(i.x)]=find(i.y);
            ++m3;
            a3.push_back(i);
        }
    }
    // for(auto i:a1) printf("{%d,%d}",i.x,i.y);
    // printf("\n");
    // for(auto i:a2) printf("{%d,%d}",i.x,i.y);
    // printf("\n");
    // for(auto i:a3) printf("{%d,%d}",i.x,i.y);
    // printf("\n");
    for(int i=1;i<=n;++i) fa[i]=i;
    for(auto i:a2)
    {
        fa[find(i.x)]=find(i.y);
    }
    for(auto i:a3)
    {
        if(find(i.x)!=find(i.y))
        {
            fa[find(i.x)]=find(i.y);
        }
        else ++w;
    }
    // printf("%d\n",w);
    for(int i=0;i<=w;++i)
    {
        // printf("# %d:\n",i);
        solve(i);
    }
    printf("NO\n");
    return 0;
}