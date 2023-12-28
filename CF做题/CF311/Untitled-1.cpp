#include <bits/stdc++.h>
#define GC c=getchar()
#define IG isdigit(c)
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
template<class T>void rd(T &x=0,char GC,bool f=1)
{
    for(x=0;!IG;GC)f=c!='-';for(;IG;GC)x=x*10+(c^48);x=f?x:-x;
}
template<class A,class... B>void rd(A& x,B&... y) {rd(x),rd(y...);}
using namespace std;
const int N(1e5+5),P(95542721),B(50);
int n,lab,q,a[N+5],b[50][N+5];
int tot,pos[N+5],L[N/B+5],R[N/B+5],s[50][N/B+5],tag[N+5];

int pw3(int x) {return 1ll*x*x%P*x%P;}
void inc(int &x,int y) {x+=y,x>=P?x-=P:1;}

void build() 
{
	while(R[tot]<n) ++tot,L[tot]=R[tot-1]+1,R[tot]=R[tot-1]+B;
	U(i,1,tot)
		U(j,L[i],R[i])
		{
			pos[j]=i;
			U(z,0,47) inc(s[z][i],b[z][j]),b[z+1][j]=pw3(b[z][j]);
		}
}

#define doit(k) {U(z,0,47) inc(s[z][k],P-b[z][i]),inc(s[z][k],b[z+1][i]),b[z][i]=b[z+1][i];b[48][i]=b[0][i];}

void mdy(int l,int r)
{
	int pl(pos[l]),pr(pos[r]);
	if(pl==pr) 
	{
		U(i,l,r) doit(pl);return ;
	}
	U(i,l,R[pl]) doit(pl);
	U(i,L[pr],r) doit(pr);
	U(i,pl+1,pr-1) ++tag[i];
}

int ask(int l,int r)
{
	int pl(pos[l]),pr(pos[r]),res(0);
	if(pl==pr)
	{
		U(i,l,r) inc(res,b[tag[pl]%48][i]);return res;
	} 
	U(i,l,R[pl]) inc(res,b[tag[pl]%48][i]);
	U(i,L[pr],r) inc(res,b[tag[pr]%48][i]);
	U(i,pl+1,pr-1) inc(res,s[tag[i]%48][i]);
	return res;
}
signed main()
{
	rd(n);
	U(i,1,n) rd(a[i]),b[0][i]=a[i]%P;
	build(),rd(q);
	while(q--)
	{
		int op,l,r; rd(op,l,r);
		if(op==1)printf("%d\n",ask(l,r));
		else mdy(l,r);
        // for(int j = 1;j <= n;j++){printf("a[%d] = %d\n",j,ask(j,j));}
	}
    return 0;
}
