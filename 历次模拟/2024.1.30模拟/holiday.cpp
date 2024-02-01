#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
#define ll long long
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, d, st;
int sum[maxn];
int a[maxn];
namespace Subtask1{
struct kmaxsum{
    priority_queue<ll,vector<ll>, greater<ll> >que;
    int siz;ll sum;
    void insert(ll x){
        if(que.size() + 1 <= siz){
            que.push(x);sum += x;
        }
        else{
            if(que.top() < x){
                sum -= que.top();que.pop();
                sum += x;que.push(x);
            }
        }
    }
    void resize(int s){
        siz = s;
        while(que.size() > siz){sum -= que.top();que.pop();}
        // cerr << "siz = " << siz << " que.siz = " << que.size() << endl;
    }
    ll getsum(){return sum;}
}que;
ll solve(int option){
    ll ans = a[st];
    for(int l = st;l;l--){
        if(d - (st - l) <= 0)break;
        que.resize(0);que.resize(d - (st - l));
        for(int i = l;i <= st;i++){que.insert(a[i]);}
        int r = st;ans = max(ans,que.getsum());
        while(r - l + st - l < d - 1 && r < n){
            r++;que.resize(d - (r - l + st - l));
            que.insert(a[r]);
            ans = max(ans,que.getsum());
        }
    }
    if(option)
        for(int r = st;r <= n;r++){
            if(d - (r - st) <= 0)break;
            que.resize(0);que.resize(d - (r - st));
            for(int i = st;i <= r;i++){que.insert(a[i]);}
            int l = st;ans = max(ans,que.getsum());
            while(r - l + r - st + 1 < d && l > 1){
                l--;que.resize(d - (r - l + r - st));
                que.insert(a[l]);
                ans = max(ans,que.getsum());
            }
        }
    return ans;
}
};
namespace Subtask2{
ll solve(){
    return -1;
}
};
void main(){
    n = read(); st =  read() + 1; d = read();
    for(int i = 1;i <= n;i++)a[i] =  read();
    printf("%lld\n",Subtask1::solve(n <= 3e3));
    // if(n <= 3e3 || st == 1){
    // }
    // else{printf("%lld\n",Subtask2::solve());}
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
/*
10 3 7
11 45 14 1 91 9 8 10 114 5
*/