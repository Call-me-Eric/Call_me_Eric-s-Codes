#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f= 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, k;
int a[maxn], tmp[maxn];
inline int mul(int a,int b){
    int res = 0;
    while(b){
        if(b & 1)res = res + a;
        if(res > k)return k;
        a = a + a;b >>= 1;a = min(k, a);
    }
    return res;
}
struct Matrix{
    int a[11][11];
    Matrix(){memset(a,0,sizeof(a));}
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix ans;
        for(int i = 1;i <= n;i++)
            for(int t = 1;t <= n;t++)
                for(int j = 1;j <= n;j++){
                    ans.a[i][j] += mul(a.a[i][t] , b.a[t][j]);
                    if(ans.a[i][j] > k)ans.a[i][j] = k;
                }
        return ans;
    }
}A, B;
Matrix qpow(Matrix a,int x){
    Matrix res = a;x--;
    while(x){
        if(x & 1){res = res * a;}
        a = a * a;x >>= 1;
        // printf("x=  %lld\n",x);
    }
    return res;
}
bool check(int mid){
    Matrix res = A * qpow(B,mid);
    // puts("1111111111");
    for(int i = 1;i <= n;i++){if(res.a[1][i] >= k)return true;}
    return false;
}
signed main(){
    // #ifndef ONLINE_JUDGE
    // freopen("CF837F.in","r",stdin);
    // #endif
    n = read(); k = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    int pos1 = 0, j = 1, book = 1;
    for(int i = 1;i <= n;i++){if(a[i] >= k){puts("0");return 0;}if(!a[i] && book)pos1 = i;else book = 0;}
    for(int i = pos1 + 1;i <= n;i++,j++){tmp[j] = a[i];}j--;
    for(int i = 1;i <= j;i++)a[i] = tmp[i];n = j;
    // printf("%lld\n",n);
    // for(int i = 1;i <= n;i++){printf("%lld ",a[i]);}
    if(n > 10){
        int cnt = 0;
        while(1){
            tmp[0] = 0;cnt++;
            for(int i = 1;i <= n;i++)tmp[i] = tmp[i - 1] + a[i];
            for(int i = 1;i <= n;i++){
                a[i] = tmp[i];
                if(a[i] >= k){printf("%lld\n",cnt);return 0;}
            }
        }
    }
    else if(n == 2){
        // if(a[2] >= k || a[1] >= k){puts("0");return 0;}
        int ans = (k - a[2]) / a[1] - 3;
        while(1){//精度修正
            if(ans * a[1] + a[2] >= k){printf("%lld\n",ans);return 0;}
            ans++;
        }
    }
    else{
        for(int i = 1;i <= n;i++){A.a[1][i] = a[i];}
        for(int i = 1;i <= n;i++)
            for(int j = n;j >= i;j--)
                B.a[i][j] = 1;
        int l = 1, r = 64356879284, mid = 0, ans = -1;
        // printf("n = %lld",n);
        while(l <= r){
            // printf("l=%lld r=%lld\n",l,r);
            mid = (r - l) / 2 + l;
            // printf("mid=%lld\n",mid);
            if(check(mid)){ans = mid;r = mid - 1;}
            else l = mid + 1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}