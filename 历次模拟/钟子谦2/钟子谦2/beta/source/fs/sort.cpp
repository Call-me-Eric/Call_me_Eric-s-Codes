#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
typedef long long ll;
#define SZ 233333
#define mp make_pair
#define pb push_back
int n,x[SZ],a[SZ];
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
    FO(sort)
    cin>>n;
    for(int i=1;i<=n;++i) cin>>x[i];
    for(int r=1;r<=n;++r){
        int aa=0;
    for(int i=1;i<=r;++i) a[i]=x[i];
    for(int i=1;i<=r;++i) {
        int m=i;++aa;
        for(int j=1;j<=r;++j)
            if(a[m]>a[j]) m=j,++aa;
        swap(a[i],a[m]);
    }
    cout<<aa<<" ";
    }
    cout<<"\n";
}