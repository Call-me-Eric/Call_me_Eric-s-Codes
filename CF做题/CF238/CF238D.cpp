#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, q;
char ch[maxn];
int len, l[maxn], r[maxn];
bool book[2][maxn];
int f[2][maxn][10];

int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
void merg(int x,int y){int fx = getf(x), fy = getf(y);if(fx != fy)fa[fy] = fx;}

int pos, opt, buc[10];
void del(int x){r[l[x]] = r[x];l[r[x]] = l[x];len--;}
void move(){
    int nxt = 0;
    if(isdigit(ch[pos])){
        buc[ch[pos] - '0']++;
        if(ch[pos] == '0')del(pos);
        else ch[pos]--;
        nxt = opt ? r[pos] : l[pos];
    }
    else{
        if(ch[pos] == '<')opt = 0;
        else opt = 1;
        nxt = opt ? r[pos] : l[pos];
        if(pos && !isdigit(ch[nxt]))del(pos);
    }
    if(opt == 1 && !book[1][nxt]){
        for(int i = 0;i < 10;i++)f[1][nxt][i] = buc[i];
        book[1][nxt] = 1;
    }
    if(opt == 0){
        int j = getf(nxt) + 1;
        while(j <= pos){
            book[0][j] = 1;
            for(int i = 0;i < 10;i++)f[0][j][i] = buc[i];
            merg(j,j - 1);j = getf(j) + 1;
        }
    }
    pos = nxt; return;
}

signed main(){
    n = read(); q = read();
    scanf("%s",ch + 1);ch[0] = '>';
    for(int i = 1;i <= n;i++){fa[i] = i;r[i] = i + 1;l[i] = i - 1;}
    memset(f,0x3f,sizeof(f));
    r[0] = 1;opt = 1;pos = 0;len = n;
    while(len > 0 && pos <= n){move();}
    for(int j = 1;j <= q;j++){
        int l = read(), r = read();
        for(int i = 0;i < 10;i++)
            printf("%d ",(book[0][l] ? min(f[0][l][i],f[1][r + 1][i]) : f[1][r + 1][i]) - f[1][l][i]);
        puts("");
    }
    return 0;
}