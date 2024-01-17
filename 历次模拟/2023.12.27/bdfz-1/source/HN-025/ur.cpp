#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6;
int n=1e6+2,K,lw[N];
int st[N],tp,ans[N];
int main(){
    ios::sync_with_stdio(false);
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    int i,j,k,l,r,x,y;
    for(x=2;x<=n;++x)
        if(!lw[x])
            for(y=n/x;y;--y)lw[x*y]=x;
    cin>>n>>K;
    if(K<lw[n]){
        for(i=1;i<=n;++i)putchar('0');
        return 0;
    }
    for(x=n;x>1;x/=lw[x])st[++tp]=lw[x];
    k=*max_element(st+1,st+tp+1,[&](int x,int y){
        return K/x*x<K/y*y;
    });
    for(i=1;i<=K/k;++i)
        for(j=i;j<=n;j+=n/k)ans[j]=1;
    int sum=0;
    for(i=1;i<=n;++i)sum+=ans[i];
    for(i=1;i<=n;++i)putchar(ans[i]^48);
    return 0;
}