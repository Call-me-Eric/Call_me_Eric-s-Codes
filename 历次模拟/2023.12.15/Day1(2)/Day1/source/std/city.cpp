#include<bits/stdc++.h>
#define MAXN 101
using namespace std;

long long MOD = 22222223;
long long ans = 1;
long long C[MAXN][MAXN];

int n , m , a , b , c , d , val;
long long x[MAXN];
long long y[MAXN];

long long dp[MAXN][MAXN];

int used1[MAXN * MAXN];
int used2[MAXN * MAXN];
int z;

int cmp(const void *u , const void *v)
{
    return *(int*)u - *(int*)v;
}

long long power(long long X , long long p)
{
    long long ret = 1;
    while(p)
    {
        if(p % 2 == 1)
            ret = (ret * X) % MOD;
        X = (X * X) % MOD;
        p /= 2;
    }
    return ret;
}

long long dodp(int nowline , int left)
{
    if(nowline == a + c + 1)
    {
        if(left == 0)
            return 1;
        else
            return 0;
    }
    else
    {
        if(dp[nowline][left] >= 0)
            return dp[nowline][left];
        long long ret = 0;
        int free;
        if(nowline <= a)
            free = b + d - left;
        else
            free = b - left;
        for(int i = 1 ; i <= left ; i++)
        {
            long long t = 1;
            t = (t * C[left][i]) % MOD;
            t = (t * power(val , free)) % MOD;
            t = (t * power(val - 1 , left - i)) % MOD;
            t = (t * dodp(nowline + 1 , left - i)) % MOD;
            ret += t;
        }
        ret = (ret + (( power(val , free) * power(val - 1 , left) )% MOD) * dodp(nowline + 1 , left)) % MOD;
        if(nowline <= a)
            ret = (MOD + ret - (power(val - 1 , free + left) * dodp(nowline + 1 , left)) % MOD) % MOD;
        z++;
        used1[z] = nowline;
        used2[z] = left;
        dp[nowline][left] = ret;
        //cout<<"dp : "<<nowline<<" , "<<left<<" : "<<ret<<endl;
        return ret;
    }
}

long long solve()
{
    z = 0;
    long long ret = dodp(1 , b);
    for(int i = 1 ; i <= z ; i++)
        dp[used1[i]][used2[i]] = -1;
    return ret;
}

int main()
{
    int start = clock();
    freopen("city.in" , "r" , stdin);
    freopen("city.out" , "w" , stdout);
    ios::sync_with_stdio(false);
    memset(C , 0 , sizeof(C));
    memset(dp , 0xff , sizeof(dp));
    C[0][0] = 1;
    for(int i = 1 ; i < MAXN ; i++)
    {
        C[i][0] = 1;
        C[i][i] = 1;
        for(int j = 1 ; j < i ; j++)
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
    }
    cin>>n>>m;
    for(int i = 1 ; i <= n ; i++)
        cin>>x[i];
    for(int i = 1 ; i <= m ; i++)
        cin>>y[i];
    qsort(x + 1 , n , sizeof(x[0]) , cmp);
    qsort(y + 1 , m , sizeof(y[0]) , cmp);
    x[n+1] = ~0U>>1;
    y[m+1] = ~0U>>1;
    if(x[n] != y[m])
        cout<<"No solution!"<<endl;
    else
    {
        int p1 = 1 , p2 = 1;
        while(p1 <= n || p2 <= m)
        {
            val = min(x[p1] , y[p2]);
            a = 0 , b = 0;
            while(x[p1] == val)
                a ++ , p1 ++;
            while(y[p2] == val)
                b ++ , p2 ++;
            c = n - p1 + 1;
            d = m - p2 + 1;
            val ++;
            long long sol = solve();
            //cout<<a<<" "<<b<<" "<<c<<" "<<d<<" : "<<sol<<endl;
            ans = (ans * sol) % MOD;
        }
        cout<<ans<<endl;
    }
    //cout<<clock() - start<<" ms used."<<endl;
    return 0;
}
