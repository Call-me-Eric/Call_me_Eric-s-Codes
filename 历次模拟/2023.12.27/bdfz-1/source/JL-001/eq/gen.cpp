#include<iostream>
#include<cstring>
#include<random>
using namespace std;
int n,q;
#define rep(i,l,r) for(int i=l;i<=r;i++)
random_device rn;
mt19937 rnd(rn());
int main(){
    n=2,q=700;
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cout<<n<<" "<<q<<'\n';
    rep(i,1,n){
        rep(j,1,n+1) cout<<rnd()%3<<" ";cout<<"\n";
    }
    rep(i,1,q){
        cout<<rnd()%n+1<<" ";
        rep(j,1,n+1) cout<<rnd()%3<<" ";cout<<"\n";
    }
}