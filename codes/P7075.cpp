#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
//BC 4714/12/31 ~ BC 1/12/31 = 1721424
//BC 1/12/31 ~ 1582/10/4 = 577737
//577825 = 1582/12/31
//577460 = 1581/12/31
long long q, r;
long long ans;
long long read() {
	long long x = 0, w = 1;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') w = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * w;
}
long long f1[5000];
long long f2[2000];
long long month[13];
long long sum(long long y){
	return (y * 365 + y / 4 - y / 100 + y / 400 + 12);
}
void F1(){//在公元前
	long long p = lower_bound(f1 + 1,f1 + 4714,r) - f1;
	long long y = 4714 - p, m = 0, d = 0;
	r -= f1[p - 1];
	month[1] = 31;month[2] = 28 + ((y - 1) % 4 == 0);
	month[3] = 31;month[4] = 30;month[5] = 31;month[6] = 30;month[7] = 31;
	month[8] = 31;month[9] = 30,month[10] = 31;month[11] = 30;month[12] = 31;
	for(int i = 1;i <= 12;i++){
		month[i] += month[i - 1];
	}
	for(int i = 1;i <= 12;i++){
		if(month[i] >= r){
			m = i;
			d = r - month[i - 1];
			break;
		}
	}
	printf("%lld %lld %lld BC\n",d, m, y);
	return;
}
void F2(){//公元后1528/10/4以前
	long long p = lower_bound(f2 + 1,f2 + 1 + 1582,r) - f2;
	long long y = p, m = 0, d = 0;
	r -= f2[p - 1];
	month[1] = 31;month[2] = 28 + (y % 4 == 0);
	month[3] = 31;month[4] = 30;month[5] = 31;month[6] = 30;month[7] = 31;
	month[8] = 31;month[9] = 30,month[10] = 31;month[11] = 30;month[12] = 31;
	for(int i = 1;i <= 12;i++){
		month[i] += month[i - 1];
	}
	for(int i = 1;i <= 12;i++){
		if(month[i] >= r){
			m = i;
			d = r - month[i - 1];
			break;
		}
	}
	printf("%lld %lld %lld\n",d, m, y);
	return;
	
}
void F3(){
	if(r <= 577825){
		long long y = 1582,m = 0, d = 0;
		r -= 577460;
		month[1] = 31;month[2] = 28 + (y % 4 == 0);
		month[3] = 31;month[4] = 30;month[5] = 31;month[6] = 30;month[7] = 31;
		month[8] = 31;month[9] = 30,month[10] = 31;month[11] = 30;month[12] = 31;
		for(int i = 1;i <= 12;i++){
			if(month[i] >= r){
				m = i;
				d = r - month[i - 1];
				break;
			}
		}
		printf("%lld %lld %lld\n",d,m,y);
		return;
	}
	else{
		long long l = 1583, R = 1e9 + 3;
		long long mid = 0;
		while(l < R){
			mid = l + ((R - l) >> 1);
			if(sum(mid) >= r){
				R = mid;
			}
			else l = mid + 1;
		}
		long long y = l,d = 0,m = 0;
		r -=  sum(y - 1);
		month[1] = 31;month[2] = 28 + ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);
		month[3] = 31;month[4] = 30;month[5] = 31;month[6] = 30;month[7] = 31;
		month[8] = 31;month[9] = 30,month[10] = 31;month[11] = 30;month[12] = 31;
		for(int i = 1;i <= 12;i++){
			month[i] += month[i - 1];
		}
		for(int i = 1;i <= 12;i++){
			if(month[i] >= r){
				m = i;
				d = r - month[i - 1];
				break;
			}
		}
		printf("%lld %lld %lld\n",d,m,y);
		return;
	}
}
int main(){
	for(int i = 1;i <= 4713;i++){
		f1[i] = 365 + ((i - 1) % 4 == 0);
	}
	for(int i = 1;i <= 4713;i++){
		f1[i] += f1[i - 1];
	}
	for(int i = 1;i <= 1582;i++){
		f2[i] = 365 + (i % 4 == 0);
	}
	for(int i = 1;i <= 1582;i++){
		f2[i] += f2[i - 1];
	}
	
	q = read();
	for(int i = 1;i <= q;i++){
		ans = 0;
		r = read();
		r += 1;
		if(r < 1721424){
			F1();
		}
		else if(r == 1721424){
			printf("31 12 1 BC\n");
		}
		else{
			r -= 1721424;
			if(r <= 577737){
				F2();
			}
			else{
				r += 10;
				F3();
			}
		}
	}
	return 0;
}

