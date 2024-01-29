#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;

int n, m, k;
int a[maxn][6];
int lg[maxn];
struct ST_table{
    int st[21][maxn];
    void init(int x){
        for(int i = 1;i <= n;i++)st[0][i] = a[i][x];
        for(int j = 1;j <= 20;j++)
            for(int i = 1;i + (1 << j) - 1 <= n;i++)
            st[j][i] = max(st[j - 1][i],st[j - 1][i + (1 << (j - 1))]);
    }
    int query(int l,int r){
        int k = lg[r - l + 1];
        return max(st[k][l],st[k][r - (1 << k) + 1]);
    }
}st[6];

int opt[6];

signed main(){
    n = read(); m = read(); k = read();lg[0] = -1;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++)
            a[i][j] = read();
        lg[i] = lg[i >> 1] + 1;
    }
    for(int i = 1;i <= m;i++)st[i].init(i);
    int ans = 0;
    for(int i = 1;i <= n;i++){
        int l = i, r = n, res = 0;
        while(l <= r){
            int mid = l + r >> 1, cnt = 0;
            for(int j = 1;j <= m;j++)cnt += st[j].query(i,mid);
            if(cnt <= k){l = mid + 1;res = mid;}
            else r = mid - 1;
        }
        if(ans < res - i + 1){
            ans = res - i + 1;
            for(int j = 1;j <= m;j++)opt[j] = st[j].query(i,res);
        }
    }
    for(int i = 1;i <= m;i++)printf("%d ",opt[i]);
    return 0;
}