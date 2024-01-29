#include<bits/stdc++.h>
using namespace std;
struct block{
    int l, r;
    int col;
};
queue<block> que,tmpque;
int n;
const int maxn = 2e5 + 10;
bool book[maxn];
int main(){
    scanf("%d",&n);
    int temp;
    block tmp;
    for(int i = 1;i <= n;i++){
        scanf("%d",&temp);
        if(!que.empty() && que.back().col == temp){
            que.back().r++;
        }
        else{
            tmp.l = tmp.r = i;
            tmp.col = temp;
            que.push(tmp);
        }
    }
    int size = que.size();
    while(!que.empty()){
        size = que.size();
        int cnt = 0;
        while(!que.empty()){
            tmp = que.front();
            que.pop();
            while(book[tmp.l])  tmp.l++;
            printf("%d ",tmp.l);
            book[tmp.l] = 1;
            cnt++;
            tmp.l++;
            if(tmp.l <= tmp.r){
                if(!tmpque.empty() && tmp.col == tmpque.back().col){
                    tmpque.back().r = max(tmpque.back().r,tmp.r);
                    tmpque.back().l = min(tmpque.back().l,tmp.l);
                }
                else{
                    tmpque.push(tmp);
                }
            }
        }
        while(!tmpque.empty()){
            que.push(tmpque.front());
            tmpque.pop();
        }
        puts("");
    }
    
    return 0;
}