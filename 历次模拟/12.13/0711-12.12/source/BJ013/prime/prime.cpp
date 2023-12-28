#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mod=998244353;

const string ss[]={"11","19","41","61","89","409","449","499","881","991","6469","6949",
"9001","9049","9649","9949","60649","666649","946669","60000049","66000049","66600049"};

int len,cnt[10]={0,1,-1,-1,2,-1,3,-1,4,5},num[6]={0,1,4,6,8,9};
bool ban[55][2],bp[1605][2],zp[2];
int dp[2][1605],tk[2][1605],ans;
int nt[55][6],adj[1605][12],ck[1605];
int cur=1,cc,_;
map<string,int> id;
string s,tp,uk[1605];

inline void add(int u,int l)
{
    if(l==len)
    {
        if(s[l]=='1')
            ban[u][0]=1;
        else
            ban[u][1]=1;
        return;
    }

    if(!nt[u][cnt[s[l]-'0']])
        nt[u][cnt[s[l]-'0']]=++cur;

    add(nt[u][cnt[s[l]-'0']],l+1);
}

inline void dfs(int u)
{
    for(int i=0;i<6;i++)
    {
        if(i==1&&bp[u][0])
            continue;
        if(i==5&&bp[u][1])
            continue;

        int v;
        zp[0]=zp[1]=0;
        tp=uk[u];
        for(int j=cur;j;j--)
        {
            if(tp[j]-'0'&&nt[j][i])
                tp[nt[j][i]]='1';
        }
        for(int j=1;j<=cur;j++)
        {
            if(tp[j]-'0')
                zp[0]|=ban[j][0],zp[1]|=ban[j][1];
        }
        if(zp[0]&&zp[1])
            v=0;
        else if(!id[tp])
            v=++cc;
        else
            v=id[tp];

        adj[u][ck[u]++]=v;
        adj[u][ck[u]++]=num[i];

        if(v&&v!=id[tp])
        {
            id[tp]=v;
            bp[v][0]=zp[0],bp[v][1]=zp[1];
            uk[v]=tp;
            dfs(v);
        }
    }
}

inline void update(int &x,int y)
{
    x+=y;
    if(x>=mod)
        x-=mod;
}

int main()
{
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    for(int i=0;i<22;i++)
    {
        s=ss[i];
        len=s.size();
        s='0'+s;
        add(1,1);
    }

    for(int i=0;i<=cur;i++)
        tp+='0';

    bp[0][0]=bp[0][1]=1;
    tp[1]='1';
    id[tp]=cc=1;
    uk[1]=tp;
    dfs(1);

    adj[0][ck[0]++]=0;
    adj[0][ck[0]++]=0;
    adj[0][ck[0]++]=0;
    adj[0][ck[0]++]=4;
    adj[0][ck[0]++]=0;
    adj[0][ck[0]++]=6;
    adj[0][ck[0]++]=0;
    adj[0][ck[0]++]=8;

    cin>>_;

    while(_--)
    {
        ans=0;

        cin>>s;
        len=s.size();

        for(int i=len-1;i>=0;i--)
        {
            if(s[i]>'0')
            {
                s[i]--;
                break;
            }

            s[i]='9';
        }

        memset(dp,0,sizeof(dp));
        memset(tk,0,sizeof(tk));
        dp[1][1]=1;

        for(int i=0;i<len;i++)
        {
            for(int k=0;k<=cc;k++)
            {
                for(int ii=0;ii<ck[k];ii+=2)
                {
                    int v=adj[k][ii],w=adj[k][ii+1];

                    update(tk[0][v],dp[0][k]);
                    if(w<s[i]-'0')
                        update(tk[0][v],dp[1][k]);
                    if(w==s[i]-'0')
                        update(tk[1][v],dp[1][k]);
                }
            }

            for(int k=0;k<=cc;k++)
            {
                dp[0][k]=tk[0][k],dp[1][k]=tk[1][k];
                tk[0][k]=tk[1][k]=0;
            }
        }

        for(int i=0;i<=cc;i++)
            update(ans,dp[0][i]),update(ans,dp[1][i]);
        ans=mod-ans;
        update(ans,0);

        cin>>s;
        len=s.size();

        memset(dp,0,sizeof(dp));
        memset(tk,0,sizeof(tk));
        dp[1][1]=1;

        for(int i=0;i<len;i++)
        {
            for(int k=0;k<=cc;k++)
            {
                for(int ii=0;ii<ck[k];ii+=2)
                {
                    int v=adj[k][ii],w=adj[k][ii+1];

                    update(tk[0][v],dp[0][k]);
                    if(w<s[i]-'0')
                        update(tk[0][v],dp[1][k]);
                    if(w==s[i]-'0')
                        update(tk[1][v],dp[1][k]);
                }
            }

            for(int k=0;k<=cc;k++)
            {
                dp[0][k]=tk[0][k],dp[1][k]=tk[1][k];
                tk[0][k]=tk[1][k]=0;
            }
        }

        for(int i=0;i<=cc;i++)
            update(ans,dp[0][i]),update(ans,dp[1][i]);

        cout<<ans<<'\n';
    }

    return 0;
}
