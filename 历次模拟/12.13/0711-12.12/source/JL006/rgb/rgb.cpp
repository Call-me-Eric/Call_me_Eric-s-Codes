#include<bits/stdc++.h>
#define N 300
using namespace std;
int n,R,G,B,m,f[N],u[N*N],v[N*N],vis[N*N];
pair<int,int> solve(double a,double b,double c){
    pair<int,int>ans;
    double mi = 1e18;
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){
        double tmp = a*i*i+b*j*j+c*(n-1-i-j)*(n-1-i-j);
        if(tmp<mi)mi=tmp,ans={i,j};
    }
    return ans;
}
int gf(int x){return f[x]==x?x:f[x]=gf(f[x]);}
int main(){
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin>>R>>G>>B>>m,n=R+G+B+1;
    double a=0,b=0,c=0,t=1;
    pair<int,int>cur = solve(a,b,c);
    for(;;){
        double da = (1.0*rand()-RAND_MAX/2)/RAND_MAX*100*t,
               db = (1.0*rand()-RAND_MAX/2)/RAND_MAX*100*t,
               dc = (1.0*rand()-RAND_MAX/2)/RAND_MAX*100*t;
        pair<int,int>nxt=solve(a+da,b+db,c+dc);
        if(abs(cur.first-R)+abs(cur.second-G) > abs(nxt.first-R)+abs(nxt.second-G) || rand() < RAND_MAX/100){
            cur = nxt,a+=da,b+=db,c+=dc;
        }
        if(cur.first == R && cur.second == G)break;
        t*=0.9999;
    }
    vector<int>vr,vg,vb;
    for(int i=1;i<=m;i++){
        char c;
        cin>>u[i]>>v[i]>>c;
        if(c=='r')vr.push_back(i);
        else if(c=='g')vg.push_back(i);
        else vb.push_back(i);
    }
    auto br = vr,bg = vg,bb = vb;
    random_device rd;
    mt19937 rnd(rd());
    while(1.0*clock()/CLOCKS_PER_SEC < 1.9){
    memset(vis,0,sizeof(vis));
    vr=br,vg=bg,vb=bb;
    for(int i=1;i<=n;i++)f[i]=i;
    int cr=0,cg=0,cb=0;
    shuffle(vr.begin(),vr.end(),rnd);
    shuffle(vg.begin(),vg.end(),rnd);
    shuffle(vb.begin(),vb.end(),rnd);
    while(!vr.empty() || !vg.empty() || !vb.empty()){
        double mi = 1e18;
        int argmi;
        if(!vr.empty() && 2*a*cr + a<mi){
            argmi=0,mi=2*a*cr + a;
        }
        if(!vg.empty() && 2*b*cg + b<mi){
            argmi=1,mi=2*b*cg + b;
        }
        if(!vb.empty() && 2*c*cb + c<mi){
            argmi=2,mi=2*c*cb + c;
        }
        if(argmi==0){
            while(!vr.empty()){
                int id = vr.back();
                vr.pop_back();
                if(gf(u[id])!=gf(v[id])){
                    f[gf(u[id])]=gf(v[id]);
                    vis[id]=1;
                    cr++;
                    break;
                }
            }
        }
        if(argmi==1){
            while(!vg.empty()){
                int id = vg.back();
                vg.pop_back();
                if(gf(u[id])!=gf(v[id])){
                    f[gf(u[id])]=gf(v[id]);
                    vis[id]=1;
                    cg++;
                    break;
                }
            }
        }
        if(argmi==2){
            while(!vb.empty()){
                int id = vb.back();
                vb.pop_back();
                if(gf(u[id])!=gf(v[id])){
                    f[gf(u[id])]=gf(v[id]);
                    vis[id]=1;
                    cb++;
                    break;
                }
            }
        }
    }
    /*cerr<<"round="<<_<<endl;
    cerr<<a<<" "<<b<<" "<<c<<endl;
    cerr<<R<<" "<<G<<" "<<B<<":"<<a*R*R+b*G*G+c*B*B<<endl;
    cerr<<cr<<" "<<cg<<" "<<cb<<":"<<a*cr*cr+b*cg*cg+c*cb*cb<<endl;*/
    if(R==cr&&G==cg&&B==cb){
        cout<<"YES"<<'\n';
        for(int i=1;i<=m;i++)cout<<vis[i];
        cout<<'\n';
        exit(0);
    }
    }
    cout<<"NO"<<'\n';
    return 0;
}