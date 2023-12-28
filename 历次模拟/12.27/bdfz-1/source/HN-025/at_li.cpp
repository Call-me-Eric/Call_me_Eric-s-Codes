#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct graph{
    int n,m;
    vector<vector<int> >lk;
    void link(int x,int y){
        ++m,lk[x].push_back(m);
        lk[y].push_back(m);
    }
    void read(){
        int i,x,y,T;
        cin>>n>>T,lk.resize(n+1);
        while(T--)cin>>x>>y,link(x,y);
    }
    void x_goto(graph &z){
        z={m,0};
        z.lk.resize(m+1);
        int x,i,j,k;
        for(x=1;x<=n;++x){
            k=lk[x].size();
            for(i=0;i<k;++i)
                for(j=i+1;j<k;++j)
                    z.link(lk[x][i],lk[x][j]);
        }
    }
}F,G;
double s[N];
double lgrg(int r,int p){
    double res=0,sum;
    int i,j;
    for(i=1;i<=r;++i){
        for(j=1,sum=s[i];j<=r;++j)
            if(i!=j)sum*=double(p-j)/(i-j);
        res+=sum;
    }return res;
}
int main(){
    ios::sync_with_stdio(false);
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    int i,j,k,l,r,x,y;
    F.read();s[1]=F.n;
    for(i=2;i<=10;++i){
        G=F,G.x_goto(F);
        // printf("n:%d m:%d\n",F.n,F.m);
        // fflush(stdout);
        s[i]=s[i-1]+F.n;
        printf("s:%.2lf lgrg:%.2lf\n",s[i],lgrg(i-1,i));
    }
    return 0;
}