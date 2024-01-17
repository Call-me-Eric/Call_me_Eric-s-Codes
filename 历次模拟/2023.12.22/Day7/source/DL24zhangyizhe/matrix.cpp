# include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
int n , m , a[N][N] , b[N];
vector< int > ans[110];

struct Ask
{
    int q , id;
} q[N];

struct matrix
{
    int g[400][400];
    int (&operator [] (int const x)) [400] {return g[x];}
    int const (&operator [] (int const x) const) [400] {return g[x];}
    matrix() {}
    matrix(int opt) 
    {
        for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) 
        {
            g[i][j] = 0;
            if(i == j) g[i][j] = opt;
        }
    }
    matrix operator * (matrix const &rhs)
    {
        matrix res(0);
        for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) for(int k = 1; k <= n; k++)
            res[i][j] = (res[i][j] ^ (g[i][k] & rhs[k][j]));
        return res;
    }
} A , B(0);

matrix ksm(matrix x , int y)
{
    matrix res = x;
    y--;
    for(; y; y >>= 1)
    {
        if(y & 1) res = res * x;
        x = x * x;
    }
    return res;
}

int main()
{
    freopen("matrix.in" , "r" , stdin);
    freopen("matrix.out" , "w" , stdout);
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            char c;
            cin >> c;
            if(c == '1') a[i][j] = 1;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        char c;
        cin >> c;
        if(c == '1') b[i] = 1;
    }
    cin >> m;
    for(int i = 1; i <= m; i++) 
    {
        cin >> q[i].q;
        q[i].id = i;
    }
    sort(q + 1 , q + m + 1 , [](Ask a , Ask b) {return a.q < b.q;});
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) A[i][j] = a[i][j];
    for(int i = 1; i <= n; i++) B[1][i] = b[i];
    // for(int i = 1; i <= m; i++)
    // {
    //     matrix res;
    //     if(q[i].q)
    //     {
    //         res = ksm(A , q[i].q);
    //         for(int j = 1; j <= n; j++)
    //         {
    //             int tmp = 0;
    //             for(int k = 1; k <= n; k++) tmp ^= res[j][k] & b[k];
    //             ans[q[i].id].push_back(tmp);
    //         }
    //     }
    //     else for(int j = 1; j <= n; j++) ans[q[i].id].push_back(b[j]);
    // }
    matrix now = A;
    for(int i = 1 , flag = 0; i <= m; i++)
    {
        if(!q[i].q) for(int j = 1; j <= n; j++) ans[q[i].id].push_back(b[j]);
        else
        {
            if(flag)
            {
                if(q[i].q != q[i - 1].q) now = now * ksm(A , q[i].q - q[i - 1].q);
            }
            else
            {
                if(q[i].q > 1) now = now * ksm(A , q[i].q - 1);
                flag = 1; 
            } 
            for(int j = 1; j <= n; j++)
            {
                int tmp = 0;
                for(int k = 1; k <= n; k++) tmp ^= now[j][k] & b[k];
                ans[q[i].id].push_back(tmp);
            }
        }
    }
    for(int i = 1; i <= m; i++) 
    {
        for(auto x : ans[i]) cout << x;
        cout << '\n';
    }
    return 0;
}