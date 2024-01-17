#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=998244353;
using uc=unsigned char;
int T,n,f[N][2][3][3][5][10];
void add(int &x,int y){(x+=y)>=M&&(x-=M);}
char s[N];
/*
b:X/9/90
c:X/8/C1
d:X/4/94/946/n6C9
e:X/6/66/666/2*60/3*60/4*60/5*60/n4C9/C9
*/
double clk;
int DP(){
    int i,_d;uc a,b,c,d,e;
    f[0][1][0][0][0][0]=1;
    auto add0=[&](int i,bool a,uc b,uc c,uc d,uc e){
        b==2?c=2:(b==1&&(b=2));d&&(e=9);
        e&&(e<4?e+=3:(e<8&&++e));
        return add(f[i][a][b][c][d][e],_d);
    };auto add4=[&](int i,bool a,uc b,uc c,uc d,uc e){
		c=2;(e>7||d||b==2)?e=9:(d=max(d,uc(e?4:(b?2:1))));
        return add(f[i][a][b][c][d][e],_d);
    };auto add6=[&](int i,bool a,uc b,uc c,uc d,uc e){
        c=2;d==4&&(e=9);e<8&&((b||e>2)?e=8:++e);
        (d==2||d==3)&&++d;
        return add(f[i][a][b][c][d][e],_d);
    };auto add9=[&](int i,bool a,uc b,uc c,uc d,uc e){
        d?e=9:(e<8&&(b||e)&&(e=8));b?c=2:b=1;
        return add(f[i][a][b][c][d][e],_d);
    };
    for(i=1;i<=n;++i)
        for(a=0;a<2;++a)
            for(b=0;b<3;++b)
                for(c=0;c<3;++c)
                    for(d=0;d<5;++d)
                        for(e=0;e<10;++e){
                            _d=f[i-1][a][b][c][d][e];
                            if(!_d)continue;
                            if(!a||0<=s[i])add0(i,a&&(0==s[i]),b,c,d,e);
                            if(c!=2&&(!a||1<=s[i]))add(f[i][a&&(1==s[i])][0][2][0][9],_d);
                            if(!a||4<=s[i])add4(i,a&&(4==s[i]),b,c,d,e);
                            if(!a||6<=s[i])add6(i,a&&(6==s[i]),b,c,d,e);
                            if(!a||8<=s[i])add(f[i][a&&(8==s[i])][b][c+(c<2)][d][9],_d);
                            if(e!=9&&(!a||9<=s[i]))add9(i,a&&(9==s[i]),b,c,d,e);
                        }
    int res=0;
    for(a=0;a<2;++a)
        for(b=0;b<3;++b)
            for(c=0;c<3;++c)
                for(d=0;d<5;++d)
                    for(e=0;e<10;++e)
                        add(res,f[n][a][b][c][d][e]);
    for(i=0;i<=n;++i)memset(f[i],0,sizeof(f[i]));
    return res;
}
int main(){
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    // cerr<<double(sizeof(f))/1048576<<endl;
    ios::sync_with_stdio(false);
    int i,j,k,l,r,x,y;
    cin>>T;
    while(T--){
        cin>>s+1,n=strlen(s+1);
        for(i=1;i<=n;++i)s[i]-='0';
        for(--s[i=n];s[i]<0;s[i]+=10,--s[--i]);
        l=DP();
        cin>>s+1,n=strlen(s+1);
        for(i=1;i<=n;++i)s[i]-='0';
        r=(DP()+M-l)%M;
        printf("%d\n",r);
    }
    // fprintf(stderr,"time:%.12lf\n",clk/CLOCKS_PER_SEC);
    return 0;
}
