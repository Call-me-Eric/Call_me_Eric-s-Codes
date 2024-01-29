#include<cstdio>
using namespace std;
int main(){
	int hand = 0, money[13] = {0}, i, m_hand = 0;
	for(i = 1;i <= 12;i++){
		scanf("%d",&money[i]);
	}
	for(i = 1;i <= 12;i++){
		if(hand < 0){
			printf("-%d",i - 1);
			return 0;
		}
		hand += 300;
		hand -= money[i];
		if(hand / 100 != 0){
			m_hand += hand / 100 * 100;
			hand -= hand / 100 * 100;
		}
	}
	hand += m_hand + m_hand / 5;
	printf("%d\n",hand);
	return 0;
}
