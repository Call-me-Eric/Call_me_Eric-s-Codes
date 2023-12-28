#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a),i##END=(b);i<=i##END;i++)
#define Rof(i,b,a) for(int i=(b),i##END=(a);i>=i##END;i--)
#define go(u) for(int i=head[u];i;i=nxt[i])
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
bool ST;
const int N=710,p=998244353;
inline int inv(int a,int b=p-2){
	int x=1;while(b){
		if(b&1)(x*=a)%=p;
		(a*=a)%=p,b>>=1;
	}return x;
}
int n,q,a[N*2][N],idx,lst[N],id[N];
int sta[N],ans[N][N],tmp[N];
int b[N][N],X[N];
struct Gauss{
	int A[N][N];
	void clear(int i){A[i][i]=0;}
	int ins(int id){
		memcpy(tmp,a[id],sizeof tmp);
		For(i,1,n)if(tmp[i]%p){
			tmp[i]%=p;
			if(!A[i][i]){
				int iv=inv(tmp[i]);
				For(j,i,n+1)A[i][j]=tmp[j]%p*iv%p;
				return i;
			}
			Rof(j,n+1,i)(tmp[j]-=tmp[i]*A[i][j]);
			if(i%9==0||i==n)For(j,i+1,n+1)tmp[j]%=p;
			assert(!tmp[i]);
		}if(tmp[n+1])return -1;
		else return -2;
	}
	void qry(int id){
		//memcpy(b,A,sizeof A);
		For(i,1,n)For(j,i,n+1)b[i][j]=A[i][j];
		Rof(i,n,1){
			//For(j,i+1,n)if(b[i][j])(b[i][n+1]-=b[i][j]*X[j])%=p;
			ans[id][i]=X[i]=(b[i][n+1]%p+p)%p;
			For(j,1,i-1)if(b[j][i])(b[j][n+1]-=b[j][i]*X[i]);
			if(i%9==0)For(j,1,i-1)b[j][n+1]%=p;
		}
	}
}G;
struct Tree{
	#define ls (k<<1)
	#define rs (k<<1|1)
	vector<int> t[N<<2];
	void ins(int k,int l,int r,int x,int y,int o){
		if(x>y)return;
		if(x<=l&&r<=y)return t[k].push_back(o),void();
		int m=l+r>>1;
		if(x<=m)ins(ls,l,m,x,y,o);
		if(y>m)ins(rs,m+1,r,x,y,o);
	}
	void solve(int k,int l,int r){
		int len=t[k].size();
		For(i,0,len-1){
			int s=G.ins(t[k][i]);
			if(s<0){
				For(x,l,r)sta[x]=s;
				For(j,0,i-1)G.clear(t[k][j]);
				return;
			}else t[k][i]=s;
		}
		if(l==r)G.qry(l);
		else{
			int m=l+r>>1;
			solve(ls,l,m),solve(rs,m+1,r);
		}
		For(i,0,len-1)G.clear(t[k][i]);
	}
}T;
int stk[30],tp;
void write(int x){
	do stk[++tp]=x%10,x/=10;while(x);
	while(tp)putchar(stk[tp--]^48);
}
bool ED;
signed main(){
	fprintf(stderr,"%.2lf MB\n",abs(&ED-&ST)/1024.0/1024.0);
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	idx=n=read(),q=read();
	For(i,1,n){
		lst[i]=0,id[i]=i;
		For(j,1,n+1)a[i][j]=read();
	}For(tim,1,q){
		int z=read();
		T.ins(1,0,q,lst[z],tim-1,id[z]);
		id[z]=++idx;For(j,1,n+1)a[idx][j]=read();
		lst[z]=tim;
	}For(z,1,n)T.ins(1,0,q,lst[z],q,id[z]);
	T.solve(1,0,q);For(i,0,q){
		if(sta[i]==-1)puts("No");
		else if(sta[i]==-2)puts("Many");
		else{For(j,1,n)write(ans[i][j]),putchar(' ');puts("");}
	}
	return 0;
}
