#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
int r, g, b, m; int n = 0;
int epu[maxn], epv[maxn];
vector<int> eg[maxn];
mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());
int rnd(int l, int r){
    return l + mtrnd() % (r - l + 1);
}
int fa[maxn];
void init(){
    for(int i = 1;i <= n;i++) fa[i] = i;
    return ;
}
int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y){
    fa[find(x)] = find(y); return ;
}
bool vis[maxn];
int main(){
    freopen("rgb.in", "r", stdin);
    freopen("rgb.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> r >> g >> b >> m;
    n = r + g + b + 1;
    for(int i = 1;i <= m;i++){
        cin >> epu[i] >> epv[i];
        char ch; cin >> ch;
        if(ch == 'r'){
            eg[0].push_back(i);
        } else if(ch == 'g'){
            eg[1].push_back(i);
        } else if(ch == 'b'){
            eg[2].push_back(i);
        }
    }
    int P = 30000000 / max(m, 1);
    while(P--){
        init();
        for(int i = 1;i <= m;i++) vis[i] = 0;
        for(int j = 0;j < 3;j++){
            for(int i = 1;i < eg[j].size();i++){
                swap(eg[j][i], eg[j][rnd(0, i)]);
            }
        }
        int rcnt = 0; int cnt = 0;
        for(auto t : eg[0]){
            if(rcnt == r) break;
            int ru = find(epu[t]); int rv = find(epv[t]);
            if(ru == rv) continue;
            cnt++; rcnt++; fa[ru] = rv; vis[t] = 1;
        }
        rcnt = 0;
        for(auto t : eg[1]){
            if(rcnt == g) break;
            int ru = find(epu[t]); int rv = find(epv[t]);
            if(ru == rv) continue;
            cnt++; rcnt++; fa[ru] = rv; vis[t] = 1;
        }
        rcnt = 0;
        for(auto t : eg[2]){
            if(rcnt == b) break;
            int ru = find(epu[t]); int rv = find(epv[t]);
            if(ru == rv) continue;
            cnt++; rcnt++; fa[ru] = rv; vis[t] = 1;
        }
        if(cnt == n - 1){
            cout << "YES" << '\n';
            for(int i = 1;i <= m;i++) cout << vis[i];
            cout << '\n'; cout.flush(); return 0;
        }
    }
    cout << "NO" << endl; return 0;
}
