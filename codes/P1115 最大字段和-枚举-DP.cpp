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
        if(b>0)                // ��a[i]+b[i-1]���С
            b += a[i];        // ����a[i]Ϊ������һ���Ӷ�
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
//ö��o��n3����ʱ 
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

