#include<bits/stdc++.h>
#define ll long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline ll read(){
    ll x = 0, f = 1;char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = -1;ch = getchar();}
    while(isdigit(ch)){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const ll maxn = 1e5 + 10, INF = 0x3f3f3f3f3f3f3f3f;
ll n, m, k, X, Y;
ll x[maxn], y[maxn];
ll sx[maxn], sy[maxn];
ll fx(ll u){return u / n * sx[n - 1] + sx[max(0ll,u % n - 1)];}
ll fy(ll u){return u / n * sy[n - 1] + sy[max(0ll,u % n - 1)];}
bool check(ll m){return abs(fx(m) - X) + abs(fy(m) - Y) <= m * k;}
ll calc(ll a,ll b,ll l,ll r){
    if(r < l)return INF;
    if(a == 0){return b >= 0 ? l : INF;}
    if(a > 0){
        ll x = floor(1.0 * b / a);
        if(x >= l)return l;
        else return INF;
    }
    else{
        ll x = ceil(1.0 * b / a);
        if(x <= r)return max(x,l);
        else return INF;
    }
}
void solve(){
    n = read(); k = read(); X = read(); Y = read();
    for(ll i = 0;i < n;i++){
        x[i] = read(); y[i] = read();
        if(i){sx[i] = sx[i - 1] + x[i];sy[i] = sy[i - 1] + y[i];}
        else {sx[i] = x[i];sy[i] = y[i];}
    }
    if(X == 0 && Y == 0){puts("0");return;}
    ll m = INF,res = INF, id = INF;
    for(ll i = 0;i < n;i++){
        ll ans = INF;
        ll sxx = i ? sx[i - 1] : 0;
        ll syy = i ? sy[i - 1] : 0;
        ll u = X - sxx, v = Y - syy;

        ll a = -1, b = -1;
        if(sx[n - 1] != 0)a = floor(1.0 * u / sx[n - 1]);
        if(sy[n - 1] != 0)b = floor(1.0 * v / sy[n - 1]);
        a = max(a,-1ll); b = max(b,-1ll);

        ll sX = sx[n - 1], sY = sy[n - 1];
        if(a > b){swap(a,b);swap(sX,sY);swap(u, v);}
        ll f1 = 1, f2 = 1, c, d;
        // printf("[%lld,%lld]\n",0ll,a);
        if(0ll <= a){
            f1 = 0 * sX > u ? 1 : -1;
            f2 = 0 * sY > v ? 1 : -1;
            c = -n * k + f1 * sX + f2 * sY, d = i * k + f1 * u + f2 * v;
            ans = min(ans,calc(c,d,0ll,a));
        }
        if(ans != INF){if(res > ans)res = ans,id = i;continue;}

        // printf("[%lld,%lld]\n",a + 1,b);
        if(a + 1 <= b){
            f1 = (a + 1) * sX > u ? 1 : -1;
            f2 = (a + 1) * sY > v ? 1 : -1;
            c = -n * k + f1 * sX + f2 * sY, d = i * k + f1 * u + f2 * v;
            ans = min(ans,calc(c,d,a + 1,b));
        }
        if(ans != INF){if(res > ans)res = ans,id = i;continue;}

        // printf("[%lld,%lld]\n",b+1,INF);
        if(b + 1 <= INF){
            f1 = (b + 1) * sX > u ? 1 : -1;
            f2 = (b + 1) * sY > v ? 1 : -1;
            c = -n * k + f1 * sX + f2 * sY, d = i * k + f1 * u + f2 * v;
            ans = min(ans,calc(c,d,b + 1,INF));
        }
        if(ans != INF){if(res > ans)res = ans,id = i;continue;}

    }
    m = res * n + id;
    if(res == INF)puts("-1");
    else{printf("%lld\n",m);}
    // printf("check = %d\n",);
    // printf("res = %lld\n",res);
    return;
}
void main(){ll T = read();while(T--){solve();}return;}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}