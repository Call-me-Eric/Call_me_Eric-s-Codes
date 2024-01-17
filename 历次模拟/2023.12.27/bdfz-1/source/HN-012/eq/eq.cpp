#include <bits/stdc++.h>

using namespace std;

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;
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

const int N=710,MOD=998244353;

int n,q;

i64 qpow(i64 x,i64 y=MOD-2){
    i64 res=1;
    while(y){
        if(y&1) (res*=x)%=MOD;
        (x*=x)%=MOD;y>>=1;
    }
    return res;
}

using arr=array<int,N>;
using mat=array<arr,N>;
arr ini[N];
pair<int,arr> mod[N];

int add(int x,int y){
    return (x+=y)>=MOD?x-MOD:x;
}
int sub(int x,int y){
    return (x-=y)<0?x+MOD:x;
}
int mul(int x,int y){
    return (i64)x*y%MOD;
}

namespace BF{
    arr res[N];
    int res_t[N];

#define ls (nw<<1)
#define rs (nw<<1|1)
#define mid ((l+r)>>1)
    vector<arr> vec[N*4];
    void ins(int nw,int l,int r,int x,int y,const arr &v){
        if(x<=l&&r<=y) {vec[nw].pb(v);return;}
        if(x<=mid) ins(ls,l,mid,x,y,v);
        if(y>mid) ins(rs,mid+1,r,x,y,v);
    }

    void solve(int nw,int l,int r,mat &ma){
        auto ins = [&](mat &a,arr v){
            for(int i=0;i<n;i++){
                if(!v[i]) continue;
                if(a[i][i]){
                    int mu=qpow(a[i][i])*v[i]%MOD;
                    for(int j=i;j<=n;j++)
                        v[j]=sub(v[j],mul(a[i][j],mu));
                }
                else {a[i]=v;return 0;}
            }
            if(!v[n]) return 1;
            else return 2;
        };

        mat bk=ma;
        int fl=0;
        for(auto &cur:vec[nw])
            fl|=1<<ins(ma,cur);
        if(fl&4){
            for(int i=l;i<=r;i++) res_t[i]=-1;
        }
        else if(l==r){
            for(int i=0;i<n;i++){
                if(!ma[i][i]){
                    assert(!ma[i][n]);
                    res_t[l]=-2;break;
                }
            }
            if(!res_t[l]){
                for(int i=n-1;i>=0;i--){
                    res[l][i]=mul(qpow(ma[i][i]),ma[i][n]);
                    for(int j=i-1;j>=0;j--)
                        ma[j][n]=sub(ma[j][n],mul(ma[j][i],res[l][i]));
                }
            }
        }
        else{
            solve(ls,l,mid,ma);
            solve(rs,mid+1,r,ma);
        }
        ma=bk;
    }
#undef ls
#undef rs
#undef mid
    int lst[N];
    mat ma;
    void solve(){
        for(int i=1;i<=q;i++){
            int x=mod[i].fi;
            ins(1,0,q,lst[x],i-1,ini[x]);
            lst[x]=i,ini[x]=mod[i].se;
        }
        for(int i=0;i<n;i++)
            ins(1,0,q,lst[i],q,ini[i]);
        solve(1,0,q,ma);
        for(int i=0;i<=q;i++){
            if(res_t[i]==-2) puts("Many");
            else if(res_t[i]==-1) puts("No");
            else{
                for(int j=0;j<n;j++)
                    cout<<res[i][j]<<' ';
                cout<<'\n';
            }
        }
    }
}

namespace SUB5{
    using arr1=array<int,N*2>;
    arr1 b[N];
    void ins(int id,arr ar){
        arr1 v;v.fill(0);
        for(int i=0;i<=n;i++) v[i]=ar[i];
        v[id+n+1]=1;
        for(int i=0;i<n;i++){
            if(!v[i]) continue;
            if(b[i][i]){
                int mu=qpow(b[i][i])*v[i]%MOD;
                for(int j=i;j<=2*n;j++)
                    v[j]=sub(v[j],mul(b[i][j],mu));
            }
            else {b[i]=v;return;}
        }
    }
    void replace(int id,arr v){
        arr bs;bs.fill(0);
        for(int i=0;i<n;i++){
            int mu=mul(v[i],qpow(b[i][i]));
            for(int j=0;j<n;j++){
                v[j]=sub(v[j],mul(b[i][j],mu));
                bs[j]=add(bs[j],mul(b[i][j+n+1],mu));
            }
        }
        int mu=qpow(bs[id]);
        for(int i=0;i<n;i++){
            if(i!=id) bs[i]=mul(mu,sub(0,bs[i]));
            else bs[i]=mu;
        }
        int old=ini[id][n];ini[id]=v;
        for(int i=0;i<n;i++){
            mu=b[i][id+n+1];
            b[i][n]=sub(b[i][n],mul(b[i][id+n+1],old));
            b[i][id+n+1]=0;
            for(int j=0;j<n;j++){
                int v1=mul(mu,bs[j]);
                b[i][j+n+1]=add(b[i][j+n+1],v1);
                b[i][n]=add(b[i][n],mul(v1,ini[j][n]));
            }
        }
    }
    void get_ans(){
        arr res;
        static arr1 bk[N];
        copy(b,b+n,bk);
        for(int i=n-1;i>=0;i--){
            res[i]=mul(qpow(b[i][i]),b[i][n]);
            for(int j=i-1;j>=0;j--)
                b[j][n]=sub(b[j][n],mul(b[j][i],res[i]));
        }
        copy(bk,bk+n,b);
        for(int i=0;i<n;i++)
            cout<<res[i]<<' ';
        cout<<'\n';
    }
    void solve(){
        for(int id=0;id<n;id++)
            ins(id,ini[id]);
        get_ans();
        for(int i=1;i<=q;i++){
            replace(mod[i].fi,mod[i].se);
            get_ans();
        }
    }
}

int main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    n=rdi(),q=rdi();
    for(int i=0;i<n;i++)
        for(int j=0;j<=n;j++)
            ini[i][j]=rdi();
    for(int i=1;i<=q;i++){
        mod[i].fi=rdi()-1;
        for(int j=0;j<=n;j++)
            mod[i].se[j]=rdi();
    }
    BF::solve();
    // SUB5::solve();
    return 0;
}
