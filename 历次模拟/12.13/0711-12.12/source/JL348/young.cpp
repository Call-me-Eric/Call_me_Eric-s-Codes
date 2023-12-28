#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int MAXN = 21;
int N, a[MAXN], M, b[MAXN], ans;
void dfs(int step, vector<int>vec, int Min) {
    if (step < Min) return ;
    if (!step) return ans++, void();
    while ((int)vec.size() and vec.back() == 0) vec.pop_back();
    vec.push_back(0);
    for (int i = 0; i < (int)vec.size(); i++) {
        if (i == 0 or vec[i] + 1 <= vec[i - 1]) {
            vec[i]++; int minn = Min;
            if (vec[i] > b[i]) minn++;
            else minn--;
            dfs(step - 1, vec, minn);
            vec[i]--;
        }
    }
    vec.pop_back();
    for (int i = 0; i < (int)vec.size(); i++) {
        if (i == (int)vec.size() - 1 or vec[i] - 1 >= vec[i + 1]) {
            vec[i]--; int minn = Min;
            if (vec[i] < b[i]) minn++;
            else minn--;
            dfs(step - 1, vec, minn);
            vec[i]++;
        }
    }
}
int main() {
    freopen("young.in", "r", stdin);
    freopen("young.out", "w", stdout);
    N = read();
    for (int i = 0; i < N; i++)
        a[i] = read();
    M = read();
    for (int i = 0; i < M; i++)
        b[i] = read();
    int Min = 0;
    for (int i = 0; i < max(N, M); i++)
        Min += abs(a[i] - b[i]);
    int Q = read(), K = read();
    vector<int>v;
    for (int i = 0; i < N; i++) v.emplace_back(a[i]);
    dfs(K, v, Min);
    printf("%d\n", ans);
}
