#include <cstdio>
#include <cstring>

#define N 50055
#define getch for (ch=getchar(); ch<=32; ch=getchar())

long long ans,al,ar;
char s[N];
int n,m,ch,x,y,i,j,k;

int main()
{
    freopen("input.in", "r", stdin);
    //freopen("bf.out", "w", stdout);
    scanf("%d%d", &n, &m);
    scanf("%s", s+1);
    while (m--)
    {
        getch;
        if (ch == 'A')
        {
            scanf("%d", &x);
            getch;
            s[x] = ch;
        }
        else
        if (ch == 'B')
        {
            scanf("%d%d", &x, &y);
            getch;
            for (i=x; i<=y; ++i) s[i] = ch;
        }
        else
        if (ch == 'C')
        {
            scanf("%d%d", &x, &y);
            ans = 0;
            for (i=x+2; i<=y-2; ++i)
            if (s[i] == 'w')
            {
                al = ar = 0;
                for (j=i-1; j>=x+1; --j)
                if (s[j] == '0')
                for (k=j-1; k>=x; --k)
                if (s[k] == '(') ++al;
                for (j=i+1; j<=y-1; ++j)
                if (s[j] == '0')
                for (k=j+1; k<=y; ++k)
                if (s[k] == ')') ++ar;
                ans += al*ar;
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}

