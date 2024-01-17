#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=998244353;
void add(int &x,int y){(x+=y)>=M&&(x-=M);}
using V=vector<int>;
V A,B;
int n,m,q,a[N],p[N],ans[N];
map<V,int>F,G;
void rec(){
    G=F,F.clear();
    int i,n;
    for(auto at:G){
        V nw=at.first;
        n=nw.size();
        for(i=0;i<n;++i){
            if(!i||nw[i]<nw[i-1]){
                ++nw[i],add(F[nw],at.second),--nw[i];
            }if(nw[i]>1&&(i==n-1||nw[i]>nw[i+1])){
                --nw[i],add(F[nw],at.second),++nw[i];
            }
        }nw.push_back(1),add(F[nw],at.second),nw.pop_back();
        if(nw.size()&&nw.back()==1){
            nw.pop_back();
            add(F[nw],at.second);
        }
    }
}
int main(){
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    ios::sync_with_stdio(false);
    int i,j,k,l,r,x,y;
    cin>>n,A.resize(n);
    for(i=0;i<n;++i)cin>>A[i];
    cin>>m,B.resize(m);
    for(i=0;i<m;++i)cin>>B[i];
    F[A]=1;
    cin>>q;
    for(i=1;i<=q;++i)cin>>a[i],p[i]=i;
    sort(p+1,p+q+1,[&](int x,int y){
        return a[x]<a[y];
    });
    for(i=1;i<=q;++i){
        for(j=a[p[i-1]];j<a[p[i]];++j)rec();
        ans[p[i]]=F[B];
    }
    for(i=1;i<=q;++i)
        printf("%d\n",ans[i]);
    return 0;
}