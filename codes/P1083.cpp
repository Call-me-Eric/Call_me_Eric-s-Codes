#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 19;
int n, m;
int r[maxn];
int d[maxn], s[maxn], t[maxn];
int leftt, rightt;
//leftt rightt
int day[maxn];
int fun(int mid){
    memset(day,0,sizeof(day));
    for(int i = 1;i <= mid;i++){
        day[s[i]] += d[i];
        day[t[i] + 1] -= d[i];
    }
    if(day[1] > r[1])return 1;
    for(int i = 2;i <= n;i++){
        day[i] += day[i - 1];
        if(day[i] > r[i])return 1;
    }
    return 0;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        scanf("%d", &r[i]);
    }
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&d[i],&s[i],&t[i]);
    }
    leftt = 1;rightt = m;
    while(leftt < rightt){
        int mid = (leftt + rightt) / 2;
        if(fun(mid))rightt = mid;
        else leftt = mid + 1;
    }
    if(rightt != m){
        printf("-1\n%d\n",rightt);
    }
    else {
        printf("0\n");
    }
    return 0;
}