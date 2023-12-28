#include<stdlib.h>
#include<stdio.h>
#include<algorithm>
using namespace std;
const int maxn = 100010;
int n, tree_size, k;
int a[maxn], x[maxn << 5], y[maxn << 5];
int sum[maxn << 5], memory[maxn];
int b[maxn], q, point;
void build(int &u,int l,int r){
    u = ++tree_size;
    if(l == r)return;
    int mid = (l + r) / 2;
    build(x[u],l,mid);
    build(y[u],mid + 1,r);
}
int modify(int u,int l,int r){
    int now = ++tree_size;
    x[now] = x[u];
    y[now] = y[u];
    sum[now] = sum[u] + 1;
    if(l < r){
        int mid = (l + r) / 2;
        if(mid >= point){
            x[now] = modify(x[now],l,mid);
        }
        else y[now] = modify(y[now],mid + 1,r);
    }
    return now;
}
int query(int u,int v,int l,int r,int k){
    if(l == r)return l;
    int mid = (l + r) / 2,tmp = sum[y[v]] - sum[y[u]],ans = 0;
    if(tmp >= k)ans = query(y[u],y[v],mid + 1,r,k);
    else ans = query(x[u],x[v],l,mid,k - tmp);
    return ans;
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        b[i] = a[i];
    }
    sort(b + 1,b + 1 + n);
    q = unique(b + 1,b + 1 + n) - b - 1;
    build(memory[0],1,q);
    for(int i = 1;i <= n;i++){
        point = lower_bound(b + 1,b + 1 + q,a[i]) - b;
        memory[i] = modify(memory[i - 1],1,q);
    }
    for(int i = 1;i <= n - k + 1;i++){
        printf("%d ",b[query(memory[i - 1],memory[i + k - 1 ],1,q,1)]);
    }
    return 0;
}