#include<bits/stdc++.h>
#define abs(x) (x>0?x:-(x))
#define int long long 
using namespace std;
int n,k;
bool b[41];
array<bool,40>a;
int p1,p2;
double x[41],y[41];
int maxx;
constexpr double eps=1e-11;
constexpr double pi=acos(-1);
void dfs1(int t,int num){
    if(num>k)return ;
    if(t==n+1){
        double xs=0,ys=0;
        for(int i=1;i<=n;++i)xs+=a[i]*x[i],ys+=a[i]*y[i];
        if(abs(xs)<eps and abs(ys)<eps){
            if(num>maxx){maxx=num;for(int i=1;i<=n;++i)b[i]=a[i];}
        }
        return ;
    }
    a[t]=1;dfs1(t+1,num+1);
    a[t]=0;dfs1(t+1,num);
    return ;
}
map<pair<int,int>,array<bool,40> >mp;
void dfs2(int t,int num){
    if(t==p1+1){
        double xs=0,ys=0;
        for(int i=1;i<=p1;++i)xs+=a[i]*x[i],ys+=a[i]*y[i];
        mp[{xs*1000000000ll,ys*1000000000ll}]=a;
        return ;
    }
    a[t]=1;dfs2(t+1,num+1);
    a[t]=0;dfs2(t+1,num);
    return ;
}
void dfs3(int t,int num){
    if(t==n+1){
        double xs=0,ys=0;
        for(int i=p1+1;i<=n;++i)xs+=a[i]*x[i],ys+=a[i]*y[i];
        int xxs=-xs*1000000000ll,yys=-ys*1000000000ll;
        if(mp.count({xxs,yys})){
            array<bool,40>tp=mp[{xxs,yys}];
            for(int i=1;i<=p1;++i)num+=tp[i];
            if(num>maxx and num<=k){
                for(int i=1;i<=p1;++i)b[i]=tp[i];
                for(int i=p1+1;i<=n;++i)b[i]=a[i];
                maxx=num;
                return ;
            }
        }
        return ;
    }
    a[t]=1;dfs3(t+1,num+1);
    a[t]=0;dfs3(t+1,num);
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    cin>>n>>k;
    if(n==k){
        for(int i=1;i<=n;++i)cout<<1;
        cout<<'\n';
        return 0;
    }else if(k<=1){
        for(int i=1;i<=n;++i)cout<<0;
        cout<<'\n';
        return 0;
    }else if(n<=20){
        for(int i=1;i<=n;++i){
            x[i]=cos(2*pi*i/n);
            y[i]=sin(2*pi*i/n);
        }
        dfs1(1,0);
        for(int i=1;i<=n;++i)cout<<b[i];
        cout<<'\n';
        return 0;
    }else if(n<=36){
        for(int i=1;i<=n;++i){
            x[i]=cos(2*pi*i/n);
            y[i]=sin(2*pi*i/n);
        }
        p1=n/2,p2=n-p1;
        dfs2(1,0);
        dfs3(p1+1,0);
        for(int i=1;i<=n;++i)cout<<b[i];
        cout<<'\n';
        return 0;
    }else for(int i=1;i<=n;++i)cout<<0;
    cout<<'\n';
    return 0;
}