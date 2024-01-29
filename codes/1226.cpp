#include <cstdio>
using namespace std;
int main() {
	int a, b, c, d, e, f, ans = 0, resa = 0, resb = 0;
	int v[4] = {0,5,3,1};
	while(1){
		scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);
		if(a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0)break;
		ans = f + d + e + (c + 3) / 4;
		resb = (d * 5) + v[c % 4];
		if(resb < b)ans += (b - resb + 8) / 9;
		resa = (ans * 36) - (36 * f) - (25 * e) - (16 * d) - (9 * c) - (4 * b);
		if(resa < a)ans += (a - resa + 35) / 36;
		printf("%d\n",ans);
	}
	return 0;
}

