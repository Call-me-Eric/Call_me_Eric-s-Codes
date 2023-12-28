#include<bits/stdc++.h>
#define For(i,l,r) for(register int i=(l);i<=(r);++i)
#define For_down(i,r,l) for(register int i=(r);i>=(l);--i)
using namespace std;
constexpr int n_MAX=30000+5,S=30,mod=998244353;
void add(int &x,const int y){((x+=y)>=mod)&&(x-=mod);}
map<vector<int>,int> mp;
vector<int> vec[n_MAX];
int n;
void DFS(const int s,const vector<int> a)
{
    mp[a]=(++n),vec[n]=a;
    if(a.empty())
    {
        For(i,1,S) DFS(i,(vector<int>){i});
    }
    else
    {
        For(i,1,a.back())
        {
            vector<int> b=a;
            b.push_back(i);
            if((s+i)<=S) DFS(s+i,b);
        }
    }
}
vector<int> empty,a,b;
vector<int> nex[n_MAX];
int F[S][n_MAX];
int main()
{
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(nullptr);
    DFS(0,empty);
    int la; cin>>la,a.resize(la);
    For(i,0,la-1) cin>>a[i];
    const int s=mp[a];
    int lb; cin>>lb,b.resize(lb);
    For(i,0,lb-1) cin>>b[i];
    const int t=mp[b];
    For(u,1,n)
    {
        a=vec[u];
        const int len=a.size();
        For(i,0,len-1)
        {
            b=a,++b[i];
            if(i&&(b[i-1]<b[i])) continue;
            if(mp.count(b)) nex[u].push_back(mp[b]);
        }
        b=a,b.push_back(1);
        if(mp.count(b)) nex[u].push_back(mp[b]);
        For(i,0,len-1)
        {
            b=a,--b[i];
            if(i==(len-1))
            {
                if(!b.back()) b.pop_back();
                nex[u].push_back(mp[b]);
            }
            else
            {
                if(b[i]<b[i+1]) continue;
                nex[u].push_back(mp[b]);
            }
        }
    }
    int q,k; cin>>q>>k,F[0][s]=1;
    For(i,1,k)
    {
        For(u,1,n) for(const int v:nex[u]) add(F[i][v],F[i-1][u]);
    }
    cout<<F[k][t]<<'\n';
    return 0;
}