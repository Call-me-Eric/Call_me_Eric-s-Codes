#include <cstdio>
using namespace std;
long long f[25][25][25];
long long fun(long long a, long long b, long long c){
	if(a <= 0 || b <= 0 || c <= 0)
		return 1;
	
			
	if(a>20 || b > 20 || c > 20)
		return fun(20,20,20);
	if (a < b && b < c){
		if(f[a][b][c] == 0) 
			f[a][b][c] =  fun(a,b,c-1) + fun(a-1,b,c-1) - fun(a-1,b-1,c-1);
	}
	else if(f[a][b][c] == 0) 
		f[a][b][c] =  fun(a-1,b,c)+fun(a-1,b-1,c)+fun(a-1,b,c-1)-fun(a-1,b-1,c-1);	;
	return f[a][b][c];
}
int main() {
	long long a, b, c; 
	while(1){
		scanf("%lld%lld%lld", &a ,&b ,&c);
		if(a == -1 && b == -1 && c == -1)
			break;
		printf("w(%lld, %lld, %lld) = %lld\n",a ,b, c, fun(a,b,c));
	}
	return 0;
}

