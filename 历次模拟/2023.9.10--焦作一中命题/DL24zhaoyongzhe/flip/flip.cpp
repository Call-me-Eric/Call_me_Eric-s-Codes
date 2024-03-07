#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
char ch[maxn], T[4];
int n, len;
signed main(){
    freopen("flip.in","r",stdin);
    freopen("flip.out","w",stdout);
    scanf("%s",ch + 1);n = strlen(ch + 1);
    scanf("%s",T + 1);len = strlen(T + 1);
    if(len == 1){
        bool pos = T[1] - '0',flag = 1;
        for(int i = 1;i <= n;i++){
            if(pos == ch[i] - '0'){flag = 0;break;}
        }
        puts(flag ? "0" : "-1");
    }
    else if(len == 2){
        if(T[1] != T[2]){
            bool pos = T[2] - '0';
            int ans = 0;
            for(int i = 2;i <= n;i++){
                if(ch[i] - '0' == pos && ch[i - 1] - '0' != pos)ans++;
            }
            printf("%d\n",ans);
        }
        else{
            bool pos = T[1] - '0';
            int ans = 0, len = 0, cnt = 0;
            for(int i = 1;i <= n;i++){
                if(ch[i] - '0' == pos){
                    len++;
                }
                else{
                    cnt++;
                    ans += (len - 1) * (len >= 1);
                    len = 0;
                }
            }
            if(cnt + 1 >= n - cnt){
                printf("%d\n",ans);
            }
            else puts("-1");
        }
    }
    else {
        if(T[1] == '1'){
            for(int i = 1;i <= n;i++){ch[i] = !(ch[i] - '0');}
            for(int i = 1;i <= len;i++){T[i] = !(T[i] - '0');}
        }
        puts("-1");
    }
    return 0;
}