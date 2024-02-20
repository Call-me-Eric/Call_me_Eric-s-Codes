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
const int maxn = 1e6 + 10;
vector<int> vec;
void main(){
    int test = 0;
    while(++test){
        system("./tmp");
        // system("./bruteforce");
        system("./room");
        // if(system("diff tmp.out room.out")){
        //     printf("Wrong answer on test %d\n",test);
        //     break;
        // }
        // puts("AC");
        // system("time ./room");
    }
    // freopen("sequence.out","r",stdin);
    // int x;while(scanf("%d",&x) != EOF)vec.push_back(x);
    // freopen("sequence4.ans","r",stdin);
    // freopen("tmp.out","w",stdout);
    // int pos = 0;
    // while(scanf("%d",&x) != EOF){
    //     if(vec[pos] != x){
    //         printf("diff on line %d,vec = %d,x = %d\n",pos,vec[pos],x);
    //     }
    //     pos++;
    // }
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