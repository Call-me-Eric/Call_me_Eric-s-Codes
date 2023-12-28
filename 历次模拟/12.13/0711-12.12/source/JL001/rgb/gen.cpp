#include<iostream>
#include<cstring>
#include<map>
#include<random>
using namespace std;
random_device rn;
int seed=rn();
mt19937 rnd(seed);
int n,m,r,g,b;
map<pair<int,int>,int>vis;
void geng(int n,int m){
    for(int i=2;i<=n;i++){
        int x=i,y=rnd()%(i-1)+1;
        cout<<x<<" "<<y<<" ";
        vis[make_pair(x,y)]=1;
        vis[make_pair(y,x)]=1;
        int w=rnd()%3;
        if(w==0) cout<<"r\n";
        else if(w==2)cout<<"g\n";
        else cout<<"b\n";
    
    }
    for(int i=n-1+1;i<=m;i++){
        int x=rnd()%n+1,y=rnd()%n+1;
        while(x==y||vis[make_pair(x,y)]){
            y=rnd()%n+1;
            x=rnd()%n+1;
        }
        vis[make_pair(x,y)]=1;
        vis[make_pair(y,x)]=1;
        cout<<x<<" "<<y<<" ";
        int w=rnd()%3;
        if(w==0) cout<<"r\n";
        else if(w==2)cout<<"g\n";
        else cout<<"b\n";
    }
}
int main(){
    cerr<<seed<<endl;
    r=rnd()%40,g=rnd()%40,b=rnd()%40;//b=0;
    m=rnd()%1000+r+g+b;
    n=r+g+b+1;
    m=min(m,n*(n-1)/2);
    cout<<r<<" "<<g<<" "<<b<<" "<<m<<endl;
    // cerr<<"?? "<<n<<" "<<m<<endl;
    geng(n,m);

}