#include <cstdio>
using namespace std;
int main() {
    long long x, n,sum = 0,week, day;
    scanf("%lld %lld",&x, &n);	//3.10 
    week = (n + x -1) / 7;	//�������һ��ʼ�� �����˶����� 
    day = (n + x -1) % 7;	// �������һ��ʼ�� ��ʣ�˶����� 
    if (day == 6) day = 0;
    day = day - (x - 1);		//�Ѷ���ļ��� 
    if (day < 0) {				//����������������ϼ� 
    	week --;
    	day = day + 7;
	}
    sum = (week * 5 + day) * 250;
    printf("%lld\n",sum);
    return 0;
}
