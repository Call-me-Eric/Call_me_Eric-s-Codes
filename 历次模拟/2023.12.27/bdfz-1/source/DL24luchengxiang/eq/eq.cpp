#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define int ll
#define endl '\n'
#define gc cin.get
#define pc cout.put
const int N=1e3+5;
const int M=1e7+5;
const int inf=0x7fffffff;
const int mod=998244353;
const int base=13131;
inl int read(){
    int x=0,f=1;char c=gc();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=gc();}
    return x*f;
}
int n,q,a,b,ans[N];
inl int gcd(int a,int b){return !b?a:gcd(b,a%b);}
inl void exgcd(int &x,int &y,int a,int b){
    if(!b)return x=1,y=0,void();
    exgcd(y,x,b,a%b);y-=(a/b)*x;
}
inl void solve(int a,int b){
    int x,y;
    exgcd(x,y,a,mod);
    x=(x%mod*b%mod+mod)%mod;
    cout<<x<<endl;
}
signed main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    n=read();q=read();
    a=read(),b=read();
    solve(a,b);
    while(q--){
        int op=read();
        a=read(),b=read();
        solve(a,b);
    }
    return 0;
}