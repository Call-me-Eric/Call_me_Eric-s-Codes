#include <bits/stdc++.h>

using namespace std;

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;
using db=double;
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

const int N=1e6+10,MX=1e6;
const db pi=acos(-1);

int n,vis[N];

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

int p[N],pc,val[N];

void dfs1(int x,int sum){
    if(x>pc) {vis[sum]=1;return;}
    for(int i=0;i<=val[x];i++)
        dfs1(x+1,sum+p[x]*i);
}

void dfs(int x,int sum){
    if(x>pc){
        if(sum==n) dfs1(1,0);
        return;
    }
    for(int i=0;sum+i*p[x]<=n;i++)
        val[x]=i,dfs(x+1,sum+p[x]*i);
}

int main(){
    n=rdi();
    for(auto v:get_fac(n))
        p[++pc]=v;
    dfs(1,0);
    for(int i=0;i<=n;i++)
        if(vis[i]) cout<<i<<'\n';
    return 0;
}
