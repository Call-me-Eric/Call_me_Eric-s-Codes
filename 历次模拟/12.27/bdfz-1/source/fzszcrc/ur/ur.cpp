#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int sum=0,fh=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')fh=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		sum=sum*10+c-'0';
		c=getchar();
	}
	return sum*fh;
}
#define maxn 1000009 
int n,k,nowp=0;
int cnt=0,p[maxn];
bool vis[maxn],ans[maxn];
void build(){
	for(int i=2;i<maxn;i++){
		if(!vis[i])p[++cnt]=i;
		for(int j=1;j<=cnt&&1ll*p[j]*i<maxn;j++){
			vis[p[j]*i]=true;
			if(i%p[j]==0)break;
		}
	}
	return ;
}
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	n=read();k=read();
	build();
	for(int i=1;i<=cnt;i++)if(n%p[i]==0){
		if(!nowp||k-k%nowp<k-k%p[i])nowp=p[i];
	}
	for(int j=1;j<=k/nowp;j++)for(int o=j;o<=n;o+=(n/nowp))ans[o]=true;
	for(int i=1;i<=n;i++)putchar('0'+ans[i]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}

