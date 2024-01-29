#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,tot,w1,w2,w3;
bool h[N];
vector<int> a[N];
void dfs(int x)
{
    ++w1,w2+=a[x].size();
    w3=max(w3,(int)a[x].size());
    h[x]=true;
    for(auto i:a[x])
    {
        if(h[i]) continue;
        dfs(i);
    }
}
int main()
{
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    ll s=0;
    int w=0;
    for(int i=1;i<=n;++i)
    {
        if(h[i]) continue;
        w1=w2=w3=0;
        dfs(i);
        w2/=2;
        if(w1==w2+1)
        {
            if(w3<=2) s+=(ll)w1*(w1+1)/2;
            else if(w1==4) w+=3;
            else
            {
                printf("-1");
                return 0;
            }
        }
        else if(w1==w2&&w3<=2)
        {
            w+=w1;
        }
        else
        {
            printf("-1");
            return 0;
        }
    }
    if(w==0) printf("0 %lld",s);
    else printf("1 %d",w);
    return 0;
}