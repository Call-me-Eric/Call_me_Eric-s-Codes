#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
typedef pair<int,int> pii;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e3 + 10;
int n, id[maxn];
pii p[maxn];
int operator * (pii a,pii b){return a.first * b.second - a.second * b.first;}
pii operator - (pii a,pii b){return make_pair(a.first - b.first,a.second - b.second);}
pair<double,int> tmp[maxn];
int stk[maxn], top;
double theta(pii p){return atan2(p.second,p.first);}
void main(){
    n = read();for(int i = 1;i <= n;i++){p[i].first = read();p[i].second = read();}
    sort(p + 1,p + 1 + n,[&](pii x,pii y){
        return x.first != y.first ? x.first < y.first : x.second < y.second;
    });
    stk[++top] = 1;id[1] = 1;
    for(int i = 2;i <= n;i++){
        while(top >= 2 && (p[stk[top]] - p[stk[top - 1]]) * (p[i] - p[stk[top]]) <= 0)
            id[stk[top--]] = 0;
        id[i] = 1;stk[++top] = i;
    }
    int tot = top;
    for(int i = n - 1;i;i--){
        if(id[i])continue;
        while(top >= tot && (p[stk[top]] - p[stk[top - 1]]) * (p[i] - p[stk[top]]) <= 0)
            id[stk[top--]] = 0;
        id[i] = 1;stk[++top] = i;
    }
    for(int i = 1;i <= top;i++)id[stk[i]] = i;
    for(int i = 1;i <= n;i++)printf("i = %d,x = %d,y = %d\n",i,p[i].first,p[i].second);
    int ans = 1;
    for(int i = 1;i <= n;i++){
        if(id[i])continue;
        for(int j = 1;j <= n;j++){
            if(j == i)tmp[j] = make_pair(0,-114514);
            else tmp[j] = make_pair(theta(p[j] - p[i]),id[j]);
        }
        sort(tmp + 1,tmp + 1 + n);
        for(int j = 1;j < n;j++){
            if(tmp[j].second && tmp[j + 1].second
            && abs(tmp[j + 1].second - tmp[j].second) == 1)ans++;
            printf("%d ",tmp[j].second);
        }
        printf("%d",tmp[n].second);
        printf("\ni = %d,ans = %d\n",i,ans);
    }
    printf("%d\n",ans);
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