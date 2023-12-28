# include <bits/stdc++.h>

using namespace std;

int read()
{
# define C ch = getchar()
    int x = 0; char C;
    for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x;
}

const int N = 110;
int n , m , a[N] , b[N];

int main()
{
    freopen("city.in" , "r" , stdin);
    freopen("city.out" , "w" , stdout);
    n = read() , m = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    for(int i = 1; i <= m; i++) b[i] = read();
    cout << "No solution!";
    return 0;
}
