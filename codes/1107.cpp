#include <iostream>
#include <cstdio>
using namespace std;
int stard[101], end[101];
int main() {
	int l, m;
	int yzou;
	int min = 99999999, max = -99999999;
	scanf("%d%d",&l,&m);
	int tree = l + 1;
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&stard[i],&end[i]);
		if(stard[i] < min)min = stard[i];
		if(end[i] > max)max = end[i];
	}
	yzou = (max + 1) - (min - 1);
	int sheng = tree - yzou;
	printf("%d",sheng);
	return 0;
}
