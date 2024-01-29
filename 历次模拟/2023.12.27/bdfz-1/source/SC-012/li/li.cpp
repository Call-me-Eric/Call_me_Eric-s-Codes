#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read() {
    int res = 0, f = 1; char ch;
    while((ch = getchar()) && (ch < '0' || ch > '9') && ch != '-');
    (ch == '-') ? f = -1 : res = ch - '0';
    while((ch = getchar()) && ch >= '0' && ch <= '9') res = (res << 3) + (res << 1) + ch - '0';
    return res * f;
}

inline void print(int x, char ch = '\n') {
    if(x < 0) putchar('-'), x = -x;
    static short prnum[21];
    short prcnt = 0;
    do { prnum[++prcnt] = x % 10; x /= 10; } while(x > 0);
    while(prcnt) putchar(prnum[prcnt--] + '0');
    putchar(ch);
}

const int MAXN  = 2e5 + 5;

int n, m, ans1, ans2;
bool vis[MAXN];
vector<int> e[MAXN];
queue<int> q;

void solve(int rt) {
    int se = 0, sn = 0, mx = 0, ye = 0;
    vis[rt] = true; q.push(rt);
    while(q.size()) {
        int x = q.front(); q.pop();
        ++sn; ye += (int)(e[x].size());
        for(int it : e[x]) {
            int v = (int)(e[x].size()) + (int)(e[it].size()) - 2;
            mx = max(mx, v);
            se += v;
            if(!vis[it]) vis[it] = true, q.push(it);
         }
    }
    ye /= 2; se /= 4;
    if(ye > sn || mx > 3) { puts("-1"); exit(0); }
    else if(sn == ye) {
        if(se > ye) { puts("-1"); exit(0); }
        ans1 += sn;
    }
    else {
        if(sn == 1) ++ans2;
        else if(se == ye) {
            if(se == 3) ans1 += 3;
            else { puts("-1"); exit(0); }
        }
        else if(se > ye) { puts("-1"); exit(0); }
        else ans2 += sn * (sn + 1) / 2;
    }
}

signed main() {
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
    n = read(); m = read();
    for(int i = 1, x, y; i <= m; i++) {
        x = read(); y = read();
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for(int i = 1; i <= n; i++)
     if((int)(e[i].size()) > 3) return puts("-1"), 0;
    for(int i = 1; i <= n; i++)
     if(!vis[i]) solve(i);
    if(ans1) printf("1 %lld\n",ans1);
    else printf("0 %lld\n",ans2);
    return 0;
}
