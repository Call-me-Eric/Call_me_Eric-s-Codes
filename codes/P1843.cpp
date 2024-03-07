#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >='0'&&ch <='9'){x=(x<<3)+(x<<1)+ch-'0'; ch = getchar();}
    return x * f;
}
int n, a, b;
priority_queue<int> heap;
int main(){
    int all = 0;
    n = read(); a = read(); b = read();
    for(int i = 1;i <= n;i++)heap.push(read());
    int k = heap.top();heap.pop();
    k -= b;
    all += a;
    heap.push(k);
    while(1){
        k = heap.top();heap.pop();
        if(k - all <= 0){
            printf("%d\n",all / a);
            break;
        }
        all += a;
        k -= b;
        heap.push(k);
    }
    return 0;
}