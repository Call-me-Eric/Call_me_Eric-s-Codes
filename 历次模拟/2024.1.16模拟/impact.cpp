#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10;
int l[maxn], r[maxn];
int a[maxn];
void solve(int *b,int n,int k){
    for(int i = 1;i <= n;i++)a[i] = b[i];
    vector<int> vec;vec.clear();
    vec.push_back(a[1]);bool lst = a[1] >= 0;
    int tot = 0, tot1 = 0;
    for(int i = 2;i <= n;i++){
        if(a[i] >= 0)tot++;
        if((a[i] >= 0) == lst)vec.back() += a[i];
        else {vec.push_back(a[i]);lst = (a[i] >= 0);}
    }
    if(tot <= k){
        int ans = 0;
        nth_element(a + 1,a + n - k + 1,a + 1 + n);
        for(int i = n - k + 1;i <= n;i++){ans += a[i];}
        printf("%d\n",ans);return;
    }
    tot = 0;
    if(vec.back() < 0)vec.back() = 0;
    if(vec[0] < 0)vec[0] = 0;
    for(int i : vec){if(i > 0){tot1++;tot += i;}}
    if(tot1 <= k){printf("%d\n",tot);return;}
    
    vector<int> tmp = vec;tot = 0;int tot2 = tot1;tot1 = 0;
    nth_element(tmp.begin(),tmp.begin() + tmp.size() - k,tmp.end());
    for(int i = tmp.size() - k;i < tmp.size();i++)tot += tmp[i];
    for(int i = 0;i < vec.size();i++){
        bool book = true;int l = 0, r = 0;
        if(i != 0){if(vec[i] + vec[i - 1] >= 0)book = false;l = vec[i - 1];}
        if(i != vec.size() - 1){if(vec[i] + vec[i + 1] >= 0)book = false;r = vec[i + 1];}
        if(book){
            int t = l + vec[i] + r;
            tot1++;vec[i] = t;if(i != 0)vec[i - 1] = -0x3f3f3f3f;
            if(i != vec.size() - 1)vec[i + 1] = -0x3f3f3f3f;
        }
    }
    if(tot2 - tot1 <= k){printf("%d\n",tot);return;}
    tmp.clear();tot2 = tot = 0;
    for(int i = 0;i < vec.size();i++){
        if(vec[i] != -0x3f3f3f3f){
            if(vec[i] > 0){tot2++;tot += vec[i];}
            else tmp.push_back(vec[i]);
        }
    }
    tot1 = tot2 - k;
    nth_element(tmp.begin(),tmp.begin() + tot1 + 1,tmp.end());
    for(int i = 0;i < tot1;i++)tot += tmp[i];
    printf("%d\n",tot);
}
int n, q;
int X[maxn];
signed main(){
    freopen("impact.in","r",stdin);
    freopen("impact.out","w",stdout);
    n = read(); q = read();
    for(int i = 1;i <= n;i++){X[i] = read();}
    while(q--){int u = read(), v = read(), w = read();solve(X + u - 1, v - u + 1, w);}
    return 0;
}