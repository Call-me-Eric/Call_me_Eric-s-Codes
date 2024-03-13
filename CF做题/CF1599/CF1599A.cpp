#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n;
int a[maxn];
char ch[maxn];
bool flag[maxn];//1 = L, 0 = R;
deque<int> L,R;
pair<int,char> ans[maxn];
void main(){
    n = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    scanf("%s",ch + 1);sort(a + 1,a + 1 + n);
    for(int i = 1;i <= n;i++){
        flag[i] = ch[i] == 'L';
        if(i & 1){L.push_back(a[i]);}
        else {R.push_back(a[i]);}
    }
    if(flag[n] != (n & 1)){swap(L,R);}
    for(int i = n;i >= 1;i--){
        int flg = flag[i] ^ flag[i - 1];
        pair<int,char> ll,rr;
        ll = rr = make_pair(flg ? -0x3f3f3f3f : 0x3f3f3f3f, 'O');
        if(L.size()){ll = make_pair(flg ? L.back() : L.front(),'L');}
        if(R.size()){rr = make_pair(flg ? R.back() : R.front(),'R');}
        if((ll < rr) ^ flg){ans[i] = ll;if(flg)L.pop_back();else L.pop_front();}
        else {ans[i] = rr;if(flg)R.pop_back();else R.pop_front();}
    }
    for(int i = 1;i <= n;i++){printf("%d %c\n",ans[i].first, ans[i].second);}
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