#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
bool st;
const int maxn = 1024;
struct Matrix{
    bitset<maxn> a[maxn];
    int n, m;
    // Matrix(int n = 0,int m = 0):n(n),m(m){for(int i = 1;i <= n;i++)a[i].reset();}
    friend Matrix operator *(Matrix a,Matrix b){
        Matrix ans;ans.n = a.n;ans.m = b.m;
        for(int i = 1;i <= a.n;i++)
            for(int k = 1;k <= a.m;k++)
                if(a.a[i][k]) ans.a[i] ^= b.a[k];
        return ans;
    }
}pw[31], b, ans;
int n, k;
char ch[maxn];
bool ed;
signed main(){
    // cerr << (&st - &ed) / 1024.0 / 1024 << "Mib cost." << endl;
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);
    n = read();
    for(int i = 1;i <= n;i++){
        scanf("%s",ch + 1);
        for(int j = 1;j <= n;j++)
            pw[0].a[j][i] = ch[j] - '0';
    }
    scanf("%s",ch + 1);
    for(int i = 1;i <= n;i++){b.a[1][i] = ch[i] - '0';}
    pw[0].n = pw[0].m = n;b.n = 1;b.m = n;
    bool flag = false;
    for(int i = 1;i <= 30;i++){
        if(!flag) pw[i] = pw[i - 1] * pw[i - 1];
        else {pw[i].n = pw[i].m = n;continue;}
        int cnt = 0;
        for(int x = 1;x <= n;x++)
            for(int y = 1;y <= n;y++)
                cnt += pw[i].a[x][y];
        if(cnt == 1)flag = 1;
    }
    for(int q = read();q;q--){
        k = read();ans = b;
        for(int i = 0;(1 << i) <= k;i++)
            if(k & (1 << i))ans = ans * pw[i];
        for(int i = 1;i <= n;i++)putchar('0' + ans.a[1][i]);
        putchar('\n');
    }
    return 0;
}