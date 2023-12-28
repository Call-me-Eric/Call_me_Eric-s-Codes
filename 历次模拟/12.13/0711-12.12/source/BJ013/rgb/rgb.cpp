#include<bits/stdc++.h>
#define ll long long
using namespace std;

struct Node{int u,v,c,id;};

Node pl[62505];
int n,m,num=120000000;
int cur[3],cnt[3];
int fa[255],ans[62505];
mt19937 mt_rand;

inline int root(int k){return fa[k]==k?k:fa[k]=root(fa[k]);}

int main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    srand(time(0));
    mt_rand.seed(rand());

    cin>>cur[0]>>cur[1]>>cur[2]>>m;
    n=cur[0]+cur[1]+cur[2]+1;

    for(int i=1;i<=m;i++)
    {
        char col;
        cin>>pl[i].u>>pl[i].v>>col;
        pl[i].id=i;
        if(col=='r')
            pl[i].c=0;
        if(col=='g')
            pl[i].c=1;
        if(col=='b')
            pl[i].c=2;
    }

    num/=m;

    while(num--)
    {
        for(int i=1;i<=n;i++)
            fa[i]=i;

        shuffle(pl+1,pl+m+1,mt_rand);

        for(int i=1;i<=m;i++)
        {
            int u=root(pl[i].u),v=root(pl[i].v),id=pl[i].id,col=pl[i].c;

            ans[id]=0;

            if(u!=v&&cnt[col]!=cur[col])
            {
                fa[u]=v;
                cnt[col]++;
                ans[id]=1;
            }
        }

        if(cnt[0]==cur[0]&&cnt[1]==cur[1]&&cnt[2]==cur[2])
        {
            cout<<"YES\n";
            for(int i=1;i<=m;i++)
                cout<<ans[i];
            cout<<'\n';
            exit(0);
        }
    }

    cout<<"NO\n";

    return 0;
}
