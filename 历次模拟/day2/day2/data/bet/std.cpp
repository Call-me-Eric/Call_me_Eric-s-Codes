#include <bits/stdc++.h>
using namespace std;
int n,c[500010],suf[20][500010],lg2[500010];
int qry(int l,int r,int k){
	if(l>r) return 0;
	int x=l+((r-l)>>k<<k),res=suf[k][l]^suf[k][x]^c[x]^c[min(x+(1<<(k-1)),r+1)];
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;i++) lg2[i]=lg2[i>>1]+1;
	for(int i=1,w;i<=n;i++) scanf("%d",&w),c[w]^=1;
	for(int i=n;i>=1;i--) c[i]^=c[i+1];
	for(int j=1;j<=lg2[n];j++) for(int i=n-(1<<j)+1;i>=1;i--){
		suf[j][i]=suf[j][i+(1<<j)]^c[i]^c[i+(1<<(j-1))];
	}
	for(int j=2;j<=n+1;j++){
		int ans=0;
		for(int k=0;k<=lg2[n];k++){
			int w=0;
			for(int l=0;l<=n;l+=j){
				w^=qry(l+(1<<k),min(l+j-1,n),k+1);
			}
			ans^=w<<k;
		}
		puts(ans?"First":"Second");
	}
}
