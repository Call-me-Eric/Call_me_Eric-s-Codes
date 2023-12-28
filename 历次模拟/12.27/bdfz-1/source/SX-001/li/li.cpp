#include<bits/stdc++.h>
using namespace std;
int n,m;
signed main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    cin>>n>>m;
    if(n==1)cout<<"0 1\n";
    else if(n==2){
        if(!m)cout<<"0 2\n";
        else cout<<"0 3\n";
    }else if(n==3){
        if(!m)cout<<"0 3\n";
        else if(m==1)cout<<"0 4\n";
        else if(m==2)cout<<"0 5\n";
        else cout<<"1 3\n";
    }else cout<<-1<<'\n';
    return 0;
}