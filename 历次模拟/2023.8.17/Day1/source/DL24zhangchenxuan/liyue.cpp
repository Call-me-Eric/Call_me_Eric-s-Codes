#include<bits/stdc++.h>
#define read(a) scanf("%d",&a)
using namespace std;
const int N=5e3+5;
int n,q,ll,rr,maxx,maxs;
int a[N];
bool sq[N*N];
int main(){
	freopen("liyue.in","r",stdin);
	freopen("liyue.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		if(maxx<=a[i]){
			maxs=maxx;
			maxx=a[i];
		}
	}
	int sqr=sqrt(maxx+maxs);
	for(int i=1;i<=sqr;i++)  sq[i*i]=1;
	read(q);
	while(q--){
		int ans=0;
		read(ll);read(rr);
		for(int i=ll;i<rr;i++){
			for(int j=i+1;j<=rr;j++){
				if(sq[a[i]+a[j]])  ans++;
			}
		}
		printf("%d\n",ans);
	}
}
