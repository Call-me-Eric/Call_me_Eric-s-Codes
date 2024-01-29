#include <stdio.h>
#include <string.h>

int main()
{
	int sn;
	char nums[8] = {0};
	long long sum = 0,num = 0, tmp;
	int i, j, len;

	scanf("%d", &sn);
	if (sn == 16) scanf("%x", &num);
	else{ 
		scanf("%s", nums);
		len = strlen(nums);
		for(i = 0; i < len; i++){
			tmp = nums[i] - '0';
			for (j = 0; j < len - i - 1; j++)tmp *= sn;
			num += tmp;
		}
	}

	for (i = 0; i < 30; i++, sum = 0){ 
		for (tmp = num; tmp; tmp /= sn)sum = sum * sn + tmp % sn;
		if (sum == num) break;
		num += sum;
	}
	if (i == 30) printf("Impossible!");
	else printf("STEP=%d", i);
	return 0;
}

