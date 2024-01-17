#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N=2e3+7;
int fa[N];

struct node{
	int pos,val;
}a[N];
int n,t;

int f[N][N];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	fa[fx]=fy;
}

int mp[N];
int cnt;
int faQ[N];
int F[N],Z[N];

bool cmp(node x,node y){return x.pos<y.pos;}

int sum;

signed main(){
	freopen("distanced.in","r",stdin);
	freopen("distanced.out","w",stdout);
	scanf("%lld%lld",&n,&t);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i].pos);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i].val),sum+=a[i].val;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(abs(a[j].pos-a[i].pos)<=t){
				int fax=find(i),fay=find(j);
//				printf("%d %d\n",fax,fay);
				fa[fay]=fax;
			}
			else break;
		}
	}
	for(int i=1;i<=n;i++){
		int father=fa[i];
		if(!mp[father]) mp[father]=++cnt,faQ[cnt]=father;
		if(a[i].val<0) F[mp[father]]+=a[i].val;
		Z[mp[father]]+=a[i].val;
	}
	for(int i=1;i<=cnt;i++){
//		printf("%d %d\n",F[i],Z[i]);
	}
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=cnt;j++){
//			f[i][j]=f[i-1][j-1];
			f[i][j]=max({f[i-1][j-1],f[i-1][j-1]-F[i],f[i-1][j]-Z[i]});
		}
	}
	for(int i=1;i<=n;i++) f[cnt][i]=max(f[cnt][i-1],f[cnt][i]);
	for(int i=1;i<=n;i++) printf("%lld ",sum+f[cnt][i]);
	return 0;
}
