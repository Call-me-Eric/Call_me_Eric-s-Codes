#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, m, k;
int cnt[30];
char ch[maxn];
bool f[maxn];
void solve(){
    n = read(); m = read(); k = read();
    if(n < m)swap(n, m);
    for(int i = 0;i < 30;i++)cnt[i] = 0;
    scanf("%s",ch + 1);
    for(int i = 1;i <= k;i++)cnt[ch[i] - 'A']++;
    int ans = 0x3f3f3f3f, rest = k - m - n;
    vector<int> tmp;tmp.clear();tmp.push_back(0);
    for(int i = 0;i < 26;i++)if(cnt[i])tmp.push_back(cnt[i]);k = tmp.size() - 1;
    for(int i = 1;i <= k;i++){
        f[0] = 1;for(int i = 1;i <= n;i++)f[i] = 0;
        for(int j = 1;j <= k;j++){
            if(i == j)continue;
            for(int l = n;l >= tmp[j];l--)f[l] |= f[l - tmp[j]];
        }
        // for(int j = 1;j <= n;j++)printf("%d ",f[j]);puts("");
        for(int j = min(tmp[i],n);j >= 0;j--){
            if(!f[n - j])continue;
            ans = min(ans,j * max(0,tmp[i] - j - rest));
        }
    }
    printf("%d\n",ans);
}
signed main(){
    int T = read();
    while(T--){solve();}
    return 0;
}