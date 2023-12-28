#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n;
const int maxn = 1010;
struct node{
    int id, time;
    node(int id = 0, int time = 0){
        this->id = id;
        this->time = time;
    }
}a[maxn];
bool operator < (node a,node b){
    return a.time < b.time;
}
priority_queue<node >que;
signed main(){
    n = read();
    for(int i = 1;i <= n;i++)a[i] = node(i,read());
    int sum = 0;
    sort(a + 1,a + 1 + n);
    for(int i = 1;i <= n;i++){
        printf("%d ",a[i].id);
        if(n - i >= 1)sum += a[i].time * (n - i);
    }
    printf("\n%.2lf\n",1.0 * sum / n);
    return 0;
}