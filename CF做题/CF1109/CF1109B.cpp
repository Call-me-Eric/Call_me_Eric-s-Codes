#include<bits/stdc++.h>
using namespace std;
const int maxn = 5000 + 10;
int chk(char *ch,int n){
    if(n & 1){return 2;}
    for(int i = 1;i <= n / 2;i++){
        if(ch[i] != ch[n / 2 - i + 1])return 1;
    }
    return chk(ch,n / 2);
}
char ch[maxn];
int n;
signed main(){
    scanf("%s",ch + 1);n = strlen(ch + 1);
    bool flag = true;
    for(int i = 2;i <= n;i++){
        if(i == n / 2 + 1 && (n & 1))continue;
        if(ch[i] != ch[1]){flag = false;break;}
    }
    if(flag){puts("Impossible");return 0;}
    printf("%d\n",chk(ch,n));
    return 0;
}