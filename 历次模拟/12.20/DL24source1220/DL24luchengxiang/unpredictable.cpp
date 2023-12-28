#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define int ll
#define endl '\n'
#define gc cin.get
#define pc cout.put
const int N=2e3+5;
const int M=1e5+5;
const int inf=0x3f3f3f3f;
const int mod=998244353;
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
int T,n,m,poww[M],len[N],ans[N],res,pos[N];
vector<int>hashh[N],w[N],f_hash[N];
char s[M];
struct node{
    int len;
    vector<int>w;
}a[N];
inl bool cmp(int x,int y){return a[x].len<a[y].len;}
signed main(){
    freopen("unpredictable.in","r",stdin);
    freopen("unpredictable.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    n=read();
    if(n>2000){
        for(int i=1;i<=n;i++)pos[i]=i;
        for(int i=1;i<=n;i++){
            cin>>s+1;a[i].len=strlen(s+1);
            a[i].w.reserve(a[i].len+1);
            a[i].w.push_back(0);
            for(int j=1;j<=a[i].len;j++)a[i].w.push_back(read());
        }
        sort(pos+1,pos+n+1,cmp);
        for(int i=1;i<=len[pos[n]];i++){
            for(int num=n-1,k=pos[num];num&&len[k]>=i;num--,k=pos[num])
                a[k].w[i]=(a[k].w[i]+a[pos[num+1]].w[i])%mod;
        }
        for(int i=1,k=pos[i];i<=n-1;i++)
            res=(res+a[pos[i+1]].w[a[k].len]*2%mod+(n-i)*(a[pos[i+1]].w[a[k].len]-a[k].w[a[k].len]+mod)*2%mod)%mod;
        cout<<res<<endl;
        return 0;
    }
    poww[0]=1;
    for(int i=1;i<=1e5;i++)poww[i]=poww[i-1]*base%mod;
    for(int i=1;i<=n;i++){
        cin>>s+1;len[i]=strlen(s+1);
        hashh[i].reserve(len[i]+1);f_hash[i].reserve(len[i]+1);w[i].reserve(len[i]+1);
        hashh[i].push_back(0);w[i].push_back(0);f_hash[i].push_back(0);
        for(int j=1;j<=len[i];j++)w[i].push_back(read());
        for(int j=1;j<=len[i];j++)
            hashh[i].push_back((hashh[i][j-1]*base%mod+s[j])%mod);
        for(int j=1;j<=len[i];j++)
            f_hash[i].push_back((f_hash[i][j-1]+s[len[i]-j+1]*poww[j-1]%mod)%mod);
    }
    for(int i=1;i<=n;i++){
        memset(ans,-1,sizeof ans);int num=0;
        for(int j=len[i];j;j--){
            if(num==n-1)break;
            int x=f_hash[i][j];
            for(int k=1;k<=n;k++){
                if(i==k||~ans[k]||len[k]<j)continue;
                if(x==hashh[k][j]){
                    int p=w[i][j]+w[k][j];
                    ans[k]=(p>=mod?p-mod:p),++num;
                }
            }
        }
        for(int j=1;j<=n;j++){
            int p=res+(~ans[j]?ans[j]:0);
            res=p>=mod?p-mod:p;
        }
    }
    res=res*(n-1)%mod;
    for(int i=2;i<=n-2;i++)res=res*i%mod;
    cout<<res<<endl;
    return 0;
}