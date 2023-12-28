#include <bits/stdc++.h>

using namespace std;

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;
using db=long double;
using vi=vector<int>;
using pii=pair<int,int>;

template<typename T>
T read(){
    T x=0,f=0;char c=getchar();
    while(!isdigit(c)) f|=(c=='-'),c=getchar();
    while(isdigit(c)) x=x*10+(c-'0'),c=getchar();
    return f?-x:x;
}

#define rdi read<int>
#define rdi64 read<i64>
#define fi first
#define se second
#define pb push_back

const int N=1e6+10;

int n,k;
int sel[N];

namespace SUB12{
    bool check(){
        return k<=1||k==n;
    }
    void solve(){
        if(k<=1) fill(sel,sel+n,0);
        else fill(sel,sel+n,1);
    }
}

vi get_fac(int n){
    vi ret;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            while(n%i==0) n/=i;
            ret.pb(i);
        }
    }
    if(n>1) ret.pb(n);
    return ret;
}

namespace SUB34{
    bool check(){
        return n<=36;
    }

    const int MX=1e6;
    const db pi=acosl(-1);
    struct vec{
        db x,y;
        vec operator+ (const vec &rhs) const{
            return {x+rhs.x,y+rhs.y};
        }
    }p[N];
    map<pii,vi> mp;
    i64 res[N];

    int to_int(db x) {return round(x*MX);}

    void solve(){
        memset(res,-1,sizeof(res));
        for(int i=0;i<n;i++)
            p[i]={cos(2*pi*i/n),sin(2*pi*i/n)};

        int mid=n/2;
        for(int i=0;i<(1<<mid);i++){
            vec sum{0,0};
            for(int j=0;j<mid;j++)
                if(i>>j&1) sum=sum+p[j];
            mp[{to_int(sum.x),to_int(sum.y)}].pb(i);
        }
        for(int i=0;i<(1<<(n-mid));i++){
            vec sum{0,0};
            for(int j=0;j<n-mid;j++)
                if(i>>j&1) sum=sum+p[j+mid];
            auto it=mp.find({-to_int(sum.x),-to_int(sum.y)});
            if(it!=mp.end()){
                for(auto j:it->se){
                    i64 stat=(i64)i<<mid|j;
                    int c=__builtin_popcountll(stat);
                    if(!~res[c]) res[c]=stat;
                }
            }
        }
        for(int i=k;i>=0;i--){
            if(~res[i]){
                for(int j=0;j<n;j++)
                    sel[j]=(res[i]>>j&1);
                return;
            }
        }
    }
}

namespace SUB57{
    bool check(){
        return get_fac(n).size()<=1;
    }
    void solve(){
        int p=get_fac(n)[0];
        k=k/p*p;
        for(int i=0;i<n;i++)
            if(i%(n/p)<k/p) sel[i]=1;
            else sel[i]=0;
    }
}

namespace SUB68{
    int pr[N],pc;
    int pre[N],f[N];
    void solve(){
        for(auto x:get_fac(n))
            pr[++pc]=x;

        f[0]=1;
        for(int i=1;i<=pc;i++)
            for(int j=pr[i];j<=n;j++)
                if(!f[j]&&f[j-pr[i]])
                    f[j]=1,pre[j]=i;
        
        while(!f[k]||!f[n-k]) --k;
        cerr<<k<<endl;
        static int cnt[N];
        for(int x=k;x;x-=pr[pre[x]]) ++cnt[pre[x]];
        for(int i=1;i<=pc;i++){
            int p=pr[i];
            for(int j=0;j<n/p&&cnt[i];j++){
                bool fl=1;
                for(int k=j;k<n;k+=n/p)
                    fl&=!sel[k];
                if(fl){
                    --cnt[i];
                    for(int k=j;k<n;k+=n/p)
                        sel[k]=1;
                }
            }
        }
    }
}

namespace checker{
    using namespace SUB34;
    bool check(){
        for(int i=0;i<n;i++)
            p[i]={cos(2*pi*i/n),sin(2*pi*i/n)};
        vec res{0,0};
        for(int i=0;i<n;i++)
            if(sel[i]) res=res+p[i];
        return fabs(res.x)<1e-5&&fabs(res.y)<1e-5;
    }
}

int main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    n=rdi(),k=rdi();
    if(SUB12::check()) SUB12::solve();
    else if(SUB34::check()) SUB34::solve();
    else SUB68::solve();
    assert(checker::check());
    for(int i=0;i<n;i++) cout<<sel[i];
    cout<<'\n';
    return 0;
}
