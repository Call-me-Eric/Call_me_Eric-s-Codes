#include<cstdio>
#include<cmath>
using namespace std;
int main(){
	int men, n;
	scanf("%d",&n);
	double x, y, far = 0.0, res = 0.0;
	for(int i = 1;i <= n;i++){
		scanf("%lf%lf%d",&x,&y,&men);
		far += sqrt(x*x+y*y);
//		res += far / 50;
		res += men * 1.5;
	}
	res += far / 50 * 2;

	res = ceil(res);
	printf("%.0lf\n",res);
	return 0;
}
