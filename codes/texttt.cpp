#include<bits/stdc++.h>
using namespace std;
int main(){
    priority_queue<int,vector<int>,greater<int>> b;
    b.push(1);
    b.push(5);
    printf("%d",b.top());
    return 0;
}
