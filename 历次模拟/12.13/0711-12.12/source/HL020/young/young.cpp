#include<bits/stdc++.h>
#define mid (l+r)/2
#define N 1000001
using namespace std;
int a[N],b[N],n,m,cnt,ab,k,z;
void dfs(int s){
    if(ab>k+1-s)return;
    if(s==k+1){
        cnt++;
        return;
    }
    for(int i=1;i<=z;i++){
        if(a[i]+1<=a[i-1]){
            ab-=abs(a[i]-b[i]);
            a[i]++;
            ab+=abs(a[i]-b[i]);
            dfs(s+1);
            ab-=abs(a[i]-b[i]);
            a[i]--;
            ab+=abs(a[i]-b[i]);
        }
        if(a[i]-1>=a[i+1]&&a[i]>0){
            ab-=abs(a[i]-b[i]);
            a[i]--;
            ab+=abs(a[i]-b[i]);
            dfs(s+1);
            ab-=abs(a[i]-b[i]);
            a[i]++;
            ab+=abs(a[i]-b[i]);
        }
    }
}
int main(){
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    a[0]=100;
    cin>>m;
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }

    cin>>k;
    cin>>k;
    z=max(n,m)+k/2;
    for(int i=1;i<=z;i++){
        ab+=abs(a[i]-b[i]);
    }
    dfs(1);
    cout<<cnt<<endl;
    return 0;
}
