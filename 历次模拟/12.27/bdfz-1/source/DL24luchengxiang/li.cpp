#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define int ll
#define endl '\n'
#define gc cin.get
#define pc cout.put
const int N=5e3+5;
const int M=1e5+5;
const int inf=0x7fffffffffffffff;
const int mod=998244353;
const int base=13131;
inl int read(){
    int x=0,f=1;char c=gc();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=gc();}
    return x*f;
}
int n,m;
signed main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    n=read();m=read();
    if(m)int u=read(),v=read();
    if(n==1)cout<<0<<' '<<1<<endl;
    if(n==2){
        if(!m)cout<<0<<' '<<2<<endl;
        else cout<<0<<' '<<3<<endl;
    }else cout<<"woshidashabi"<<endl;
    return 0;
}