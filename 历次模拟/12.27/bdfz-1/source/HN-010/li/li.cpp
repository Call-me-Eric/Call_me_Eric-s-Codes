#include<cstdio>
typedef unsigned long long u64;
int n,m,i,j,d[200086];
int a[200086],r[200086],c[200086];
int gd(int g){
	if(d[g]==g)return g;
	return d[g]=gd(d[g]);
}int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=0;i<n;++i)d[i]=i,c[i]=1;
	while(m--){
		scanf("%d%d",&i,&j);
		--i;--j;
		if(r[gd(i)]||r[gd(j)]){puts("-1");return 0;}
		if(gd(i)==gd(j))r[gd(i)]=1;
		else c[gd(j)]+=c[gd(i)],d[gd(i)]=gd(j);
		++a[i];++a[j];
	}for(i=0;i<n;++i){
		if(a[i]>3){puts("-1");return 0;}
		if(a[i]>2&&r[gd(i)]){puts("-1");return 0;}
		if(a[i]==3&&c[gd(i)]>4){puts("-1");return 0;}
	}
	u64 ans=0;
	for(i=m=0;i<n;++i){
		if(a[i]==3)m+=3;
		if(r[gd(i)])++m;
		if(d[i]==i)ans+=c[i]*(c[i]+1ull)/2;
	}
	if(m)printf("1 %d",m);
	else printf("0 %llu",ans);
	return 0;
}