#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=998244353;
mt19937_64 rg(random_device{}());
int rd(int l,int r){
    return l+rg()%(r-l+1);
}
int n=700,q=700;
int main(){
    freopen("eq.in","w",stdout);
    int i,j,k,l,r,x,y;
    printf("%d %d\n",n,q);
    for(i=1;i<=n;++i)
        for(j=0;j<=n;++j)
            printf("%d%c",rd(0,M-1)," \n"[j==n]);
    while(q--){
        printf("%d ",rd(1,n));
        for(j=0;j<=n;++j)
            printf("%d%c",rd(0,M-1)," \n"[j==n]);
    }return 0;
}