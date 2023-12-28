#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 2e5 + 5, M = N << 1;
vector<int> to[N];
inline void add(int a, int b)
{
    to[a].push_back(b), to[b].push_back(a);
}
#define RING 2
#define FLOWER 3
#define LINE 1
static bool vis[N];
inline int calc(int st)
{
    if (vis[st])
        return 0;
    int sz = 0;
    queue<int> q;
    q.push(st);
    int deg[5]{};
    while (!q.empty())
    {
        int p = q.front();
        q.pop();
        vis[p] = 1, ++sz;
        //printf("%d\n",(int)to[p].size());
        if (to[p].size() >= 3)
            deg[3]++;
        else
            ++deg[to[p].size()];
        for (int i : to[p])
            if (!vis[i])
                q.push(i);
    }
    if (sz == 4 && deg[3] == 1 && deg[1] == 3)
        return RING;
    if (deg[3])
        return FLOWER;
    if (deg[1]+deg[0])
        return -sz;
    return RING;
}

int main()
{
    freopen("li.in", "r", stdin);
    freopen("li.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 1, a, b; i <= m; ++i)
        scanf("%d %d", &a, &b), add(a, b);
    int f = LINE;
    long long block = 0;
    int cnt=0;
    int ssz=0;
    for (int i = 1; i <= n; ++i)
    {
        if (vis[i])
            continue;
        ++cnt;
        if (i == 1929)
        {
            cerr << i;
        }
        int v = calc(i);
        if (v < 0)
            block += (1ll - v) * -v >> 1;
        f = max(f, v);
    }
    if (f == LINE)
    {
        printf("0 %lld\n", block);
    }
    else if (f == RING)
    {
        printf("1 %d\n", n);
    }
    else
        printf("-1\n");
    return 0;
}