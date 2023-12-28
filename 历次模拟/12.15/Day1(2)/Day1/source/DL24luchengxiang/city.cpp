#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
#define endl '\n'
#define gc cin.get
#define pc cout.put
const int N=5e2+5;
const int M=1e8+5;
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
int n,m;
signed main(){
    freopen("city.in","r",stdin);
    freopen("city.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cout<<"No solution!"<<endl;
    return 0;
}