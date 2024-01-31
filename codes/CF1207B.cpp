#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f  = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch= getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 51;
int a[maxn][maxn],b[maxn][maxn],n, m;
bool book[maxn][maxn];
vector<pair<int,int> > vec;
signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            a[i][j] = read();
    for(int i = 0;i <= n;i++)a[i][0] = 1;
    for(int i = 0;i <= m;i++)a[0][i] = 1;
    for(int i = 2;i <= n;i++)
        for(int j = 2;j <= m;j++)
            if(a[i][j] && a[i - 1][j] && a[i][j - 1] && a[i - 1][j - 1]){
                book[i][j] = 1;
            }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            if(book[i][j]){
                b[i][j] = b[i - 1][j] = b[i][j - 1] = b[i - 1][j - 1] = 1;
            }
    int ans = 0;
    for(int i = 1;i <= n && ans != -1;i++)
        for(int j = 1;j <= m;j++){
            if(a[i][j] != b[i][j]){ans = -1;break;}
            if(book[i][j]){ans++;vec.push_back(make_pair(i,j));}
        }
    if(ans != -1){
        printf("%d\n",ans);
        for(auto i : vec){printf("%d %d\n",i.first - 1,i.second - 1);}
    }
    else puts("-1");
    return 0;
}