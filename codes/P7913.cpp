#include<iostream>
#include<queue>
#include<stdio.h>
#include<algorithm>
using namespace std;
const int maxm = 1e6 + 10;
int ans = 0;
int n, m1, m2;
int res1[maxm],res2[maxm];
struct node{
    int a,b;

}a1[maxm],a2[maxm];
bool operator < (node a,node b){
    return a.b > b.b;
}
struct cmp{
    bool operator ()(node a,node b){
        return a.a < b.a;
    }
};
void func(node* t,int m,int *res){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> lq;
    priority_queue<int,vector<int>,greater<int>> wq;
    for(int i = 1;i <= n;i++){
        wq.push(i);
    }
    for(int i = 1;i <= m;i++){
        while(!lq.empty() && t[i].a >= lq.top().first){
            wq.push(lq.top().second);
            lq.pop();
        }
        if(wq.empty())continue;
        int tmp = wq.top();
        wq.pop();
        res[tmp]++;
        lq.push(make_pair(t[i].b,tmp));
    }
    for(int i = 1;i <= n;i++)res[i] += res[i - 1];
}
int main(){
    //freopen("airport.in","r",stdin);
    //freopen("airport.out","w",stdout);
    scanf("%d%d%d",&n,&m1,&m2);
    for(int i = 1;i <= m1;i++){
        scanf("%d%d",&a1[i].a,&a1[i].b);
    }
    sort(a1 + 1,a1 + 1 + m1,cmp());
    for(int i = 1;i <= m2;i++){
        scanf("%d%d",&a2[i].a,&a2[i].b);
    }
    sort(a2 + 1,a2 + 1 + m2,cmp());
    func(a1,m1,res1);
    func(a2,m2,res2);
    for(int i = 0;i <= n;i++){
        ans = max(res1[i] + res2[n - i],ans);
    }
    printf("%d\n",ans);
    return 0;
}
/*

3 5 4
1 5
3 8
6 10
9 14
13 18
2 11
4 15
7 17
12 16

2 4 6
20 30
40 50
21 22
41 42
1 19
2 18
3 4
5 6
7 8
9 10
*/