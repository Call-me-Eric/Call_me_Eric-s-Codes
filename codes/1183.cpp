#include <algorithm>
#include <cstdio>
using namespace std;

struct note{
	char id[11];
	int age;
	int i;
}a[10001]; 
int n;
struct cmp{
	bool operator()(const note& a, const note& b){
		if(a.age >= 60){
			if(b.age >= 60){
				if(a.age == b.age)return a.i < b.i;
				else return a.age > b.age;
			}
			else if(b.age < 60)return true;
		}
		return a.i < b.i;
	}
};

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%s%d",&(a[i].id),&a[i].age);
		a[i].i = i;
	}
	sort(a + 1, a + 1 + n, cmp());
	for(int i = 1;i <= n;i++){
		printf("%s\n",a[i].id);
	}
	return 0;
}

