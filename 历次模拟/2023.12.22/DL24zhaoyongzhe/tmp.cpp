#include<bits/stdc++.h>
using namespace std;
namespace datamaker1{
    void main(){
        freopen("compose.in","w",stdout);
        int subtask = 2;
        int n = 1e5, k = 12, q = 1e5;
        
        if(subtask == 1)n = 100;
        
        printf("%d %d %d\n",n,k,q);
        srand(time(0));mt19937 rnd(rand());
        for(int i = 1;i <= k;i++){
            for(int j = 1;j <= n;j++){
                int x = rnd() % (int)1e9;
        
                if(subtask == 3)x = x % 2 + 1;
        
                printf("%d ",x);
            }
            puts("");
        }
        int opt, x, y, cnt = 0;
        for(int i = 1;i <= q;i++){
            opt = rnd() % 3 + 1;
            if(opt <= 2){
                x = rnd() % (cnt + k - 1) + 1;
                y = rnd() % (cnt + k - 1) + 1;
                cnt++;
        
                if(subtask == 2)opt = 1;
        
            }
            else {
                x = rnd() % (cnt + k - 1) + 1;
                y = rnd() % n + 1;
            }
            printf("%d %d %d\n",opt,x,y);
        }
    }
};
namespace datamaker2{
    void main(){
        freopen("matrix.in","w",stdout);
        int n = 1000, m = 100, k = 1e9;
        srand(time(0));mt19937 rnd(rand());
        printf("%d\n",n);
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                putchar('0' + (rnd() % 2));
            }
            puts("");
        }
        for(int i = 1;i <= n;i++){
            putchar('0' + (rnd() % 2));
        }
        printf("\n%d\n",m);
        for(int i = 1;i <= m;i++){
            k = rnd() % (int)(1e9);
            printf("%d\n",k);
        }
    }
};
signed main(){
    datamaker1::main();
    return 0;
}