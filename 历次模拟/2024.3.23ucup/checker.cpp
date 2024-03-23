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
inline pair<int,int> read(int tmp){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return make_pair(x,f);
}
const int maxn = 3e3 + 10;
int n;
pair<int,int> opts[maxn];
char ch[maxn];
void main(){
    freopen("test.in","r",stdin);
    n = read();
    for(int i = 1;i <= n * 2;i++){
        auto x = read(1);
        opts[i] = x;
    }
    freopen("test.out","r",stdin);
    stack<int> stk[2];
    scanf("%s",ch + 1);int pos = 1;
    for(int i = 1;i <= n * 2;i++){
        if(opts[i].second == 1){
            stk[ch[pos] == 'G'].push(opts[i].first);pos++;
        }
        else{
            if(!stk[0].empty() && stk[0].top() == opts[i].first){
                stk[0].pop();
            }
            else if(!stk[1].empty() && stk[1].top() == opts[i].first){
                stk[1].pop();
            }
            else{
                printf("Wrong Answer on %d opt\n",i);
            }
        }
    }
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