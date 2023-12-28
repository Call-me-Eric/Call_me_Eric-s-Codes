#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
typedef unsigned long long ull;
const int maxn=1e6+10,mod=998244353,S=26;
inline void Add(int &x,int y){ x=(x+y)%mod; }

int n,len[maxn],ans;
string str[maxn];
vector<int>w[maxn],v[maxn],kmp[maxn];

struct acam
{
    int idx,t[maxn][26],fail[maxn],ed[maxn],val[maxn];
    vector<int>e[maxn];
    inline void insert(int id)
    {
        int x=0;
        for(int i=0;i<len[id];i++)
        {
            int ch=str[id][i]-'a';
            if(!t[x][ch]) t[x][ch]=++idx;
            x=t[x][ch];
            Add(val[x],v[id][i]);
        }
        ed[id]=x;
    }
    inline void build()
    {
        queue<int>q;
        for(int i=0;i<S;i++) if(t[0][i]) q.push(t[0][i]);
        while(!q.empty())
        {
            int x=q.front();q.pop();
            if(x) e[fail[x]].push_back(x);
            for(int i=0;i<S;i++)
            {
                int &y=t[x][i];
                if(y) fail[y]=t[fail[x]][i],q.push(y);
                else y=t[fail[x]][i];
            }
        }
    }
    inline void dfs(int x)
    {
        for(auto y:e[x])
            Add(val[y],val[x]),dfs(y);
    }
}B[2];

inline void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>str[i],len[i]=str[i].size();
        for(int j=0,x;j<len[i];j++) cin>>x,w[i].push_back(x);
    }

    for(int T=0;T<2;T++)
    {
        for(int i=1;i<=n;i++)
        {
            kmp[i].resize(len[i]),v[i].resize(len[i]);
            kmp[i][0]=-1;
            for(int x=1,y=-1;x<len[i];x++) 
            {  
                while(y>-1 && str[i][y+1]!=str[i][x]) y=kmp[i][y];
                if(str[i][y+1]==str[i][x]) y++;
                kmp[i][x]=y;
            }
            for(int j=0;j<len[i];j++)
            {
                if(kmp[i][j]>=0) v[i][j]=(w[i][j]-w[i][kmp[i][j]]+mod)%mod;
                else v[i][j]=w[i][j];
            }
            B[T].insert(i);
        }
        B[T].build(),B[T].dfs(0);
        vector<int>res(2);
        for(int i=1;i<=n;i++)
        {
            int tot=0;
            Add(tot,B[T].val[B[T].ed[i]]);
            Add(tot,mod-w[i][len[i]-1]);
            Add(ans,tot);
        }
        for(int i=1;i<=n;i++) reverse(str[i].begin(),str[i].end());
    }
    for(int i=1;i<n;i++) ans=ans*i%mod;
    cout<<ans<<endl;
}
signed main()
{
    freopen("unpredictable.in","r",stdin);
    freopen("unpredictable.out","w",stdout);
    ios::sync_with_stdio(false); cin.tie(NULL);
    solve();
}