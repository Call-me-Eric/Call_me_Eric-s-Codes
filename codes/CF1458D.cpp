#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
char ch[maxn];
int e[maxn][2];//0 \leftarrow,1\rightarrow
void solve(){
    scanf("%s",ch + 1);int n = strlen(ch + 1);
    int x = 0;
    for(int i = 1;i <= n;i++){
        if(ch[i] == '0'){e[n + 1 + x][0]++;x--;}
        else{e[n + 1 + x][1]++;x++;}
    }
    x = 0;int cnt = 0;
    while(cnt < n){
        if((e[n + 1 + x][0] && e[n + 1 + x - 1][1]) || (!e[n + x + 1][1])){
            ch[++cnt] = '0';e[n + 1 + x][0]--;x--;
        }
        else{
            ch[++cnt] = '1';e[n + 1 + x][1]--;x++;
        }
    }
    puts(ch + 1);
}
signed main(){
    int T = read();
    while(T--){solve();}
    return 0;
}