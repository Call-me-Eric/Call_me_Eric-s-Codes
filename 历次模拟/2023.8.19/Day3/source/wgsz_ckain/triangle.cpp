#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

const int N=105;

struct Node{
	int mx[10];
	Node(){
		memset(mx, ~63, sizeof(mx));
	}
	Node operator +(const Node &o)const{
		int tmp[20]; Node re;
		for(int i=0; i<10; i++) tmp[i]=mx[i], tmp[i+10]=o.mx[i];
		sort(tmp, tmp+20, greater<int>());
		for(int i=0; i<10; i++) re.mx[i]=tmp[i];
		return re;
	}
};

int n, K, a[N][N];
Node f[N][N];

signed main(){
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
	n=rd(), K=rd();
	for(int i=1; i<=n;i++){
		for(int j=1; j<=i; j++){
			a[i][j]=rd();
			
			if(i==1) f[i][j].mx[0]=a[i][j];
			else{
				if(j>1) f[i][j]=f[i][j]+f[i-1][j-1];
				if(j!=i) f[i][j]=f[i][j]+f[i-1][j];
				for(int k=0; k<10; k++) f[i][j].mx[k]+=a[i][j];
			}
		}
	}
	Node ans;
	for(int i=1; i<=n; i++) ans=ans+f[n][i];
	printf("%d\n", ans.mx[K-1]);
	return 0;
}
