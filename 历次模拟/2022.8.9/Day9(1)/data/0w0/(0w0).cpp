#include <cstdio>
#include <cstring>

#define N 50055
#define getch for (ch=getchar(); ch<=32; ch=getchar())

char s[N];
int f[N*4][5][5],ans[5][5],tmpans[5][5],len[N*4],cv[N*4],n,m,ch,x,y;

void read(int &x)
{
    getch;
    for (x=0; ch>32; ch=getchar()) x = x*10+ch-48;
}

void merge(int src1[5][5], int src2[5][5], int dst[5][5])
{
    int i,j,k;
    for (i=0; i<=4; ++i)
    for (j=i; j<=4; ++j)
    {
        dst[i][j] = src1[i][j]+src2[i][j];
        for (k=i; k<j; ++k) dst[i][j] += src1[i][k]*src2[k+1][j];
    }
}

void build(int l, int r, int t)
{
    len[t] = r-l+1;
    if (l == r)
    {
        if (s[l] == '(') f[t][0][0] = 1;
        else
        if (s[l] == '0') f[t][1][1] = f[t][3][3] = 1;
        else
        if (s[l] == 'w') f[t][2][2] = 1;
        else
        if (s[l] == ')') f[t][4][4] = 1;
        return;
    }
    int k = l+r>>1;
    build(l, k, t*2);
    build(k+1, r, t*2+1);
    merge(f[t*2], f[t*2+1], f[t]);
}

void downtag(int t)
{
    if (cv[t] == 0) return;
    if (t*2 < N*4) cv[t*2] = cv[t*2+1] = cv[t];
    int i,j;
    memset(f[t], 0, sizeof(f[t]));
    if (cv[t] == '(') f[t][0][0] = len[t];
    else
    if (cv[t] == '0') f[t][1][1] = f[t][3][3] = len[t];
    else
    if (cv[t] == 'w') f[t][2][2] = len[t];
    else
    if (cv[t] == ')') f[t][4][4] = len[t];
    cv[t] = 0;
}

void modify(int l, int r, int t)
{
    if (x<=l && r<=y)
    {
        cv[t] = ch;
        downtag(t);
        return;
    }
    downtag(t*2), downtag(t*2+1);
    int k = l+r>>1;
    if (x <= k) modify(l, k, t*2);
    if (y > k) modify(k+1, r, t*2+1);
    merge(f[t*2], f[t*2+1], f[t]);
}

void query(int l, int r, int t)
{
    if (x<=l && r<=y)
    {
        merge(ans, f[t], tmpans);
        memcpy(ans, tmpans, sizeof(tmpans));
        return;
    }
    downtag(t*2), downtag(t*2+1);
    int k = l+r>>1;
    if (x <= k) query(l, k, t*2);
    if (y > k) query(k+1, r, t*2+1);
}

int main()
{
    freopen("(0w0)10.in", "r", stdin);
    freopen("(0w0)10.out", "w", stdout);
    scanf("%d%d", &n, &m);
    scanf("%s", s+1);
    build(1, n, 1);
    while (m--)
    {
        getch;
        if (ch == 'A')
        {
            read(x);
            y = x;
            getch;
            modify(1, n, 1);
        }
        else
        if (ch == 'B')
        {
            read(x), read(y);
            getch;
            modify(1, n, 1);
        }
        else
        if (ch == 'C')
        {
            read(x), read(y);
            memset(ans, 0, sizeof(ans));
            query(1, n, 1);
            printf("%u\n", ans[0][4]);
        }
    }
    return 0;
}

