#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
bool book[maxn];
int a, b;
vector<int> v1, v2;
signed main(){
    a = read(); b = read();
    int sum = a + b, tmp = 0,point = 1;
    while(tmp + point <= sum){tmp += point;point++;}
    tmp = 0;point--;
    for(int i = 1;i <= point;i++){
        if(tmp + i > a){book[i] = 1;book[tmp + i - a] = 0;break;}
        if(tmp + i == a){book[i] = 1;break;}
        book[i] = 1;tmp += i;
    }
    for(int i = 1;i <= point;i++){
        if(book[i])v1.push_back(i);
        else v2.push_back(i);
    }
    printf("%d\n",v1.size());for(int i : v1)printf("%d ",i);puts("");
    printf("%d\n",v2.size());for(int i : v2)printf("%d ",i);puts("");
    return 0;
}