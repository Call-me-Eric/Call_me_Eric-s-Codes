#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
const int mod = 1e8 - 3;
int n;
int ans;
int a[maxn];
int t[maxn];
struct node{
    int num;
    int id;
}a1[maxn],a2[maxn];
struct cmp{
    bool operator()(node a,node b){
        return a.num < b.num;
    }
};
void msort(int left,int right){
    if(left >= right)return;
    int mid = (left + right) / 2;
    msort(left, mid);msort(mid + 1,right);
    int i = left, k = left, j = mid + 1;
    while(i <= mid && j <= right){
        if(a[i] <= a[j]){
            t[k] = a[i];
            i++;
        }
        else {
            t[k] = a[j];
            ans = (ans + mid - i + 1) % mod;
            j++;
        }
        k++;
    }
    while(i <= mid){
        t[k] = a[i];
        i++;k++;
    }
    while(j <= right){
        t[k] = a[j];
        j++;k++;
    }
    for(int i = left;i <= right;i++){
        a[i] = t[i];
    }
}
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d",&a1[i].num);
        a1[i].id = i;
    }
    for(int i = 1;i <= n;i++){
        scanf("%d",&a2[i].num);
        a2[i].id = i;
    }
    sort(a1 + 1,a1 + 1 + n,cmp());
    sort(a2 + 1,a2 + 1 + n,cmp());
    for(int i = 1;i <= n;i++){
        a[a2[i].id] = a1[i].id;
    }
    msort(1,n);
    printf("%d\n",ans);
    return 0;
}