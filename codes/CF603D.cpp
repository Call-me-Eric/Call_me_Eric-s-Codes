#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e3 + 10;
const double eps = 1e-12;
int a[maxn], b[maxn], c[maxn];
int n;
double x[maxn], y[maxn];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        a[i] = read(); b[i] = read(); c[i] = read();
        x[i] = 1.0 * c[i] * a[i] / (a[i] * a[i] * 1.0 + b[i] * b[i] * 1.0);
        y[i] = 1.0 * c[i] * b[i] / (a[i] * a[i] * 1.0 + b[i] * b[i] * 1.0);
        // printf("x = %lf, y = %lf\n",x[i],y[i]);
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        int sam = 0,cnt = 0;vector<double> vec;vec.clear();
        for(int j = 1;j <= n;j++){
            if(j == i)continue;
            double dx = x[j] - x[i];
            double dy = y[j] - y[i];
            if(abs(dx) < eps && abs(dy) < eps)sam++;
            else if(abs(dx) < eps) cnt++;
            else vec.push_back(dy / dx);
        }
        sort(vec.begin(),vec.end(),greater<double>());
        int k = 0;
        ans += (cnt - 1 + sam) * (cnt + sam);
        for(int j = 0;j < vec.size();j += k, k = 1){
            while(j + k < vec.size() && abs(vec[k + j] - vec[j]) < eps)k++;
            ans += (k + sam) * (k + sam - 1);
            // printf("j = %d k = %d\n",j,k);
        }
        // for(int j = 1;j < vec.size();j++)
        //     printf("j = %d,dirt = %lf\n",j,vec[j + 1] - vec[j]);
    }
    printf("%d\n",ans / 6);
    return 0;
}