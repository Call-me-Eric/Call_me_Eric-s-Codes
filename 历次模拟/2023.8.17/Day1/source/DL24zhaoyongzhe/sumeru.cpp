#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
double eps = 1e-10;
struct node{
	double arr[5];
}a[5];
int tmp[13];
int gcd(int x,int y){
	return y ? gcd(y,x % y) : x ;
}
signed main(){
	freopen("sumeru.in","r",stdin);
	freopen("sumeru.out","w",stdout);
int Test = read();
for(int T = 1;T <= Test;T++){
//	memset(tot,0,sizeof(tot));
	memset(a,0,sizeof(a));
	for(int i = 1;i <= 4;i++){
//		tot[i] = 1;
		for(int j = 1;j <= 3;j++){
			a[j].arr[i] = read();
		}
	}
	for(int i = 1;i <= 3;i++){
//		if(i == 3)
//		for(int j = 1;j <= 3;j++){
//			int g = a[j].arr[1];
//			for(int k = 2;k <= 4;k++){
//				if(!a[j].arr[k])
//				g = gcd(g,a[j].arr[k]);
//			}
//			for(int k = 1;k <= 4;k++){
//				if(!a[j].arr[k])a[j].arr[k] /= g;
//			}
//		}
		if(a[i].arr[i] < eps && a[i].arr[i] > -eps){
			for(int j = i + 1;j <= 3;j++){
				if(a[j].arr[i]){
					swap(a[i],a[j]);
					break;
				}
			}
		}
		if(a[i].arr[i] < eps && a[i].arr[i] > -eps)continue;
		if(a[i].arr[i] < -eps){
			for(int j = 1;j <= 4;j++){
				a[i].arr[j] = -a[i].arr[j];
			}
		}
		for(int j = 1;j <= 3;j++){
			if(!a[j].arr[i] || j == i)continue;
			double tmp1 = a[j].arr[i], tmp2 = a[i].arr[i];
			if(tmp1 < 0){
				for(int k = 1;k <= 4;k++){
					a[j].arr[k] = -a[j].arr[k];
				}
				tmp1 = -tmp1;
			}
			double pw = tmp2 / tmp1;
			for(int k = 1;k <= 4;k++){
				a[j].arr[k] = a[i].arr[k] - a[j].arr[k] * pw;
			}
		}
	}
	bool flag = true;
	for(int i = 1;i <= 3;i++){
		if(a[i].arr[i] < eps && a[i].arr[i] > -eps && !(a[i].arr[4] < eps && a[i].arr[4] > -eps)){
			flag = false;break;
		}
		if(a[i].arr[i] > eps && a[i].arr[4] < eps){
			flag = false; break;
		}
		if(a[i].arr[i] < eps && a[i].arr[4] > eps){
			flag = false;break;
		}
//		if(!a[i].arr[i])continue;
//		if(a[i].arr[4] % a[i].arr[i]){
//			flag = false;break;
//		}
	}
//	if(T == 30){
//		for(int i = 1;i <= 3;i++){
//			for(int j = 1;j <= 4;j++){
//				tmp[i * 3 + j - 3] = a[i].arr[j];
//			}
//		}
//	}
	puts(flag ? "YES" : "NO");
}
//	for(int i = 1;i <= 3;i++){
//		for(int j = 1;j <= 4;j++){
//			printf("%d ",tmp[i * 3 + j - 3]);
//		}
//		puts("");
//	}
	return 0;
}

