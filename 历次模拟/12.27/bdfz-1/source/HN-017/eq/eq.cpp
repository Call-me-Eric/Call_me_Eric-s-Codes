#include <bits/stdc++.h>
#define ll long long
using namespace std;

template<typename ...Args>
signed debug(const char*str,Args ...args){return fprintf(stderr,str,args...);}

inline static int read(){
    int sum=0; bool neg=false; char ch=getchar();
    while(!isdigit(ch)) neg|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) sum=(sum<<3)+(sum<<1)+(ch^48),ch=getchar();
    return neg?-sum:sum;
}

const int p=998244353;

ll power(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=(ll)res*a%p;
        a=(ll)a*a%p,b>>=1;
    } return res;
}

void solve(int a,int b){
    if(a==0) puts(b==0?"Many":"No");
    else printf("%lld\n",power(a,p-2)*b%p);
}
signed main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    int n=read(),q=read(),a=read(),b=read();
    solve(a,b);
    while(q--){
        read(),a=read(),b=read();
        solve(a,b);
    }
    return 0;
}
