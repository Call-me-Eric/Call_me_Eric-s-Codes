#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int n, a[maxn], b[maxn];
int sum[maxn], buc[maxn];
int check(int mid){//1 meant ans should be lower,-1 meant ans should be higher
    a[n + 1] = -1;
    for(int i = 1;i <= n + 1;i++){
        b[i] = a[i];
        if(a[i] < mid){
            b[i] = mid;
            for(int j = i + 1;j <= n + 1;j++)
                b[j] = a[j - 1];
            break;
        }
    }
    for(int i = 1;i <= n + 1;i++){sum[i] = sum[i - 1] + b[i];}
    for(int k = 1, j = n + 1;k <= n + 1;k++){
        while(j > k && b[j] < k)j--;j = max(j,k);
        int suml = sum[k], sumr = k * (k - 1) + (j - k) * k + (sum[n + 1] - sum[j]);
        if(suml > sumr){return mid < b[k] ? -1 : 1;}
    }
    return 0;
}
void main(){
    n = read();int tot = 0;
    for(int i = 1;i <= n;i++)tot += (a[i] = read());
    sort(a + 1,a + 1 + n,greater<int>());
    int l = 0, r = n, ansl = 0;
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid) >= 0){r = mid - 1,ansl = mid;}
        else l = mid + 1;
    }
    l = 0; r = n;
    int ansr = -1;
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid) <= 0){l = mid + 1,ansr = mid;}
        else r = mid - 1;
    }
    vector<int> ans;
    for(int i = ansl;i <= ansr;i++)if(!((tot + i) & 1))ans.push_back(i);
    if(ans.empty())ans.push_back(-1);
    for(int i : ans)printf("%lld ",i);puts("");
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}