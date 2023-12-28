#include<cstdio>
#include<vector>
using namespace std;
const int o=710,MOD=998244353;
inline int qp(int b,int f){int res=1;for(;f;f>>=1,b=b*1ll*b%MOD) if(f&1) res=res*1ll*b%MOD;return res;}
int n,q,tim[o],id[o],a[o*2][o],cnt;vector<int> vec[o*99];
void ins(int id,int ql,int qr,int val,int l=0,int r=q){
	if(ql<=l&&r<=qr){vec[id].push_back(val);return;}
	int md=l+r>>1;
	if(ql<=md) ins(id<<1,ql,qr,val,l,md);
	if(md<qr) ins((id<<1)|1,ql,qr,val,md+1,r);
}
struct info{
	int b[o][o];bool flg1,flg2;
	inline void ins(int*tmp){
		if(flg1) return;
		static int a[o];
		for(int i=1;i<=n+1;++i) a[i]=tmp[i];
		for(int i=1,coef;i<=n;++i) if(a[i]){
			if(!b[i][i]){for(int j=i;j<=n+1;++j) b[i][j]=a[j];return;}
			coef=(MOD-a[i])*1ll*qp(b[i][i],MOD-2)%MOD;
			for(int j=i;j<=n+1;++j) if(b[i][j]) a[j]=(a[j]+coef*1ll*b[i][j])%MOD;
		}
		if(a[n+1]) flg1=1;
		else flg2=1;
	}
	inline void calc(){
		if(flg2){printf("Many\n");return;}
		for(int i=n;i;--i){
			b[i][n+1]=b[i][n+1]*1ll*qp(b[i][i],MOD-2)%MOD;
			if(b[i][n+1]) for(int j=i;--j;) if(b[j][i]) b[j][n+1]=(b[j][n+1]+(MOD-b[j][i])*1ll*b[i][n+1])%MOD;
		}
		for(int i=1;i<=n;++i) printf("%d ",b[i][n+1]);
		putchar('\n');
	}
}v[12];
void slv(int dep,int id,int l,int r){
	for(int i=vec[id].size();i--;) v[dep].ins(a[vec[id][i]]);
	if(v[dep].flg1){for(int i=l;i<=r;++i) printf("No\n");return;}
	if(l==r){v[dep].calc();return;}
	int md=l+r>>1;
	v[dep+1]=v[dep];slv(dep+1,id<<1,l,md);
	v[dep+1]=v[dep];slv(dep+1,(id<<1)|1,md+1,r);
}
int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	scanf("%d%d",&n,&q);cnt=n;
	for(int i=1;i<=n;++i){
		id[i]=i;
		for(int j=1;j<=n+1;++j) scanf("%d",&a[i][j]);
	}
	for(int i=1,z;i<=q;++i){
		scanf("%d",&z);ins(1,tim[z],i-1,id[z]);tim[z]=i;id[z]=++cnt;
		for(int j=1;j<=n+1;++j) scanf("%d",&a[id[z]][j]);
	}
	for(int i=1;i<=n;++i) ins(1,tim[i],q,id[i]);
	slv(0,1,0,q);
	return 0;
}
