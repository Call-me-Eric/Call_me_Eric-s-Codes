#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2000 + 10;
bool e[maxn][maxn];
int n;
char ch[maxn];
int buc[maxn];
int d[maxn], deg[maxn];
void rev(int x,int y){deg[x] -= e[x][y];e[x][y] ^= 1;deg[x] += e[x][y];}
void upd(int x){for(int i = 1;i <= n;i++)rev(x,i),rev(i,x);}
bool check(){
    for(int i = 0;i < n;i++)buc[i] = 0;
    for(int i = 1;i <= n;i++)buc[deg[i]]++;
    int pos = 0, sum = 0;
    for(int i = 0;i < n;i++)
        while(buc[i]){d[++pos] = i;buc[i]--;}
    
    for(int i = 1;i < n;i++){sum += d[i]; if(sum == i * (i - 1) / 2)return false;}
    return true;
}
int ans1,ans2;
void solve1(){
    ans1 = 114514;
    for(int sta = 0;sta < (1 << n);sta++){
        int tot = 0;
        for(int i = 1;i <= n;i++)
            if(sta & (1 << (i - 1))){
                upd(i);tot++;
            }
        if(tot <= ans1 && check()){
            if(tot == ans1){ans2++;}
            else {ans1 = tot;ans2 = 1;}
        }
        for(int i = 1;i <= n;i++)
            if(sta & (1 << (i - 1)))
                upd(i);
    }
    for(int i = 1;i <= ans1;i++)ans2 *= i;
}
void solve2(){
    ans1 = 1;
    for(int i = 1;i <= n;i++){
        upd(i);ans2 += check();upd(i);
    }
}
void print(){
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            printf("%d%c",e[i][j]," \n"[j == n]);
    for(int i = 1;i <= n;i++){
        printf("deg[%d] = %d\n",i,deg[i]);
    }
    puts("");
}
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        scanf("%s",ch + 1);
        for(int j = 1;j <= n;j++){
            e[i][j] = (ch[j] == '1');
            deg[i] += e[i][j];
        }
    }
    if(check()){puts("0 1");return 0;}
    if(n <= 6){solve1();}else solve2();
    if(ans1 == 114514)puts("-1");
    else printf("%d %d\n",ans1,ans2);
    return 0;
}