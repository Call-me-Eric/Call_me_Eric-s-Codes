#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define endl '\n'
#define int ll
#define gc cin.get
#define pc cout.put
const int N=2e5+5;
const int M=5e6+5;
const int inf=0x3f3f3f3f;
const int mod=1e8+7;
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
int t,n,m,sum[N],ma;
struct node{
    int x,y;
    friend bool operator<(node a,node b){return a.x<b.x;}
}a[N];
signed main(){
    freopen("value.in","r",stdin);
    freopen("value.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    n=read();int flag=1,res=0;
    for(int i=1;i<=n;i++)a[i]={read(),read()};
    sort(a+1,a+n+1);
    for(int i=1;i<=n+1;i++){
        int ans=(n-i+1)*a[i].x;
        sum[i-1]++;ma=max(ma,a[i-1].y);
        for(int j=1;j<i-1;j++){
            if(a[j].y>a[i-1].y)continue;
            sum[j]++;ma=max(ma,sum[j]*a[j].y);
        }
        res=max(res,ans+ma);
    }
    cout<<res<<endl;
    return 0;
}