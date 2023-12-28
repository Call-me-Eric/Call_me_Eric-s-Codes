#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct qwq{
    int x,y;
};
vector<qwq>t,bt;
vector<int>ver[100005],bver[100005];
int n,m;
vector<int>s;
inline int ksm(int x,int y){
    int re=1;
    while(y>0){
        if((y&1)==1) re=re*x;
        x=x*x;
        y>>=1;
    }
    return re;
}
int main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    scanf("%d%d",&n,&m);
    int x,y;
    for(int i=1;i<=m;++i){
        scanf("%d%d",&x,&y);
        t.push_back({x,y});
        ver[x].push_back(t.size());
        ver[y].push_back(t.size());
    }
    s.push_back(n);
    for(int i=1;i<=50;++i){
        s.push_back(t.size());
        s[s.size()-1]+=s[s.size()-2];
        bt.clear();
        for(int j=1;j<=s[i-1];++j) bver[j].clear();
        for(int j=0;j<t.size();++j){
            for(int x:ver[t[j].x]){
                if(j+1<x){
                    bt.push_back({j+1,x});
                    bver[j+1].push_back(bt.size());
                    bver[x].push_back(bt.size());
                }
            }
            for(int x:ver[t[j].y]){
                if(j+1<x){
                    bt.push_back({j+1,x});
                    bver[j+1].push_back(bt.size());
                    bver[x].push_back(bt.size());
                }
            }
        }
        t=bt;
        for(int j=1;j<=s[s.size()-1];++j){
            ver[j]=bver[j];
        }
    }
    // for(int i=0;i<=50;++i){
    //     printf("%d ",s[i]);
    // }
    // printf("\n");
    int ss,ans=0,sum;
    for(ss=0;ss<=50;++ss){
        sum=ksm(50,ss);
        if(s[50]/sum<=n) break;
    }
    printf("%d %d",ss,s[50]/sum);
    return 0;
}
/*
*/
