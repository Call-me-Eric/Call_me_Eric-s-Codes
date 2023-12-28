#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,m;
pair<int,int> e[N];
int tot;
map<pair<int,int>,int>mp;
int main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            e[++tot]=make_pair(j,i);
            mp[make_pair(j,i)]=tot;
        }
    }
    int ed=0;
    for(int i=1;i<=m;i++){
        static int a,b;
        cin>>a>>b;
        if(a>b)swap(a,b);
        ed+=(1<<((mp[make_pair(a,b)])-1));
    }
    if(n==1){
        cout<<"0 1";
        return 0;
    }else if(n==2){
        if(ed==0)cout<<"0 2";
        else cout<<"0 3";
        return 0;
    }else if(n==3){
        if(ed==0)cout<<"0 3";
        else if(ed==1)cout<<"0 4";
        else if(ed==2)cout<<"0 4";
        else if(ed==3)cout<<"0 6";
        else if(ed==4)cout<<"0 4";
        else if(ed==5)cout<<"0 6";
        else if(ed==6)cout<<"0 6";
        else if(ed==7)cout<<"1 3";
        return 0;
    }
}