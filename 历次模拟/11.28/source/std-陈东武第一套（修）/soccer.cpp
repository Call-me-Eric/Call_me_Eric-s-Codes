#include <bits/stdc++.h>
using namespace std;
#define maxn 5000010
inline int read()
{
    int sum = 0, fh = 1;
    char c = getchar();
    while (c > '9' || c < '0')
    {
        if (c == '-')
            fh = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        sum *= 10;
        sum += c - '0';
        c = getchar();
    }
    return sum * fh;
}
int n, l[maxn], r[maxn], tot = 0;
char s[maxn];
bool flag = false;
void check(int m)
{
    int top = 0, p[maxn];
    for (int i = 1; i <= tot; i++)
    {
        int lim = l[i] - r[i - 1] - 1 - m - 1;
        if (lim < 0)
            return;
        if (lim == 1)
            return;
        if (lim > 0)
        {
            if (m)
            {
                for (int j = 1; j <= lim / 2; j++)
                {
                    p[++top] = 1;
                }
                if (lim % 2)
                {
                    if (m > 1)
                        top--, p[++top] = 2;
                    else
                        return;
                }
            }
            else
                return;
        }
        p[++top] = r[i] - l[i] + 1 + m;
    }
    //	cout<<top<<endl;
    //	for(int i=1;i<=top;i++){
    //		cout<<p[i]<<" ";
    //	}
    //	cout<<endl;
    int lim = n - r[tot] - m;
    if (lim < 0)
        return;
    if (lim == 1)
        return;
    if (lim > 0)
    {
        if (m)
        {
            for (int j = 1; j <= lim / 2; j++)
            {
                p[++top] = 1;
            }
            if (lim % 2)
            {
                if (m > 1)
                    top--, p[++top] = 2;
                else
                    return;
            }
        }
        else
            return;
    }
    flag = true;
    cout << "Yes\n";
    int cur = 0;
    for (int i = 1; i <= top; i++)
    {
        for (int j = 1; j <= p[i]; j++)
            cout << 'B', cur++;
        if (i != top)
            cout << 'R', cur++;
    }
    while (cur < n)
        cout << 'R', cur++;
    cout << "\n";
    return;
}
int main()
{
    freopen("soccer.in", "r", stdin);
    freopen("soccer.out", "w", stdout);
    cin >> n;
    cin >> s + 1;
    ;
    int m = n;
    r[0] = -1;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == '1')
        {
            l[++tot] = i;
            r[tot] = i;
            while (s[r[tot] + 1] == '1')
            {
                r[tot]++;
            }
            i = r[tot] + 1;
            m = min(m, l[tot] - r[tot - 1]);
        }
    }
    if (tot == 0)
    {
        cout << "Yes\n";
        for (int i = 1; i <= n; i++)
            cout << 'R';
        cout << '\n';
        return 0;
    }
    m = min(m, n - r[tot]);
    m = min(m, 4);
    for (int i = 0; i <= m; i++)
    {
        check(i);
        if (flag)
        {
            return 0;
        }
    }
    puts("No");
    return 0;
}