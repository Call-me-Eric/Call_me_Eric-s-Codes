#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 5 * 1e5;
char s[maxn];
bool down[maxn];// '/' = false, '\' = true
int sum[maxn];
int solve(int l,int r){
    for(int i = l;i <= r;i++){
        down[i] = !down[i];
    }
    memset(sum,0,sizeof(sum));
    for(int i = l;i <= r;i++){
        int pos = i;
        while(1){
            if(!down[i])
                if(pos > 1 && !down[pos - 1])pos--;
                else {pos--;break;}
            else
                if(pos < n && down[pos + 1])pos++;
                else {break;}
        }
        sum[pos]++;
    }
    int maxx = 0;
    for(int i = 0;i <= n;i++){maxx = max(maxx,sum[i]);}
    return maxx;
}
signed main(){
    freopen("ball.in","r",stdin);
    freopen("ball.out","w",stdout);
    n = read(); m = read();
    scanf("%s",s + 1);
    for(int i = 1;i <= n;i++){down[i] = !(s[i] == '/');}
    for(int i = 1;i <= m;i++){
        int l = read(), r = read();
        printf("%d\n",solve(l,r));
    }
    return 0;
}
/*
5 6
\/\\/
2 4
3 5
1 5
1 3
2 4
1 5
*/