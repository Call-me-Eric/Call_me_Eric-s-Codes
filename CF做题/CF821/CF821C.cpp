#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch =  getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int st[maxn], top;
int n, pos;
signed main(){
    scanf("%d",&n);
    char opt[10];int u, ans = 0;pos = 0;
    for(int i = 1;i <= n * 2;i++){
        scanf(" %s",opt);
        if(opt[0] == 'a'){
            scanf("%d",&u);
            st[++top] = u;
        }
        else{
            pos++;
            if(top == 0)continue;
            if(st[top] != pos){
                ans++;top = 0;
            }
            else top--;
        }
    }
    printf("%d\n",ans);
    return 0;
}