/*
    All tradgedy erased,I see only wonders.
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
#define int long long
int n,m;
const int N=2e5+1000;
vector<int>v[N];
#define rep(i,l,r) for(int i=l;i<=r;i++)
int deg[N];
int vis[N];
vector<int>p;
void paint(int x){
    if(vis[x]) return ;
    vis[x]=1;p.push_back(x);
    for(auto y:v[x]) paint(y);
}
int ans=0;
int32_t main(){
    freopen("li.in","r",stdin);freopen("li.out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    rep(i,1,m){
        int x,y;cin>>x>>y;
        v[x].push_back(y),v[y].push_back(x);
        deg[x]++,deg[y]++;
    }
    rep(i,1,n){
        if(deg[i]>3) cout<<"-1",exit(0);
    }
    int all=0;

    rep(i,1,n){
        if(!vis[i]){
            p.clear();
            paint(i);
            int e=0,mx=0;
            for(int x:p) mx=max(mx,deg[x]);
            for(int x:p) e+=v[x].size();
            e/=2;
            if(e>3&&mx>=3){
                cout<<"-1",exit(0);
            }
            if(e==3&&mx==3){
                all+=3;continue;
            }
            if(p.size()==e){
                all+=p.size();continue;
            }
            ans+=1ll*p.size()*(p.size()+1)/2;
        }
    }
    if(all==0){
        cout<<0<<" "<<ans<<'\n';
    }else{
        cout<<1<<" "<<all<<'\n';
    }
}