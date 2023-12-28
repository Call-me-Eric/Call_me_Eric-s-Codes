#include<bits/stdc++.h>
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=260;
void chmn(int &x,int y){(x>y)&&(x=y);}
void chmx(int &x,int y){(x<y)&&(x=y);}
int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
int r,g,b,m,n;
int fa[N],F[3][N],nd[3];
int X[N*N],Y[N*N];
int c[N*N],cnt[3];
int get(int *W,int x){return W[x]==x?x:W[x]=get(W,W[x]);}
void work(int op){
	cnt[op]=0;
	rep(i,n)F[op][i]=fa[i];
	rep(i,m)if(c[i]==op){
		int x=get(F[op],X[i]);
		int y=get(F[op],Y[i]);
		if(x==y)continue;
		F[op][x]=y;cnt[op]++;
	}
}
int ans[N*N],a[N*N];
bool solve(){
	rep(i,m)ans[i]=0;
	rep(i,n)fa[i]=i;
	rep(i,m)a[i]=i;random_shuffle(a+1,a+1+m);
	nd[0]=r;nd[1]=g;nd[2]=b;
	rep(k,n-1){
		rep(i,n)get(fa,i);
		work(0);work(1);work(2);
		For(i,0,2)if(cnt[i]<nd[i]){puts("NO");exit(0);}
		int fi=-1,O=0;
		For(i,0,2)if(nd[i])if(fi==-1||cnt[i]-nd[i]<cnt[fi]-nd[fi])fi=i;
		head:if(nd[fi])rep(I,m)if(c[a[I]]==fi){
			int i=a[I];
			int x=get(fa,X[i]);
			int y=get(fa,Y[i]);
			if(x==y)continue;
			int fl=1;
			For(j,0,2)if(j!=fi){if(nd[j]>=cnt[j]&&get(F[j],X[i])==get(F[j],Y[i]))fl=0;}
			if(fl){
				fa[get(fa,X[i])]=get(fa,Y[i]);
				nd[fi]--;
				ans[i]=1;
				goto end;
			}
		}
		O++;fi++;fi%=3;
		if(O==2)
			return 0;
		goto head;
		end:;
	}
	puts("YES");
	assert(nd[0]==0&&nd[1]==0&&nd[2]==0);
	rep(i,m)putchar(ans[i]?'1':'0');
	exit(0);
}
signed main(){
	//printf("%.5lf\n",(&ppp-&pppp)/1024.0/1024.0);
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	r=read(),g=read(),b=read(),m=read();
	n=r+g+b+1;
	rep(i,m){
		X[i]=read();
		Y[i]=read();
		char C;cin>>C;
		c[i]=(C=='r'?0:(C=='g'?1:2));
	}
	rep(i,max(130000000/n/m,1))solve();
	//assert(0);////////////////////////////////////////////
	puts("NO");
	return 0;
}
