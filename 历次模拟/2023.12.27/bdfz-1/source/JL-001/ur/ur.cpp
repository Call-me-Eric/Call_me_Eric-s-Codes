#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
#include<cmath>
using namespace std;
using ld=long double;
const ld eps=1e-8;
struct p{
    ld x,y;
    bool operator<(const p&a)const{
        if(fabs(x-a.x)<eps)return y+eps<a.y;
        return x+eps<a.x;
    }
};
p operator+(const p&a,const p&b){
    return p{a.x+b.x,a.y+b.y};
}
p flip(const p&a){
    return p{-a.x,-a.y};
}
p o[1000];
map<p,int>vis;
const ld pie=acosl(-1);
p f[1<<20],g[1<<20];
map<p,int>bit[40];
int ans[2000000];
vector<int>d[1000000];
int main(){
    freopen("ur.in","r",stdin);freopen("ur.out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int n,k;
    cin>>n>>k;
    if(n==k){
        for(int i=1;i<=n;i++)cout<<1;return 0;
    }
    if(k==0){
        for(int i=1;i<=n;i++)cout<<0;return 0;
    }
    if(n<=40){
        for(int i=0;i<n;i++) o[i]=p{cosl(2*pie/n*i),sinl(2*pie/n*i)};
        int b=n/2;
        for(int s=1;s<(1<<b);s++){
            int i=__builtin_ctz(s);
            f[s]=f[s-(1<<i)]+o[i];
        }
        for(int s=1;s<(1<<(n-b));s++){
            int i=__builtin_ctz(s);
            g[s]=g[s-(1<<i)]+o[i+b];
        }
        for(int s=0;s<(1<<b);s++) {
            vis[f[s]]++;
            bit[__builtin_popcount(s)][f[s]]=s;
            // if(s==7){
            //     // cerr<<"?? "<<f[s].x<<" "<<f[s].y<<endl;
            //     // cerr<<"?? "<<bit[3].count(p{1,0})<<" "<<(f[s]<p{1,0})<<" "<<(p{1,0}<f[s])<<endl;
            // }
        }
        int res=0;
        for(int s=0;s<(1<<(n-b));s++){
            if(vis.count(flip(g[s]))) res+=vis[flip(g[s])];
        }
        cerr<<res<<'\n';
        // k=5;
        for(int K=k;K>=1;K--){
            // cerr<<"?? "<<K<<endl;
            for(int s=0;s<(1<<(n-b));s++){
                int t=__builtin_popcount(s);
                if(K>=t&&bit[K-t].count(flip(g[s]))){
                    int u=bit[K-t][flip(g[s])];
                    cerr<<K<<endl;
                    // cerr<<"?? "<<u<<" "<<t<<" "<<s<<" | "<<flip(g[s]).x<<" "<<flip(g[s]).y<<" | "<<f[u].x<<" "<<f[u].y<<endl;
                    for(int i=0;i<b;i++) cout<<((u>>i)&1);
                    for(int i=0;i<n-b;i++) cout<<((s>>i)&1);
                    cout<<'\n';return 0;
                }
            }
        }
        for(int i=0;i<n;i++) cout<<0;return 0;
    }
    // for(int )
    // vector<int>
    vector<pair<int,int>>p;int lim=n;
    for(int i=2;i*i<=lim;i++){
        if((lim%i==0)){
            int tik=0;
            while(lim%i==0) lim/=i,tik++;
            p.push_back(make_pair(i,tik));
        }
    }
    if(lim>1) p.push_back(make_pair(lim,1));
    if(p.size()==1){
        if(p[0].second==1){
            for(int i=0;i<n;i++) cout<<0;return 0;
        }
        int tim=k/p[0].first;
        for(int i=0;i<tim;i++){
            int cur=i,step=n/p[0].first;
            for(int j=0;j<p[0].first;j++){
                ans[cur]=1;cur+=step;
            }
        }
        for(int i=0;i<n;i++) cout<<ans[i];return 0;
    }
    if(p.size()==2){
        // vector<int> 
        int base=p[0].first*p[1].first;
        for(int i=0;i<n/(base);i++){
            int step=n/(base);
            int cur=i;
            for(int j=0;j<base;j++){
                d[i].push_back(cur);cur+=step;
            }
        }
        int mx=0,pa=0,pb=0,pc=0,ext=n/base;
        for(int a=0;a<p[1].first;a++){
            for(int b=0;b<p[0].first;b++){
                int sum=a*p[0].first+b*p[1].first;
                if(sum>k||ext<a+b) continue;
                int c=min(ext-a-b,(k-sum)/(base));
                int cur=c*base+sum;
                if(cur>mx) mx=cur,pa=a,pb=b,pc=c;
            }
        }
        for(int i=0;i<pa;i++){
            int step=base/p[0].first;
            int cur=0;
            for(int j=0;j<p[0].first;j++){
                ans[d[i][cur]]=1;cur+=step;
            }
        }
        for(int i=pa;i<pa+pb;i++){
            int step=base/p[1].first;
            int cur=0;
            for(int j=0;j<p[1].first;j++){
                ans[d[i][cur]]=1;cur+=step;
            }
        }
        for(int i=pa+pb;i<pa+pb+pc;i++){
            for(int z:d[i]) ans[z]=1;
        }
        for(int i=0;i<n;i++) cout<<ans[i];
        return 0;
    }
}
