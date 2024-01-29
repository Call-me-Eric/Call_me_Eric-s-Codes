#include <cmath>
#include <cstdio>
#define inf 99999999
using namespace std;

int f[10001] = {0}, size, a, b, book, ans;

int usesqrt(int);
int usef(int);

int usesqrt(int a){
	if(a == 1)return 0;
	for(int i = 2;i <= sqrt(a);i++)if(a % i == 0)return 0;
	f[++size] = a;
	book = 1;
	return 1;
}

int usef(int a){
	for(int i = 1;i <= size;i++)if(a % f[i] == 0)return 0;
	f[++size] = a;
	return 1;
}

int main(){
	scanf("%d%d",&a,&b);
	for(int i = a;i <= b;i++){
		if(usesqrt(i))
			ans++;
	}
	printf("%d",ans);
	return 0;
}

