#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
char ch[maxn];int n, m, k;
signed main(){
    scanf("%d%d%d",&n,&m,&k); scanf("%s",ch + 1);
    for(int i = 1;i <= m + k;i++){
        int opt,u,v,w;scanf("%d%d%d%d",&opt,&u,&v,&w);
        if(opt == 1){memset(ch + u,w + '0',v - u + 1);}
        else{puts(memcmp(ch + u,ch + u + w,v - u - w + 1) ? "NO" : "YES");}
    }
    return 0;
}