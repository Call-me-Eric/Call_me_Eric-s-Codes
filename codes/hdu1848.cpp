#include<stdio.h>
#include<string.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1001;
int n, m, p;
bool book[maxn];
int sg[maxn], fib[16] = {1,2,3,5,8,13,21,34,55,89,144,233,377,610,987};
int main(){
    for(int i = 1;i < maxn;i++){
        memset(book,0,sizeof(book));
        for(int j = 0;j < 15 && fib[j] <= i;j++){
            book[sg[i - fib[j]]] = 1;
        }
        for(int j = 0;j <= i;j++){
            if(!book[j]){
                sg[i] = j;
                break;
            }
        }
    }
    while(1){
        n = read(); m = read(); p = read();
        if(n == 0 && m == 0 && p == 0)break;
        puts((sg[n] ^ sg[m] ^ sg[p]) ? "Fibo" : "Nacci");
    }
    return 0;
}