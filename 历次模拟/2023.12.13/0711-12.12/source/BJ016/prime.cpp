#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const int mod = 998244353;
int T;
char sl[maxn], sr[maxn];
int f0[maxn][5][5];
inline void upd(int &x, int y){
    return x = x + y >= mod ? x + y - mod : x + y, void();
}
int a[maxn]; int n = 0;
const int dar[4] = {4, 6, 8, 0};
int dfsf0(int st, int p0, int p1, bool fl, bool ld){
    // cerr << st << " " << p0 << " " << p1 << " " << fl << " " << ld << endl;
    if(fl == 0 && ld == 0 && f0[st][p0][p1] >= 0) return f0[st][p0][p1];
    if(st == 0){
        return p0 == 3;
    }
    int res = 0;
    if(ld){
        upd(res, dfsf0(st - 1, p0, p1, 0, ld));
    }
    if(p0 == 0){
        int num = (p1 == 0 ? 9 : (p1 == 1 ? 8 : 1));
        if(fl == 0 || num <= a[st]){
            if(p1 == 0){
                upd(res, dfsf0(st - 1, p0, p1 + 2, fl && (a[st] == num), 0));
            }
            upd(res, dfsf0(st - 1, (p1 == 2 ? 3 : p0), (p1 + 1) % 3, fl && (a[st] == num), 0));
        }
    }
    if(p0 == 1){
        int num = (p1 == 0 ? 9 : (p1 == 1 ? 8 : (p1 == 2 ? 0 : 1)));
        if(fl == 0 || num <= a[st]){
            upd(res, dfsf0(st - 1, (p1 == 3 ? 3 : p0), (p1 + 1) & 3, fl && (a[st] == num), 0));
        }
    }
    if(p0 == 2){
        int num = (p1 == 0 ? 9 : (p1 == 1 ? 0 : (p1 == 2 ? 8 : 1)));
        if(fl == 0 || num <= a[st]){
            if(p1 == 1){
                upd(res, dfsf0(st - 1, p0, p1 + 2, fl && (a[st] == num), 0));
            }
            upd(res, dfsf0(st - 1, (p1 == 3 ? 3 : p0), (p1 + 1) & 3, fl && (a[st] == num), 0));
        }
    }
    if(p0 == 3){
        for(int i = 0;i < 4;i++){
            if(fl && dar[i] > a[st]) continue;
            if(ld && dar[i] == 0) continue;
            upd(res, dfsf0(st - 1, p0, p1, fl && (a[st] == dar[i]), 0));
        }
    }
    if(ld == 0 && fl == 0) f0[st][p0][p1] = res;
    return res;
}
const int dpr[3] = {6, 0, 9};
int f1[maxn][4][5];
int dfsf1(int st, int p0, int p1, bool fl, bool ld){
    if(fl == 0 && ld == 0 && f1[st][p0][p1] >= 0) return f1[st][p0][p1];
    if(st == 0){
        return (p0 == 3);
    }
    int res = 0;
    if(ld){
        upd(res, dfsf1(st - 1, p0, p1, 0, ld));
    }
    if(p0 == 0){
        int num = (p1 == 0 || p1 == 3 ? 9 : (p1 == 1 ? 4 : 6));
        if(fl == 0 || num <= a[st]){
            if(p1 == 1){
                upd(res, dfsf1(st - 1, p0, p1 + 2, fl && a[st] == num, 0));
            }
            if(p1 == 2){
                upd(res, dfsf1(st - 1, p0, 4, fl && a[st] == num, 0));
            }
            if(p1 == 4){
                upd(res, dfsf1(st - 1, p0, 3, fl && a[st] == num, 0));
            }
            if(p1 != 4) upd(res, dfsf1(st - 1, (p1 == 3 ? 3 : p0), (p1 + 1) & 3, fl && a[st] == num, 0));
        }
    }
    if(p0 == 1){
        int num = (p1 == 0 ? 4 : (p1 == 1 ? 6 : 9));
        if(fl == 0 || num <= a[st]){
            if(p1 == 1){
                upd(res, dfsf1(st - 1, p0, p1, fl && a[st] == num, 0));
                upd(res, dfsf1(st - 1, p0, p1 + 1, fl && a[st] == num, 0));
            } else if(p1 != 1){
                if(p1 == 0){
                    upd(res, dfsf1(st - 1, p0, p1 + 2, fl && a[st] == num, 0));
                }
                upd(res, dfsf1(st - 1, (p1 == 2 ? 3 : p0), p1 + 1, fl && a[st] == num, 0));
            }
        }
    }
    if(p0 == 2){
        for(int i = 0;i < 3;i++){
            int num = dpr[i];
            if(fl && num > a[st]) continue;
            if(ld && num == 0) continue;
            upd(res, dfsf1(st - 1, p0, p1, fl && a[st] == num, 0));
            if(num == 9){
                upd(res, dfsf1(st - 1, 3, 0, fl && a[st] == num, 0));
            }
        }
    }
    if(p0 == 3){
        for(int i = 0;i < 4;i++){
            int num = dar[i];
            if(fl && num > a[st]) continue;
            if(ld && num == 0) continue;
            upd(res, dfsf1(st - 1, p0, p1, fl && a[st] == num, 0));
        }
    }
    if(fl == 0 && ld == 0){
        f1[st][p0][p1] = res;
    }
    return res;
}
int f2[maxn][4][3];
int dfsf2(int st, int p0, int p1, bool fl, bool ld){
    if(ld == 0 && fl == 0 && f2[st][p0][p1] >= 0) return f2[st][p0][p1];
    if(st == 0){
        return p0 == 3;
    }
    int res = 0;
    if(ld){
        upd(res, dfsf2(st - 1, p0, p1, 0, ld));
    }
    if(p0 == 0){
        int num = (p1 == 0 ? 8 : (p1 == 1 ? 0 : 1));
        if(fl == 0 || num <= a[st]){
            if(p1 == 1){
                upd(res, dfsf2(st - 1, p0, p1, fl && a[st] == num, 0));
                upd(res, dfsf2(st - 1, p0, p1 + 1, fl && a[st] == num, 0));
            } else if(p1 != 1){
                upd(res, dfsf2(st - 1, (p1 == 2 ? 3 : p0), (p1 + 1) % 3, fl && a[st] == num, 0));
            }
        }
    }
    if(p0 == 1){
        int num = (p1 == 0 ? 8 : 1);
        if(fl == 0 || num <= a[st]){
            upd(res, dfsf2(st - 1, (p1 == 1 ? 3 : p0), (p1 + 1) & 1, fl && a[st] == num, 0));
        }
    }
    if(p0 == 2){
        int num = 1;
        if(fl == 0 || num <= a[st]){
            upd(res, dfsf2(st - 1, 3, 0, fl && a[st] == num, 0));
        }
    }
    if(p0 == 3){
        for(int i = 0;i < 4;i++){
            if(fl && dar[i] > a[st]) continue;
            if(ld && dar[i] == 0) continue;
            upd(res, dfsf2(st - 1, p0, p1, fl && (a[st] == dar[i]), 0));
        }
    }
    if(ld == 0 && fl == 0){
        f2[st][p0][p1] = res;
    }
    return res;
}
int f3[maxn][5][6];
int dfsf3(int st, int p0, int p1, bool fl, bool ld){
    if(ld == 0 && fl == 0 && f3[st][p0][p1] >= 0) return f3[st][p0][p1];
    if(st == 0){
        return p0 == 4;
    }
    int res = 0;
    if(ld){
        upd(res, dfsf3(st - 1, p0, p1, 0, ld));
    }
    if(p0 == 0){
        int num = 6;
        if(fl == 0 || num <= a[st]){
            if(p1 < 3){
                upd(res, dfsf3(st - 1, 1, p1 + 1, fl && a[st] == num, 0));
                upd(res, dfsf3(st - 1, 0, p1 + 1, fl && (a[st] == num), 0));
                upd(res, dfsf3(st - 1, 2, 0, fl && a[st] == num, 0));
            }
        }
    }
    if(p0 == 1){
        int num = 0;
        if(ld == 0 && p1 < 5){
            upd(res, dfsf3(st - 1, 1, p1 + 1, fl && (a[st] == num), 0));
            upd(res, dfsf3(st - 1, 2, 0, fl && (a[st] == num), 0));
        }
    }
    if(p0 == 2){
        int num = 4;
        if(fl == 0 || num <= a[st]){
            upd(res, dfsf3(st - 1, 3, 0, fl && a[st] == num, 0));
        }
    }
    if(p0 == 3){
        int num = 9;
        if(fl == 0 || num <= a[st]){
            upd(res, dfsf3(st - 1, 4, 0, fl && a[st] == num, 0));
        }
    }
    if(p0 == 4){
        for(int i = 0;i < 4;i++){
            if(fl && dar[i] > a[st]) continue;
            if(ld && dar[i] == 0) continue;
            upd(res, dfsf3(st - 1, p0, p1, fl && (a[st] == dar[i]), 0));
        }
    }
    if(ld == 0 && fl == 0){
        f3[st][p0][p1] = res;
    }
    return res;
}
int getsolve(){
    memset(f0, -1, sizeof(f0)); memset(f1, -1, sizeof(f1));
    memset(f2, -1, sizeof(f2)); memset(f3, -1, sizeof(f3));
    int ans = 0;
    for(int i = 0;i <= 2;i++){
        upd(ans, dfsf0(n, i, 0, 1, 1));
    }
    // cerr << ans << endl;
    for(int i = 0;i <= 2;i++){
        upd(ans, dfsf1(n, i, 0, 1, 1));
    }
    // cerr << ans << endl;
    for(int i = 0;i <= 2;i++){
        upd(ans, dfsf2(n, i, 0, 1, 1));
    }
    upd(ans, dfsf3(n, 0, 0, 1, 1));
    // cerr << ans << endl;
    upd(ans, dfsf0(n, 3, 0, 1, 1));
    // cerr << ans << endl;
    return ans;
}
int main(){
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--){
        cin >> (sl + 1) >> (sr + 1);
        n = strlen(sr + 1);
        for(int i = 1;i <= n;i++){
            a[n - i + 1] = sr[i] - '0';
        }
        int ans = getsolve();
        n = strlen(sl + 1);
        // cerr << (sl + 1) << endl;
        for(int i = 1;i <= n;i++){
            a[n - i + 1] = sl[i] - '0';
        }
        a[1]--;
        int now = 1;
        while(a[now] < 0){
            a[now + 1] -= 1; a[now] += 10; now++;
        }
        while(n > 0 && a[n] == 0) n--;
        upd(ans, mod - getsolve());
        cout << ans << '\n';
    }
    cout.flush(); return 0;
}
