#include<bits/stdc++.h>
using namespace std;
queue<int> que;
int n, ans;
int tmp;
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d",&tmp);
        que.push(tmp);
    }
    while(que.size() > 1){
        int x = que.front();
        que.pop();
        int y = que.front();
        que.pop();
        ans += x + y;
        que.push(x + y);
    }
    printf("%d",ans);
    return 0;
}