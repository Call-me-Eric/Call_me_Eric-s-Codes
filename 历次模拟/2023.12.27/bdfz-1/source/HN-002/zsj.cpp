#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(random_device{}());
int n=700,q=700;
const int mod=998244353;
int main(){
    freopen("eq.in","w",stdout);
    printf("%d %d\n",n,q);
    for(int i=1;i<=n;i++){for(int j=0;j<=n;j++)printf("%ld ",rnd()%mod);puts("");}
    for(int i=1;i<=q;i++){printf("%ld ",(rnd()%n)+1);for(int j=0;j<=n;j++)printf("%ld ",rnd()%mod);puts("");}
}