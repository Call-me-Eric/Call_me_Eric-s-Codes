#include <cstring>
#include <cstdio>
#define inf 99999999

using namespace std;

int n, s[20], f[1001] = {0,2}, size = 1, ans;

int is_sushu(int);
int is_huiwen(int);

int is_sushu(int a){
	for(int i = 1;i <= size;i++)
		if(a % f[i] == 0)
			return 0;
	f[++size] = a; 
	return 1;
}

int is_huiwen(int a){
	int i = 0;
	while(a > 0){
		s[i++] = a % 10;
		a /= 10;
	}
	int j = 0, k = i - 1;
	while(j < k)
		if(s[j] != s[k])
			return 0;
		else j++, k--;
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int i = 11;i <= n;i++){
		memset(s,0,sizeof(s));
		if(is_sushu(i)){/*判断是否素数*/
			if(is_huiwen(i))/*进一步判断*/
				++ans;
		}
	}
	printf("%d",ans);
	return 0;
}

