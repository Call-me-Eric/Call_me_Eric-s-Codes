## 关于 `Day7 T3` 的 $O(n\sqrt n) 算法$

**注：下面的块长默认为 $O(\sqrt n)$，且 $n$ 和 $q$ 同阶**

首先我们观察到 $O(n\sqrt n\log n)$ 算法的瓶颈在于查询第 $k$ 大值二分的部分，因为二分不能和分块很好的结合。所以我们需要探寻另外的查询第 $k$ 大值的方法。

### 我们先只考虑只有操作 $2$ 的做法。

先考虑单独一个块查询第 $k$ 大的做法，我们使用值域分块。 值域分块上我们记录这个块在每一个值域的分块上每一个数的出现次数，当查询的时候直接暴力先跳块再跳零散部分，就可以有 $O(\sqrt n)$ 的查询最大值的方法了。

我们再考虑多个连续的块上查询第 $k$ 大的做法，我们只要求每个值在序列分块的前缀和和每个值域分块在序列分块上的前缀和，我们这样就可以求出这几个连续的块上每个值和值域分块内的元素的总出现次数。这部分时间复杂度为 $O(\sqrt n)$ ，。

我们最后再考虑零散部分怎么查询，其实我们可以直接可以对这些零散元素新建一个值域分块，然后丢进**多个连续的块**里进行查询，这部分复杂度 $O(\sqrt n)$ 。

这样我们就有一个预处理 $O(n\sqrt n)$ ，单次查询 $O(\sqrt n)$ 的做法了。

### 我们再考虑有操作 $1$ 的做法。
因为对于每个块中有 $O(\sqrt n)$ 不同的元素，所以我们这时就有一个想法就是对于每一次操作 $1$，我们只要使每个块中会被出现次数会被修改的元素暴力修改会影响的前缀和就行。

但是这时我们考虑到对于每一块中如果有元素的出现次数产生修改，就相当于在每一个块中减去一些元素加上 `min`，如果直接暴力修改的话我们考虑势能分析。因为所有块总共有 $O(n)$ 个不同的数，每一次询问会给每个块增加一个元素，所以此时暴力修改的总共复杂度为 $O(n\sqrt n +n^2)$，当然由于这道题时间限制比较宽松，你可以通过调块长通过这道题且通过极限数据，但是这并不是我们想要的 $O(\sqrt n)$ 的做法。

我们观察到这道题修改有且仅有取 `min`，我们就考虑到如果这次修改对这个块有效果的话 $min$ 必定是最大值。所以我们可以单独统计这个块中最大值和其出现次数，不加入这个出现次数的前缀和，查询时再把这些最大值出现次数加入零散部分组成的值域分块中，这样插入的复杂度是 $O(\sqrt n)$ ，而且修改时整块并不会增加上一个数，且只有零散部分会加上这个 `min`，所以包括修改和原序列最多只会产生 $n+2q$ 个不同的数，这个对于我们来说只要暴力修改块之间值域前缀和即可，复杂度为 $O(n\sqrt n)$ 。

我们再考虑零散部分，我们只要先统计一遍需要修改的数和及其出现次数。统计完再进行暴力修改块之间值域前缀和。**如果直接修改复杂度是错误的**。这边的复杂度为 $O(n\sqrt n)$ 。

所以我们这样我们就有 $O(n\sqrt n)$ 的分块做法通过此题了。

**欢迎提供更为优秀复杂度的算法。**

### 参考程序：
```cpp
/**
 *    unicode:  UTF-8
 *    name:     打怪兽
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Changle District, Fuzhou City, Fujian Province, China
 *    created:  2023.02.03 周五 13:39:47 (Asia/Shanghai)
 *    standard: c++17
 **/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <list>
typedef long long ll;
typedef unsigned long long ull;
constexpr auto lowbit = [](const auto &x)
{ return x & (-x); };

// #define FAST_IO

#if !defined(WIN32) && !defined(_WIN32)
#define getchar getchar_unlocked

#define putchar putchar_unlocked

#endif
namespace IO
{
#ifdef FAST_IO
#ifndef FAST_IN
#define FAST_IN

#endif
#ifndef FAST_OUT
#define FAST_OUT

#endif
#endif

    namespace INPUT
    {
#ifdef FAST_IN
#ifndef FAST_OUT_BUFFER_SIZE
#define FAST_OUT_BUFFER_SIZE (1 << 21)

#endif
        char _buf[FAST_OUT_BUFFER_SIZE], *_now = _buf, *_end = _buf;
#undef getchar
#define getchar() (_now == _end && (_end = (_now = _buf) + fread(_buf, 1, FAST_OUT_BUFFER_SIZE, stdin), _now == _end) ? EOF : *_now++)

#else
#if !defined(WIN32) && !defined(_WIN32)
#define getchar getchar_unlocked

#endif
#endif
        inline void read(char &_x)
        {
            char _s = (char)getchar();
            while ((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20))
                _s = (char)getchar();
            _x = _s;
        }
        inline int read(char *_x)
        {
            char _s = (char)getchar();
            int _len = 0;
            while ((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20))
                _s = (char)getchar();
            while (!((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20)))
            {
                _x[_len++] = _s;
                _s = (char)getchar();
            }
            _x[_len] = '\0';
            return _len;
        }
        template <typename _T>
        inline void read(_T &_x)
        {
            _x = 0;
            char _s = (char)getchar();
            bool _f = false;
            while (!(_s >= '0' && _s <= '9'))
            {
                if (_s == '-')
                    _f = true;
                _s = (char)getchar();
            }
            while (_s >= '0' && _s <= '9')
            {
                _x = (_x << 1) + (_x << 3) + _s - '0';
                _s = (char)getchar();
            }
            if (_f)
                _x = -_x;
        }
        template <typename _T, typename... _G>
        inline void read(_T &_x, _G &..._y)
        {
            read(_x);
            read(_y...);
        }
#ifdef FAST_IN
#undef getchar
#if !defined(WIN32) && !defined(_WIN32)
#define getchar getchar_unlocked

#endif
#endif
    }
    namespace OUTPUT
    {
#ifdef FAST_OUT
#ifndef FAST_OUT_BUFFER_SIZE
#define FAST_OUT_BUFFER_SIZE (1 << 21)

#endif
        char _buf[FAST_OUT_BUFFER_SIZE], *_now = _buf;
        inline void flush()
        {
            fwrite(_buf, 1, _now - _buf, stdout), _now = _buf;
        }
#undef putchar
#define putchar(c) (_now - _buf == FAST_OUT_BUFFER_SIZE ? flush(), *_now++ = c : *_now++ = c)

#else
#if !defined(WIN32) && !defined(_WIN32)
#define putchar putchar_unlocked

#endif
#endif
        inline void write(char _x)
        {
            putchar(_x);
        }
        inline void write(char *const _x)
        {
            for (int i = 0; _x[i]; ++i)
                putchar(_x[i]);
        }
        inline void write(const char *__restrict _x)
        {
            for (int i = 0; _x[i]; ++i)
                putchar(_x[i]);
        }
        template <typename _T>
        inline void write(_T _x)
        {
            static char dight[39];
            int _len = 0;
            if (_x == 0)
            {
                putchar('0');
                return;
            }
            bool flag = false;
            if (_x < 0)
            {
                _x = -_x;
                flag = true;
            }
            while (_x)
            {
                dight[_len++] = (char)(_x % 10) + '0';
                _x /= 10;
            }
            if (flag)
                putchar('-');
            while (_len--)
                putchar(dight[_len]);
        }
        template <typename _T, typename... _G>
        inline void write(_T _x, _G... _y)
        {
            write(_x);
            write(_y...);
        }
#ifdef FAST_OUT
#undef putchar
#if !defined(WIN32) && !defined(_WIN32)
#define putchar putchar_unlocked

#endif
#endif
    }
}
template <typename T>
inline void ckmin(T &_x, T _y)
{
    if (_x > _y)
        _x = _y;
}
template <typename T>
inline void ckmax(T &_x, T _y)
{
    if (_x < _y)
        _x = _y;
}
template <const int _mod>
struct modint
{
    int x;
    constexpr modint(int _x = 0) : x(_x) {}
    constexpr inline modint operator+() const
    {
        return *this;
    }
    constexpr inline modint operator-() const
    {
        return !x ? 0 : _mod - x;
    }
    constexpr inline modint &operator++()
    {
        ++x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    constexpr inline modint &operator--()
    {
        --x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    constexpr inline modint operator++(int)
    {
        int res = x;
        if (x >= _mod)
            x -= _mod;
        return res;
    }
    constexpr inline modint operator--(int)
    {
        int res = x;
        if (x < 0)
            x += _mod;
        return res;
    }
    constexpr inline modint operator+(const modint &rhs) const
    {
        int res = x;
        res += rhs.x;
        if (res >= _mod)
            res -= _mod;
        return res;
    }
    constexpr inline modint operator-(const modint &rhs) const
    {
        int res = x;
        res -= rhs.x;
        if (res < 0)
            res += _mod;
        return res;
    }
    constexpr inline modint operator*(const modint &rhs) const
    {
        return (int)((ll)x * rhs.x % _mod);
    }
    constexpr inline modint &operator+=(const modint &rhs)
    {
        x += rhs.x;
        if (x >= _mod)
            x -= _mod;
        return *this;
    }
    constexpr inline modint &operator-=(const modint &rhs)
    {
        x -= rhs.x;
        if (x < 0)
            x += _mod;
        return *this;
    }
    constexpr inline modint &operator*=(const modint &rhs)
    {
        x = (int)((ll)x * rhs.x % _mod);
        return *this;
    }
    template <typename _G>
    constexpr inline modint operator^(_G rhs) const
    {
        modint a = x, res = 1;
        while (rhs)
        {
            if (rhs & 1)
                res *= a;
            a *= a;
            rhs >>= 1;
        }
        return res;
    }
    constexpr inline modint inv() const
    {
        return *this ^ (_mod - 2);
    }
    constexpr inline modint operator/(const modint &rhs) const
    {
        return (*this) * rhs.inv();
    }
    constexpr inline modint &operator/=(const modint &rhs)
    {
        return (*this) *= rhs.inv();
    }
    constexpr inline modint &operator==(const modint &rhs)
    {
        return x == rhs.x;
    }
    constexpr inline int &data()
    {
        return x;
    }
};
template <typename _T, const int MAXN, const int MAXM>
struct Graph
{
    struct Edge
    {
        int next;
        _T to;
    } edge[MAXM];
    int head[MAXN], num_edge;
    inline void add_edge(int from, _T to)
    {
        edge[++num_edge].next = head[from];
        edge[num_edge].to = to;
        head[from] = num_edge;
    }
#define foreach(i, graph, u) for (int i = graph.head[u]; i; i = graph.edge[i].next)
};
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 8e4 * 2 + 5;
constexpr int M = 405;
int n, m;
int a[N], b[N], c[N];
int p[N], tot;
struct Query
{
    int opt, l, r, x;
} q[N];
struct node
{
    int block, num;
    int L[M], R[M];
    int belong[N];
    inline void init(int _n)
    {
        block = (int)__builtin_sqrt(_n);
        num = (_n - 1) / block + 1;
        for (int i = 1; i <= num; ++i)
        {
            L[i] = R[i - 1] + 1;
            R[i] = min(R[i - 1] + block, _n);
            for (int j = L[i]; j <= R[i]; ++j)
                belong[j] = i;
        }
    }
    inline int left(int x)
    {
        return L[belong[x]];
    }
    inline int right(int x)
    {
        return R[belong[x]];
    }
} seq, value;
int cnt[M][N], cntblock[M][M];
list<int> have[M][M];
inline void _update(int _bel, int _val, int _add)
{
    for (int i = _bel; i <= seq.num; ++i)
    {
        cnt[i][_val] += _add;
        cntblock[i][value.belong[_val]] += _add;
    }
};
int vis[N], vistime;
int st[N], stcnt[N], where[N], top;
inline void updatein(int l, int r, int val)
{
    int bel = seq.belong[l];
    if (b[bel] > val)
    {
        int res = 0;
        ++vistime;
        for (int i = l; i <= r; ++i)
        {
            if (a[i] > val)
            {
                int v = min(a[i], b[bel]);
                if (v == b[bel])
                    --c[bel];
                else
                {
                    if (vis[v] != vistime)
                    {
                        st[where[v] = ++top] = v;
                        stcnt[top] = 1;
                        vis[v] = vistime;
                    }
                    else
                        ++stcnt[where[v]];
                }
                ++res;
                a[i] = val;
            }
        }
        if (res)
        {
            while (top)
            {
                _update(bel, st[top], -stcnt[top]);
                --top;
            }
            _update(bel, val, res);
            for (int i = 1; i <= value.num; ++i)
                for (auto it = have[bel][i].begin(); it != have[bel][i].end();)
                    if (cnt[bel][*it] - cnt[bel - 1][*it] == 0)
                        it = have[bel][i].erase(it);
                    else
                        ++it;
            auto &li = have[bel][value.belong[val]];
            bool flag = true;
            for (auto it = li.begin(); it != li.end(); ++it)
            {
                if (*it == val)
                {
                    flag = false;
                    break;
                }
                if (*it > val)
                {
                    li.insert(it, val);
                    flag = false;
                    break;
                }
            }
            if (flag)
                li.push_back(val);
        }
    }
}
inline void cover(int bel, int val)
{
    int &res = c[bel];
    for (int i = value.belong[val] + 1; i <= value.belong[b[bel]]; ++i)
    {
        res += cntblock[bel][i] - cntblock[bel - 1][i];
        for (int j : have[bel][i])
            _update(bel, j, cnt[bel - 1][j] - cnt[bel][j]);
        have[bel][i].clear();
    }
    auto &li = have[bel][value.belong[val]];
    while (!li.empty() && li.back() > val)
    {
        res += cnt[bel][li.back()] - cnt[bel - 1][li.back()];
        _update(bel, li.back(), cnt[bel - 1][li.back()] - cnt[bel][li.back()]);
        li.pop_back();
    }
    b[bel] = val;
}
inline void updateout(int l, int r, int val)
{
    for (int i = l; i <= r; ++i)
    {
        if (b[i] > val)
            cover(i, val);
    }
}
inline void update(int l, int r, int val)
{
    if (seq.belong[l] == seq.belong[r])
    {
        updatein(l, r, val);
        return;
    }
    updatein(l, seq.right(l), val);
    updateout(seq.belong[l] + 1, seq.belong[r] - 1, val);
    updatein(seq.left(r), r, val);
}
inline int _query(int l, int r, int k)
{
    for (int i = 1; i <= value.num; ++i)
    {
        int now = cntblock[r][i] - cntblock[l][i] + cntblock[0][i];
        if (k <= now)
        {
            for (int j = value.L[i]; j <= value.R[i]; ++j)
            {
                now = cnt[r][j] - cnt[l][j] + cnt[0][j];
                if (k <= now)
                    return j;
                else
                    k -= now;
            }
        }
        else
            k -= now;
    }
    return 0;
}
inline int query(int l, int r, int k)
{
    if (seq.belong[l] == seq.belong[r])
    {
        for (int i = l; i <= r; ++i)
        {
            int v = min(a[i], b[seq.belong[i]]);
            ++cnt[0][v];
            ++cntblock[0][value.belong[v]];
        }
        int res = _query(0, 0, k);
        for (int i = l; i <= r; ++i)
        {
            int v = min(a[i], b[seq.belong[i]]);
            --cnt[0][v];
            --cntblock[0][value.belong[v]];
        }
        return res;
    }
    for (int i = l; i <= seq.right(l); ++i)
    {
        int v = min(a[i], b[seq.belong[i]]);
        ++cnt[0][v];
        ++cntblock[0][value.belong[v]];
    }
    for (int i = seq.belong[l] + 1; i < seq.belong[r]; ++i)
    {
        cnt[0][b[i]] += c[i];
        cntblock[0][value.belong[b[i]]] += c[i];
    }
    for (int i = seq.left(r); i <= r; ++i)
    {
        int v = min(a[i], b[seq.belong[i]]);
        ++cnt[0][v];
        ++cntblock[0][value.belong[v]];
    }
    int res = _query(seq.belong[l], seq.belong[r] - 1, k);
    for (int i = l; i <= seq.right(l); ++i)
    {
        int v = min(a[i], b[seq.belong[i]]);
        --cnt[0][v];
        --cntblock[0][value.belong[v]];
    }
    for (int i = seq.belong[l] + 1; i < seq.belong[r]; ++i)
    {
        cnt[0][b[i]] -= c[i];
        cntblock[0][value.belong[b[i]]] -= c[i];
    }
    for (int i = seq.left(r); i <= r; ++i)
    {
        int v = min(a[i], b[seq.belong[i]]);
        --cnt[0][v];
        --cntblock[0][value.belong[v]];
    }
    return res;
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("segment.in", "r", stdin);
    freopen("segment.out", "w", stdout);
#endif
    read(n, m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        p[++tot] = a[i];
    }
    for (int i = 1; i <= m; ++i)
    {
        auto &[opt, l, r, x] = q[i];
        read(opt, l, r, x);
        if (opt == 1)
            p[++tot] = x;
    }
    sort(p + 1, p + 1 + tot);
    tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
    seq.init(n), value.init(tot);
    for (int i = 1; i <= seq.num; ++i)
    {
        b[i] = tot;
        for (int j = seq.L[i]; j <= seq.R[i]; ++j)
        {
            a[j] = (int)(lower_bound(p + 1, p + 1 + tot, a[j]) - p);
            ++cnt[i][a[j]];
            ++cntblock[i][value.belong[a[j]]];
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (cnt[i][j])
                have[i][value.belong[j]].push_back(j);
            cnt[i][j] += cnt[i - 1][j];
        }
        for (int j = 1; j <= value.num; ++j)
            cntblock[i][j] += cntblock[i - 1][j];
    }
    for (int i = 1; i <= m; ++i)
    {
        auto [opt, l, r, x] = q[i];
        if (opt == 1)
        {
            x = (int)(lower_bound(p + 1, p + 1 + tot, x) - p);
            update(l, r, x);
        }
        else
            write(p[query(l, r, x)], '\n');
    }
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}
```