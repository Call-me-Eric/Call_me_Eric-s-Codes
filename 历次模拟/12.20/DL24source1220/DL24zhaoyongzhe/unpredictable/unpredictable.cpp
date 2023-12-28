#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
typedef unsigned long long ull;
typedef long long ll;
const int maxn = 1e6 + 10;
const ll mod = 998244353;
int n;
// bool st;
string ch[maxn];
vector<ll> w[maxn];

vector<ull> hsh[maxn];
ull pw[maxn];
const ull Base = 27;
ull gethash(int id,int l,int r){
    ull lft = (l == 0) ? 0 : hsh[id][l - 1];
    lft *= pw[r - l + 1];
    return hsh[id][r] - lft;
}
// bool ed;

map<pair<int,ull>,ll> mp;
ll solve(){
    ll ans = 0;mp.clear();
    for(int i = 1;i <= n;i++){
        hsh[i].clear();
        ull lst = 0;
        for(int j = 0;j < ch[i].size();j++){
            hsh[i].push_back(lst * Base + (ull)(ch[i][j] - 'a'));
            lst = hsh[i].back();
            // cout << " " << lst;
        }
        // cout << endl;
        ans -= w[i][ch[i].size() - 1];if(ans < 0)ans += mod;
        for(int j = 0;j < ch[i].size();j++){
            ll last = 0;
            for(int k = j - 1;k >= 0;k--){
                if(gethash(i,0,k) == gethash(i,j - k,j)){
                    last = w[i][k];
                    break;
                }
            }
            mp[make_pair(j + 1,gethash(i,0,j))] += (w[i][j] - last + mod) % mod;
            mp[make_pair(j + 1,gethash(i,0,j))] %= mod;
        }
        // cout << "i = " << i << " ans = " << ans << endl;
    }
    for(int i = 1;i <= n;i++){
        for(int j = ch[i].size() - 1;j + 1;j--){
            ans += mp[make_pair(ch[i].size() - j,gethash(i,j,ch[i].size() - 1))];
            // cout << "mp = " << mp[make_pair(ch[i].size() - j,gethash(i,j,ch[i].size() - 1))] << endl;
            ans %= mod;
        }
        // cout << "i = " << i << " ans = " << ans << endl;
    }
    return ans % mod;
}
signed main(){
    // cerr << (&ed - &st) / 1024.0 / 1024.0 << "Mib cost." << endl;
    freopen("unpredictable.in","r",stdin);
    freopen("unpredictable.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n;pw[0] = 1;ll fac = 1, sum = 0;
    for(int i = 1;i <= n;i++){
        pw[i] = pw[i - 1] * Base;
        if(i != n)fac = fac * i % mod;
        cin >> ch[i];sum += ch[i].size();
        for(int j = 0;j < ch[i].size();j++){
            ll x;cin >> x;w[i].push_back(x);
        }
    }
    // if(sum){
        ll ans = solve() % mod;
        for(int i = 1;i <= n;i++){
            reverse(ch[i].begin(),ch[i].end());
        }
        cout << (ans + solve()) % mod * fac % mod << endl;
    // }
    // else{
    //     ll ans = 0;
    //     for(int i = 1;i <= n;i++){
    //         ull lst = 0;
    //         for(int j = 0;j < ch[i].size();j++){
    //             hsh[i].push_back(lst * Base + (ull)(ch[i][j] - 'a'));
    //             lst = hsh[i].back();
    //             // cout << " " << lst;
    //         }
    //     }
    //     for(int i = 1;i <= n;i++){
    //         for(int j = 1;j <= n;j++){
    //             if(i == j)continue;int l = -1;
    //             for(int k = min(ch[i].size(),ch[j].size()) - 1;k >= 0;k--){
    //                 if(gethash(i,0,k) == gethash(j,ch[j].size() - 1 - k,ch[j].size() - 1)){
    //                     l = k;break;
    //                 }
    //             }
    //             if(l == -1)continue;
    //             ans = (ans + w[i][l] + w[j][l]) % mod;
    //         }
    //     }
    //     cout << ans * fac % mod << endl;
    // }
    return 0;
}