#include<bits/stdc++.h>
#define int long long 
#define read(a) scanf("%lld",&a)
using namespace std;
const int N=5e4+5;
int gcd(int x,int y){
	if(!y)  return x;
	else return gcd(y,x%y);
} 
int n,q,k=1;
int ans[N];
struct old{
	int a,b;
}o[N];
struct nevv{
	int c,d;
}m[N];
struct que{
	int g,cnt;
}qu[N],ask[N];
bool cmp(que x,que y){
	return x.g<y.g;
}
signed main(){
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
	read(n);read(q);
	for(int i=1;i<=n;i++){
		read(o[i].a);read(o[i].b);
		qu[i].cnt=i;
		qu[i].g=gcd(o[i].a,o[i].b);
	}
	for(int i=1;i<=q;i++){
		read(m[i].c);read(m[i].d);
		ask[i].cnt=i;
		ask[i].g=gcd(m[i].c,m[i].d);
	}
	sort(qu+1,qu+n+1,cmp);
	sort(ask+1,ask+q+1,cmp);
	for(int i=1;i<=q;i++){
//		if(ask[i].g==ask[i-1].g)  ans[ask[i].cnt]=ans[ask[i-1].cnt];
		for(int j=k;j<=n;j++){
//			printf("j=%lld\n",j);
			if(ask[i].g<qu[j].g){
				if(ask[i].g==ask[i].g)  break;
				k=j-1;
				break;
			}
			if(ask[i].g==qu[j].g){
				int ii=ask[i].cnt,jj=qu[j].cnt;
//				printf("%lld %lld==%lld %lld\n",ask[i].g,qu[j].g,ii,jj);
				if(o[jj].a>=m[ii].c&&o[jj].b>=m[ii].d){
					ans[ii]++;
				}
			}
		}
	}
	for(int i=1;i<=q;i++){
		printf("%lld\n",ans[i]);
	}
}
