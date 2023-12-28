#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
#include <stack>
#include <cmath>
#include <set>
#include <cstdlib>
#include <unordered_map>
#include <random>
#include <chrono>
#include <ctime>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
#define mp make_pair
#define pb push_back
#define debug() cout<<"qwq"<<endl
#define mem(i,a) memset(i,a,sizeof(i))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
#define i128 __int128
#define pii pair<int,int>
const db eps=1e-10;
const ll INF = 1e18;
const int siev =1000000+5;
const int inf = 0x3f3f3f3f;
const int DMAX = 100000 + 10;
const int G=3;
const int invG=332748118;
const double PI=acos(-1.0);
const ll MOD = 998244353;
const ll LMOD = 1000000007;
const int hmod = 202010923;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template<class T> inline void print(T x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    int a[20];
    int cnt=0;
    do{
        a[++cnt]=x%10;
        x/=10;
    }while(x>0);
    for(int i=cnt;i>=1;i--){
        putchar(a[i]+'0');
    }
    putchar('\n');
    // puts("");
}
template<class T> inline void read(T &x){
    x=0;
    T f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch<='9' && ch>='0'){
        x=x*10+(ch-'0');
        ch=getchar();
    }
    x*=f;
}
int T;
int n;
ll a[DMAX];
ll dp[DMAX];
ll opt[DMAX];
ll solve(ll x,ll y){
    if(x+1>y-1){
        return 0;
    }
    ll tot=(y-1-(x+1))+1;
    return tot*(tot+1)/2;
}
struct SegTree{
    int l,r;
    int id;
};
SegTree tr[DMAX<<2];
void build(int p,int l,int r){
    tr[p].l=l,tr[p].r=r;
    tr[p].id=0;
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
}
struct Segment{
    ll k,b;
};
Segment seg[DMAX*90];
int cnt=0;
struct node{
    ll val,pos;
    bool operator <(const node &p) const{
        if(val==p.val){
            return pos<p.pos;
        }
        return val<p.val;
    }
};
node nde[DMAX];
int ls[DMAX*90],rs[DMAX*90];
int tag[DMAX*90],qwq=0;
ll calc(ll lab,ll x){
    return x*seg[lab].k+seg[lab].b;
}
void insert(int &p,int l,int r,int val){
    if(!p){
        p=++qwq;
    }
    if(!tag[p]){
        tag[p]=val;
        return ;
    }
    if(l==r){
        if(calc(val,l)>calc(tag[p],l)){
            tag[p]=val;
        }
        return ;
    }
    int mid=(l+r)>>1;
    ll temp=calc(val,mid),temp1=calc(tag[p],mid);
    if(seg[val].k>seg[tag[p]].k){
        if(temp>=temp1){
            insert(ls[p],l,mid,tag[p]);
            tag[p]=val;
        }
        else{
            insert(rs[p],mid+1,r,val);
        }
    }
    else if(seg[val].k<seg[tag[p]].k){
        if(temp>=temp1){
            insert(rs[p],mid+1,r,tag[p]);
            tag[p]=val;
        }
        else{
            insert(ls[p],l,mid,val);
        }
    }
    else if(seg[val].b>seg[tag[p]].b){
        tag[p]=val;
        return ;
    }
}
void modify(int p,int x,int val){
    insert(tr[p].id,1,n,val);
    if(tr[p].l==tr[p].r){
        return ;
    }
    int mid=(tr[p].l+tr[p].r)>>1;
    if(x<=mid){
        modify(p<<1,x,val);
    }
    else{
        modify(p<<1|1,x,val);
    }
}
ll query1(int p,int l,int r,int val){
    if(!p){
        return -INF;
    }
    if(l==r){
        return calc(tag[p],val);
    }
    ll res=calc(tag[p],val);
    int mid=(l+r)>>1;
    if(val<=mid){
        res=max(res,query1(ls[p],l,mid,val));
    }
    else{
        res=max(res,query1(rs[p],mid+1,r,val));
    }
    return res;
}
ll query(int p,int l,int r,int val){
    if(l<=tr[p].l && tr[p].r<=r){
        return query1(tr[p].id,1,n,val);
    }
    int mid=(tr[p].l+tr[p].r)>>1;
    ll res=-INF;
    if(l<=mid){
        res=max(res,query(p<<1,l,r,val));
    }
    if(r>mid){
        res=max(res,query(p<<1|1,l,r,val));
    }
    return res;
}
int main(){
    read(T);
    while(T--){
        read(n);
        for(int i=1;i<=n;i++){
            read(a[i]);
            nde[i]=node{a[i],i};
        }
        sort(nde+1,nde+n+1);
        for(int i=1;i<=n;i++){
            dp[i]=-INF;
        }
        dp[0]=0;
        qwq=0,cnt=0;
        build(1,1,n);
        seg[0]=Segment{0,-INF};
        for(int i=1;i<=n;i++){
            ll x=nde[i].pos;
            ll res=query(1,1,x,x);
            res=(res-(x*x-x)/2+nde[i].val);
            res=max(res,dp[0]-solve(0,x)+nde[i].val);
            dp[x]=res;
            seg[++cnt]=Segment{x,-(x*x+x)/2+dp[x]};
            modify(1,x,cnt);
        }
        ll ans=-1e18;
        for(int i=0;i<=n;i++){
            ans=max(ans,dp[i]-solve(i,n+1));
        }
        for(int i=0;i<=qwq;i++){
            tag[i]=0,ls[i]=0,rs[i]=0;
        }
        for(int i=0;i<=cnt;i++){
            seg[i]=Segment{0,-INF};
        }
        print(ans);
    }
    return 0;
}