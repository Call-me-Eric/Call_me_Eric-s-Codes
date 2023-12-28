#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
bool pri(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0)return 0;
    }
    return 1;
}
int ans,now;
int get(int x){
    int ret=0;
    while(x)ret+=x&1,x>>=1;
    return ret;
}
double pi=acos(-1),eps=1e-8;
bool chk(int a){
    if(get(a)>k)return 0;
    double x=0,y=0;
    for(int i=0;i<n;i++){
        if((a>>i)&1){
            double ang=2*pi/n*i;
            x+=sin(ang),y+=cos(ang);
        }
    }
    return fabs(x)<eps&&fabs(y)<eps;
}
void sub1(){
    for(int i=0;i<1<<n;i++){
        if(chk(i)&&get(i)>get(ans))ans=i;
    }
    for(int i=0;i<n;i++){
        if((ans>>i)&1)putchar('1');
        else putchar('0');
    }
}
int find(int x){
    int ret=0;
    for(int i=2;i*i<=x;i++){
        if(x%i)continue;
        ret++;
        while(x%i==0)x/=i;
    }
    if(x>1)ret++;
    return ret;
}
void sub2(){
    int t=0,x=n;
    for(int i=2;i*i<=x;i++){
        if(x%i)continue;
        t=i;
        while(x%i==0)x/=i;
    }
    if(x>1)t=x;
    int d=k/t;
    for(int i=0;i<n;i++){
        if(i%(n/t)<d)putchar('1');
        else putchar('0');
    }
}
namespace sub3{
    int t,cntx,cnty,ans;
    double X[1000005],Y[1000005];
    vector<pair<pair<double,double>,int> >vl;
    void upd(int a){
        double x=0,y=0;
        for(int i=0;i<t;i++){
            if((a>>i)&1){
                double ang=2*pi/n*i;
                x+=sin(ang),y+=cos(ang);
            }
        }
        X[++cntx]=x,Y[++cnty]=y;
        vl.push_back({{x,y},a});
    }
    multimap<pair<int,int>,int> mp;
    void init(){
        sort(X+1,X+cntx+1);cntx=unique(X+1,X+cntx+1)-X-1;
        sort(Y+1,Y+cnty+1);cnty=unique(Y+1,Y+cnty+1)-Y-1;
        for(auto it:vl){
            int x=lower_bound(X+1,X+cntx+1,it.first.first)-X;
            int y=lower_bound(Y+1,Y+cnty+1,it.first.second)-Y;
            mp.insert({{x,y},it.second});
        }
    }
    void kot(int a){
        double x=0,y=0;
        for(int i=0;i<n-t;i++){
            if((a>>i)&1){
                double ang=2*pi/n*(i+t);
                x+=sin(ang),y+=cos(ang);
            }
        }
        int ax=lower_bound(X+1,X+cntx+1,-x)-X;
        int ay=lower_bound(Y+1,Y+cnty+1,-y)-Y;
        int uc=get(a);
        for(int i=max(1ll,ax-5);i<=min(cntx,ax+5);i++){
            for(int j=max(1ll,ay-5);j<=min(cnty,ay+5);j++){
                if(fabs(X[i]+x)>eps||fabs(Y[j]+y)>eps)continue;
                for(auto it=mp.lower_bound({i,j});it!=mp.end()&&
                (*it).first.first==i&&(*it).first.second==j;it++){
                    if(get((*it).second)+uc>k)continue;
                    if(get((*it).second)+uc>get(ans))ans=((*it).second<<(n-t))|a;
                }
            }
        }
    }
    void main(){
        t=n/2;
        for(int i=0;i<1<<t;i++){
            if(get(i)>k)continue;
            upd(i);
        }
        init();
        for(int i=0;i<1<<(n-t);i++){
            if(get(i)>k)continue;
            kot(i);
        }
        for(int i=0;i<n;i++){
            if((ans>>i)&1)putchar('1');
            else putchar('0');
        }
    }
}
signed main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    cin>>n>>k;
    if(n==k){
        for(int i=1;i<=n;i++)putchar('1');
        return 0;
    }
    if(k<=1||pri(n)){
        for(int i=1;i<=n;i++)putchar('0');
        return 0;
    }
    if(n<=20){
        sub1();
        return 0;
    }
    if(find(n)==1){
        sub2();
        return 0;
    }
    if(n<=36){
        sub3::main();
        return 0;
    }
    for(int i=2;i*i<=n;i++){
        if(n%i)continue;
        if(k%i==0){
            for(int j=0;j<n;j++){
                if(j%(n/i)<k%(n/i))putchar('1');
                else putchar('0');
            }
            return 0;
        }
    }
    return 0;
}