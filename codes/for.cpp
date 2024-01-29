#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
struct note{
	string name;
	double chinese, math, english;
	double science, thinking_goods;
	double total;
	note(double a = 0.0){
		science = thinking_goods = a;
		chinese = math = english = a;
		total = a;name.clear();
	}
	void in(){
		cin >> name;
		scanf("%lf%lf%lf%lf%lf",&chinese, &math, &english, &science, &thinking_goods);
		total = chinese + math + english + science + thinking_goods;
	}
	void out(){
		cout << name;
		printf("\t%.1lf\t%.1lf\t%.1lf\t%.1lf\t%.1lf\t%.1lf\n",
		chinese, math, english, science, thinking_goods, total);
	}
};
struct cmp{
	bool operator () (note a, note b){
		int x2 = (a.total * 10);
		int y2 = (b.total * 10);
		x2 = x2 % 10;y2 = y2 % 10;
		int x1 = a.total;int y1 = b.total;
		if(x1 < y1)return true;
		else if(x1 > y1)return false;
		else if(x2 < y2)return true;
		else return false;
	}
};
note a[46];
int main() {
//	freopen("for.in","r",stdin);
//	freopen("for.out","w",stdout);
	int n = 4;
	for(int i = 1;i <= n;i++){
		a[i].in();
	}
	sort(a + 1, a + 1 + n, cmp());
	int k = 1;
	for(int i = n;i >= 1;i--){
		if(a[i].total == a[i + 1].total)printf("%d\t",k + 1);
		else printf("%d\t",k);
		a[i].out();
		k++;
	}
	return 0;
}

