#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define int ll
#define endl '\n'
#define gc cin.get
#define pc cout.put
const int N=1e6+5;
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
int n,k,x,primes[N],c[N],num,rx,ry,ans[N];
inl void dfs(int x,int ans){
    if(x>num){
        if(ans==1)return;
        int x=ans,y=k/ans;
        if(x*y>rx*ry)rx=y,ry=x;
        return;
    }
    for(int i=1;i<=c[x];i++){
        dfs(x+1,ans);
        ans*=primes[x];
    }
}
signed main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    n=x=read();k=read();
    for(int j=2;j*j<=n;j++){
        if(x%j)continue;
        primes[++num]=j;c[num]=1;
        while(!(x%j))x/=j,c[num]++;
    }
    if(x^1)primes[++num]=x,c[num]=2;
    dfs(1,1);
    for(int i=1;i<=rx;i++)
        for(int j=i;j<=n;j+=n/ry)
            ans[j]=1;
    for(int i=1;i<=n;i++)cout<<ans[i];
    return 0;
}