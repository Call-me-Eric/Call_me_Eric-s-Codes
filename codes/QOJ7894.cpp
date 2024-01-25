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
char ch[maxn];int n;
bool getbrack(char ch){if(ch == '[' || ch == ']')return 0;return 1;}
char brack(bool opt, bool lft){if(opt == 0){return lft == 0 ? '[' : ']';}return lft == 0 ? '(' : ')';}
void solve(){
    scanf("%s",ch + 1);n = strlen(ch + 1);int cnt = 0;
    stack<int> stk;while(stk.size())stk.pop();
    for(int i = 1;i <= n;i++){
        if(stk.empty()){stk.push(i);continue;}
        int x = stk.top();
        if(getbrack(ch[x]) == getbrack(ch[i])){
            ch[x] = brack(getbrack(ch[x]),0);
            ch[i] = brack(getbrack(ch[i]),1);stk.pop();
        }
        else{stk.push(i);}
        cnt += stk.empty();
    }
    // printf("cnt = %d\n",cnt);
    if(!stk.empty()){puts("No");return;} if(cnt > 2){puts("No");return;}
    for(int i = 1;i < n;i++)
        if(ch[i] != ch[i + 1] && getbrack(ch[i]) == getbrack(ch[i + 1])
            && ch[i] == brack(getbrack(ch[i]),1)){puts("No");return;}
    puts("Yes");return;
}
void main(){
    int T = read();
    while(T--){solve();}
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