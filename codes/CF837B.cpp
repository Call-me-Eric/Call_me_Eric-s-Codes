#include<bits/stdc++.h>
using namespace std;
const int maxn = 110;
int n, m;char ch[maxn][maxn];int a[maxn][maxn];
bool book[4];
bool check(int x,bool mod){
    if(mod){
        int col = a[1][m / 3 * x + 1];if(book[col])return 0;book[col] = 1;
        for(int i = 1;i <= n;i++){
            for(int j = m / 3 * x + 1;j <= m / 3 * (x + 1);j++){
                // printf("%d %d\n",i,j);
                if(a[i][j] != col)return false;
            }
        }
        return true;
    }
    else{
        int col = a[n / 3 * x + 1][1];if(book[col])return 0;book[col] = 1;
        for(int i = 1;i <= m;i++){
            for(int j = n / 3 * x + 1;j <= n / 3 * (x + 1);j++){
                if(a[j][i] != col)return false;
            }
        }
        return true;    
    }
}
signed main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        scanf("%s",ch[i] + 1);
        for(int j = 1;j <= m;j++)
            a[i][j] = (ch[i][j] == 'R' ? 1 : (ch[i][j] == 'G' ? 2 : 3));
    }
    bool ans = 0;
    if(m % 3 == 0){
        bool res = 1;memset(book,0,sizeof(book));
        for(int i = 0;i <= 2;i++)if(!check(i,1)){res = 0;break;}
        ans |= res;
    }
    if(n % 3 == 0){
        bool res = 1;memset(book,0,sizeof(book));
        for(int i = 0;i <= 2;i++)if(!check(i,0)){res = 0;break;}
        ans |= res;
    }
    puts(ans ? "YES" : "NO");
    return 0;
}