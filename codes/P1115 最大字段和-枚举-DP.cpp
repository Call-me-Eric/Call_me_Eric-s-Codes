#include <cstdio>
#include <iostream>
#define INF 0x7fffffff
using namespace std;
int a[200005];
int MaxSubArray(int a[],int n)
{
    int i,b = 0,sum = -INF;
    for(i = 1;i <= n;i++)
    {
        if(b>0)                // 若a[i]+b[i-1]会减小
            b += a[i];        // 则以a[i]为首另起一个子段
        else    
            b = a[i];
        if(b > sum)    
            sum = b;
    }
    return sum;
}

int main() {
	int n, sum = -INF, maxx = -INF;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
//枚举o（n3）超时 
//	for (int i = 1; i <= n; i++){
//		for(int j = 1; j <= i; j++){
//			sum = 0;
//			for (int k = j; k <= i; k++){
//				sum += a[k];
//			}
//			if(sum > maxx)
//				maxx = sum;
//		}
//	}
	cout << MaxSubArray(a,n) << endl;
	return 0;
}

