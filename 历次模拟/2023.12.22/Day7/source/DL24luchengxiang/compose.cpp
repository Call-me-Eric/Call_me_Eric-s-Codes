#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define int ll
#define endl '\n'
#define gc cin.get
#define pc cout.put
const int N=2e5+5;
const int M=1e5+5;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int base=13131;
inl int read(){
    int x=0,f=1;char c=gc();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=gc();}
    return x*f;
}
inl void write(int x){
    if(x<0){pc('-');x=-x;}
    if(x>9)write(x/10);
    pc(x%10+'0');
}
inl void writei(int x){write(x);pc(' ');}
inl void writel(int x){write(x);pc('\n');}
int n,k,num,q,a[15][N],ls[N],rs[N],opt[N],ans[N],res[N],qid;
vector<pair<int,int>>v[N];
vector<int>G;
inl int dfs(int x,int p){
    if(x<=k)return a[x][p];
    if(ans[x])return ans[x];
    G.push_back(x);
    if(!opt[x])return ans[x]=max(dfs(ls[x],p),dfs(rs[x],p));
    return ans[x]=min(dfs(ls[x],p),dfs(rs[x],p));
}
signed main(){
    freopen("compose.in","r",stdin);
    freopen("compose.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    n=read();k=num=read();q=read();G.reserve(n);
    for(int i=1;i<=k;i++)
        for(int j=1;j<=n;j++)
            a[i][j]=read();
    for(int i=1;i<=q;i++){
        int op=read(),x=read(),y=read();
        if(op==1)ls[++num]=x,rs[num]=y,opt[num]=0;
        if(op==2)ls[++num]=x,rs[num]=y,opt[num]=1;
        if(op==3)v[y].push_back({x,++qid});
    }
    for(int i=1;i<=n;i++){
        for(auto j:G)ans[j]=0;G.clear();
        for(auto j:v[i])res[j.second]=dfs(j.first,i);
    }
    for(int i=1;i<=qid;i++)cout<<res[i]<<endl;
    return 0;
}