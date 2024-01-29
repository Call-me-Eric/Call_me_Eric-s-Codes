#include<bits/stdc++.h>
#define int long long
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline int getc(){
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
inline int redi() {
    int ret = 0,f = 0;char ch = getc();
    while (!isdigit (ch)) {
        if (ch == '-') f = 1;
        ch = getc();
    }
    while (isdigit (ch)) {
        ret = ret * 10 + ch - 48;
        ch = getc();
    }
    return f?-ret:ret;
}
#ifdef ONLINE_JUDGE
inline int read(){return redi();}
#else
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
#endif

const int maxn = 5e6 + 10;
int a[maxn][2], b[maxn][2];
int n;
const int dx[4] = {0,0,1};
const int dy[4] = {1,-1,0};
void dfs(int x,int y,int col){
    a[x][y] = -1;
    for(int i = 0;i < 3;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx > n || ny < 0 || ny > 1)continue;
        if(a[nx][ny] != col)continue;
        dfs(nx,ny,col);
    }
}
int solve(){
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        if(a[i][0] != a[i][1]){
            int x = a[i][0], y = a[i][1];
            if(y != a[i - 1][1]&& y != a[i + 1][1]){
                a[i][0] = -1;a[i][1] = x;cnt++;
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 0;j < 2;j++)
            if(a[i][j] != -1){dfs(i, j,a[i][j]);cnt++;}
    }
    return cnt;
}
signed main(){
    n = read();
    for(int i = 1;i <= n;i++)
        b[i][0] = a[i][0] = read();
    for(int i = 1;i <= n;i++)
        b[i][1] = a[i][1] = read();
    
    if(n == 1){
        if(a[1][0] != a[1][1])puts("2");
        else puts("1");
    }
    else{
        int ans = n * 2;
        a[0][0] = !a[1][0];a[0][1] = !a[1][1];
        a[n + 1][0] = !a[n][0];a[n + 1][1] = !a[n][1];
        ans = min(ans,solve());

        for(int i = 1;i <= n;i++)
            a[i][0] = b[i][0];
        for(int i = 1;i <= n;i++)
            a[i][1] = b[i][1];
        a[0][0] = !a[1][0];a[0][1] = !a[1][1];
        ans = min(ans,solve());
        
        for(int i = 1;i <= n;i++)
            a[i][0] = b[i][0];
        for(int i = 1;i <= n;i++)
            a[i][1] = b[i][1];
        a[n + 1][0] = !a[n][0];a[n + 1][1] = !a[n][1];
        ans = min(ans,solve());
        
        for(int i = 1;i <= n;i++)
            a[i][0] = b[i][0];
        for(int i = 1;i <= n;i++)
            a[i][1] = b[i][1];
        ans = min(ans,solve());
        printf("%d\n",ans);
    }
    return 0;
}