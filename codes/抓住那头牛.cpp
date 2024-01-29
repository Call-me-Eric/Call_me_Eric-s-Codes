#include<cstring>
#include<cstdio>
using namespace std;
int x, y;
struct aaa{
	int s, x;
}que[500001];
int head, tail;
bool book[500001];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&x,&y);
		head = 1;
		tail = 1;
		memset(que,0,sizeof(que));
		memset(book,0,sizeof(book));
		que[tail].x = x;
		que[tail].s = 0;
		book[que[tail].x] = 1;
		tail++;
		while(head < tail){
			if(que[head].x < y){
				if(!book[que[head].x + 1]){
					que[tail].x = que[head].x + 1;
					que[tail].s = que[head].s + 1;
					book[que[tail].x] = 1;
					tail++;
					if(que[tail - 1].x == y)break;
				}
				if(!book[que[head].x * 2]){
					que[tail].x = que[head].x * 2;
					que[tail].s = que[head].s + 1;
					book[que[tail].x] = 1;
					tail++;
					if(que[tail - 1].x == y)break;
				}
			}
			if(!book[que[head].x - 1]){
				que[tail].x = que[head].x - 1;
				que[tail].s = que[head].s + 1;
				book[que[tail].x] = 1;
				tail++;
				if(que[tail - 1].x == y)break;
			}
			head++;
		}
		printf("%d\n",que[tail - 1].s);
	}
	return 0;
}
