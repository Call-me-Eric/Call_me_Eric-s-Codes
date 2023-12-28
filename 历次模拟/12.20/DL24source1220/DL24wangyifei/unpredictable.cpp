#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
    long long xr=0,F=1; char cr;
    while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
    while(cr>='0'&&cr<='9')
        xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
    return xr*F;
}
#define int long long
const int N=1e6+15,mod=998244353;
const int Mod=1e9+7,base1=131,base2=133;
int n,jc[N];
string s[N];
vector<int> w[N];
struct Hash
{
    int h1=0; ulong h2=0;
    friend Hash operator *(const Hash &x,const Hash &y) {return {x.h1*y.h1%Mod,x.h2*y.h2};}
    friend Hash operator +(const Hash &x,const Hash &y) {return {(x.h1+y.h1)%Mod,x.h2+y.h2};}
    friend Hash operator -(const Hash &x,const Hash &y) {return {(x.h1-y.h1+Mod)%Mod,x.h2-y.h2};}
    friend bool operator ==(const Hash &x,const Hash &y) {return x.h1==y.h1&&x.h2==y.h2;}
    friend bool operator <(const Hash &x,const Hash &y) 
    {
        if(x.h1!=y.h1) return x.h1<y.h1;
        else return x.h2<y.h2;
    }
} pw[N];
struct HashMap
{
    const int mmod=1e6-7;
    struct node{int len,w;Hash x;};
    vector<node> e[N];
    il void add(int len,Hash x,int k)
    {
        int id=x.h1%mmod;
        for(auto &[Len,w,X]:e[id]) if(Len==len&&x==X) {(w+=k)%=mod;return;}
        e[id].push_back({len,k,x});
    }
    il int ask(int len,Hash x)
    {
        int id=x.h1%mmod;
        for(auto &[Len,w,X]:e[id]) if(Len==len&&x==X) return w;
        return 0;
    }
}mp,Ct;
vector<Hash> h[N];
il Hash get(int id,int l,int r)
{
    return (h[id][r]-h[id][l-1]*pw[r-l+1]);
}
int f[N],nx[N];
vector<int> nxt[N];
il int solve(int id)
{
    int res=0;
    for(int j=1;j<s[id].size();j++) 
    {
        Ct.add(s[id].size()-j,get(id,j,s[id].size()-1),-1);
        mp.add(s[id].size()-j,get(id,j,s[id].size()-1),
            -(w[id][s[id].size()-j]-(nxt[id][j]<s[id].size()?w[id][s[id].size()-nxt[id][j]]:0)+mod));
    }
    for(int now=0,i=2;i<s[id].size();i++)
    {
        while(now&&s[id][i]!=s[id][now+1]) now=nx[now];
        if(s[id][i]==s[id][now+1]) now++;
        nx[i]=now;
    }
    for(int i=1;i<s[id].size();i++) 
    {
        f[i]=Ct.ask(i,get(id,1,i));
        (res+=(w[id][i]-w[id][nx[i]]+mod)*f[i]%mod+mp.ask(i,get(id,1,i)))%=mod;
    }
    for(int j=1;j<s[id].size();j++) 
    {
        Ct.add(s[id].size()-j,get(id,j,s[id].size()-1),1);
        mp.add(s[id].size()-j,get(id,j,s[id].size()-1),
            w[id][s[id].size()-j]-(nxt[id][j]<s[id].size()?w[id][s[id].size()-nxt[id][j]]:0)+mod);
    }
    return (res+mod)%mod;
}
int mxlen;
signed main()
{
    freopen("unpredictable.in","r",stdin);
    freopen("unpredictable.out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s[i]; s[i]=" "+s[i];
        w[i].resize(s[i].size()),h[i].resize(s[i].size());
        for(int j=1;j<s[i].size();j++) cin>>w[i][j];
        for(int j=1;j<s[i].size();j++) h[i][j]=h[i][j-1]*Hash{base1,(ulong)base2}+Hash{s[i][j]-'a',ulong(s[i][j]-'a')};
        mxlen=max(mxlen,(int)s[i].size());
    }
    jc[0]=1,pw[0]={1,1}; int ans=0;
    for(int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
    for(int i=1;i<=mxlen;i++) pw[i]=pw[i-1]*Hash{base1,(ulong)base2};
    for(int id=1;id<=n;id++)
    {
        nxt[id].resize(s[id].size());
        nxt[id][s[id].size()-1]=s[id].size();
        for(int now=s[id].size(),i=s[id].size()-2;i;i--)
        {
            while(now<s[id].size()&&s[id][i]!=s[id][now-1]) now=nxt[id][now];
            if(s[id][i]==s[id][now-1]) now--;
            nxt[id][i]=now;
        }
        for(int j=1;j<s[id].size();j++) 
        {
            Ct.add(s[id].size()-j,get(id,j,s[id].size()-1),1);
            mp.add(s[id].size()-j,get(id,j,s[id].size()-1),
                w[id][s[id].size()-j]-(nxt[id][j]<s[id].size()?w[id][s[id].size()-nxt[id][j]]:0)+mod);
        }
    }
    // cout<<get(1,3,3).h2<<" "<<get(4,3,3).h2<<" "<<mp[1][{0,0}]<<endl;
    for(int i=1;i<=n;i++) (ans+=solve(i)*jc[n-1]%mod)%=mod;
    cout<<ans<<endl;
    return 0;
}
/*
4
aba 1 2 3
ab 1 2
aa 1 2
aaa 1 2 3
*/