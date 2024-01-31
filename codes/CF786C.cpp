#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int a[maxn], n;

int book[maxn];
int ans[maxn];
int solve(int k){
    if(ans[k])return ans[k];
    memset(book,0,sizeof(book));
    int l = 0, cnt = 0, m = 0;
    for(int i = 1;i <= n;i++){
        cnt += !book[a[i]]++;
        if(cnt > k){
            for(int j = l + 1;j < i;j++)book[a[j]]--;
            m++; cnt = 1; l = i - 1;
        }
    }
    return ans[k] = m + (cnt ? 1 : 0);
}
signed main(){
    n = read();for(int i = 1;i <= n;i++)a[i] = read();
    for(int k = 1, len = sqrt(n);k <= n;k++){
        if(k <= len){printf("%d ",solve(k));}
        else{
            int res = solve(k);
            int l = k, r = n;
            while(l <= r){
                int mid = l + r >> 1;
                if(solve(mid) == res){l = mid + 1;}
                else r = mid - 1;
            }
            l--;
            for(int j = k;j <= l;j++)printf("%d ",res);
            k = l;
        }
    }
    puts("");
    return 0;
}