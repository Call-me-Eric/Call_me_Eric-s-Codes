#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=50001;
int n,m;
char c[N];
ll search(int l,int r){
	ll ans=0;
	char b[r-l+1],cnt=0;
	for(int i=l;i<=r;i++){
		if(c[i]=='('||c[i]==')'||c[i]=='0'||c[i]=='w'){
			b[++cnt]=c[i];
		}
	}
	int num[cnt+1][5];
	for(int i=1;i<=cnt;i++){
		num[i][1]=num[i-1][1]+(b[i]=='('?1:0);
		num[i][2]=num[i-1][2]+(b[i]=='0'?1:0);
		num[i][3]=num[i-1][3]+(b[i]=='w'?1:0);
		num[i][4]=num[i-1][4]+(b[i]==')'?1:0);
	}
	for(int i=cnt;i>=5&&num[i][4];i--){
		if(b[i]==')'){
			for(int j=i-1;j>=4&&num[j][2]>=2;j--){
				if(b[j]=='0'){
					for(int k=j-1;k>=3&&num[k][3];k--){
						if(b[k]=='w'){
							for(int q=k-1;q>=2&&num[q][2];q--){
								if(b[q]=='0'){
									ans+=num[q-1][1];
								}
							}
						}
					}
				}
			}
		}
	}
	return ans;
}
int main(){
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("\n%s",c+1);
	for(int i=1;i<=m;i++){
		char t;
		scanf("\n%c",&t);
		if(t=='A'){
			int x;char y;
			scanf("%d %c",&x,&y);
			c[x]=y;
		}
		if(t=='B'){
			int l,r;char z;
			scanf("%d%d %c",&l,&r,&z);
			for(int i=l;i<=r;i++){
				c[i]=z;
			}
		}
		if(t=='C'){
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",search(l,r));
		}
	}
	return 0;
}
