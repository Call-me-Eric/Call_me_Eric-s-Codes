#include<bits/stdc++.h>
using namespace std;
priority_queue<int,vector<int>,less<int> > que;
signed main(){
    que.push(1);que.push(2);
    printf("%d\n",que.top());
    return 0;
}