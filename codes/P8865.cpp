#include<bits/stdc++.h>
#define int long long
#define rep(x,a,b) for(int x = 1;x <= b;x += a)
using namespace std;
int T, id;
int n, m;
const int maxn = 1010, mod = 998244353;
int cpoint, fpoint;
bool a[maxn][maxn];
int _right[maxn][maxn], down[maxn][maxn], kt[maxn][maxn], up[maxn][maxn];
//关于right是个函数和起名比AK都难的这件事情
int C[maxn][maxn], F[maxn][maxn];
char ch[maxn][maxn];
signed main(){
    scanf("%lld%lld",&T,&id);
    while(T--){
    memset(a,0,sizeof(a));
    memset(ch,0,sizeof(ch));
    scanf("%lld%lld%lld%lld",&n,&m,&cpoint,&fpoint);
    for(int i = 1;i <= n;i++){
        scanf("%s",ch[i] + 1);
        for(int j = 1;j <= m;j++){
            a[i][j] = ch[i][j] - '0';
        }
    }
    for(int i = m;i >= 1;i--){
        for(int j = 1;j <= n;j++){
            if(a[j][i] == 1)_right[j][i] = 0;
            else{
                if(i == m)_right[j][i] = 1;
                else _right[j][i] = _right[j][i + 1] + 1;
            }
        }
    }
    for(int i = n;i >= 1;i--){
        for(int j = 1;j <= m;j++){
            if(a[i][j] == 1)down[i][j] = 0;
            else {
                if(i == n)down[i][j] = 1;
                else down[i][j] = down[i + 1][j] + 1;
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(a[i][j] == 1)up[i][j] = 0;
            else {
                if(i == 1)up[i][j] = 1;
                else up[i][j] = up[i - 1][j] + 1;
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(a[i][j] == 1)kt[i][j] = 0;
            else {
                if(i == 1)kt[i][j] = _right[i][j];
                else kt[i][j] = kt[i - 1][j] + _right[i][j];
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(up[i][j] <= 2)C[i][j] = 0;
            else{
                C[i][j] = (_right[i][j] - 1) % mod * (kt[i][j] - _right[i][j] - _right[i - 1][j] - (up[i][j] - 2)) % mod;
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(down[i][j] == 0)F[i][j] = 0;
            else F[i][j] = C[i][j] % mod * (down[i][j] - 1) % mod;
        }
    }
    int ans0 = 0,ans1 = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            ans0 += C[i][j];ans1 += F[i][j];
            ans0 %= mod;    ans1 %= mod;
        }
    }
        printf("%lld %lld\n",ans0 * cpoint,ans1 * fpoint);
    }
    return 0;
}
/*
2 0
6 6 1 1
000010
011000
000110
010000
011000
000000

16 12 1 1
000000000001
011111111111
000000000011
011111111111
010011111111
010111100011
010011101111
011111100011
111111111111
000011111111
011111111111
000000111111
011111000111
011111011111
011111000111
011111011111
*/