#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    scanf("%d%d",&n,&k);
    if(n==k){for(int i=1;i<=n;i++)putchar('1');}
    else{for(int i=1;i<=n;i++)putchar('0');}
    return 0;
}