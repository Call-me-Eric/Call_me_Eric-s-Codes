#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,q;
int z,a,b;
enum :int{p=998244353};
int ksm(int x,int y){
    int sum=1;
    while(y){
        if(y&1)sum=sum*x%p;
        x=x*x%p;
        y>>=1;
    }
    return sum;
}
signed main(){
    ios::sync_with_stdio(0);
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    cin>>n>>q;
    cin>>a>>b;
    if(a==0 and b!=0)cout<<"No"<<"\n";
    else if(a==0 and b==0)cout<<"Many\n";
    else if(b==0)cout<<0<<'\n';
    else cout<<ksm(a,p-2)*b%p<<'\n';
    while(q--){
        cin>>z>>a>>b;
        if(a==0 and b!=0)cout<<"No"<<"\n";
        else if(a==0 and b==0)cout<<"Many\n";
        else if(b==0)cout<<0<<'\n';
        else cout<<ksm(a,p-2)*b%p<<'\n';
    }
    return 0;
}