#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e3 + 10;
int T;
int n;
ll r,h;
//if u state "r" as "int" instead of "long long",u will "RE"
int f[maxn];
int f1[maxn],f2[maxn];
ll x[maxn], y[maxn], z[maxn];


ll dist(ll x1,ll y1,ll z1,ll x2,ll y2,ll z2){//pay attention:this is dis square
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
}

int getf(int x){
    if(f[x] == x)return x;
    else {
        f[x] = getf(f[x]);
        return f[x];
    }
}

int main(){
    scanf("%d",&T);
    while(T--){
        memset(f1,0,sizeof(f1));
        memset(f2,0,sizeof(f2));
        scanf("%d%lld%lld",&n,&h,&r);
        int top = 0, bottom = 0;
        for(int i = 1;i <= n;i++){
            f[i] = i;
        }
        ll dis = 0;
        for(int i = 1;i <= n;i++){
            scanf("%lld%lld%lld",&x[i],&y[i],&z[i]);
            if(z[i] + r >= h){
                top++;
                f1[top] = i;
            }
            if(z[i] - r <= 0){
                bottom++;
                f2[bottom] = i;
            }
            for(int j = 1;j <= i;j++){
                if((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) > 4 * r * r)
                            continue;//it is so large that it maybe over LONG_LONG_MAX
                if(dist(x[i],y[i],z[i],x[j],y[j],z[j]) <= 4 * r * r){
                    int a1 = getf(i);
                    int a2 = getf(j);
                    if(a1 != a2)f[a2] = a1;
                }
            }
        }
        bool book = 0;
        for(int i = 1;i <= top;i++){
            for(int j = 1;j <= bottom;j++){
                if(getf(f1[i]) == getf(f2[j])){
                    book = 1;
                    break;
                }
            }
            if(book)break;
        }
        puts(book ? "Yes" : "No");
    }
    return 0;
}