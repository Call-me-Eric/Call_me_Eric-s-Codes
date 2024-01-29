#include <cstdio>
using namespace std;
int main() {
    long long x, n,sum = 0,week, day;
    scanf("%lld %lld",&x, &n);	//3.10 
    week = (n + x -1) / 7;	//假设从周一开始算 ，过了多少周 
    day = (n + x -1) % 7;	// 假设从周一开始算 ，剩了多少周 
    if (day == 6) day = 0;
    day = day - (x - 1);		//把多算的减掉 
    if (day < 0) {				//如果不够减，从周上减 
    	week --;
    	day = day + 7;
	}
    sum = (week * 5 + day) * 250;
    printf("%lld\n",sum);
    return 0;
}
