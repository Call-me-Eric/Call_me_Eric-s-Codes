#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct student{
	int chinese, math, english;
	int total, list;
}a[1001];
struct cmp{
	bool operator ()(student a,student b){
		if(a.total != b.total){
			return a.total < b.total ? 0 : 1;
		}
		else{
			if(a.chinese != b.chinese){
				return a.chinese < b.chinese ? 0 : 1;
			}
			else return a.list > b.list ? 0 : 1;
		}
	}
};
int n;
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++){
		scanf("%d%d%d",&a[i].chinese,&a[i].math,&a[i].english);
		a[i].total = a[i].chinese + a[i].math + a[i].english;
		a[i].list = i;
	}
	sort(a + 1,a + 1 + n,cmp());
	for(int i = 1;i <= 5;i ++){
		printf("%d %d\n",a[i].list,a[i].total);
	}
	return 0;
}

