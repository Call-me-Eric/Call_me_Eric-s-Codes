#include<bits/stdc++.h>
using namespace std;
int st, ed, ans;
int book[1000000][7];
int a[8] = {0,100000,10000,1000,100,10,1,1};
struct number{
    int num, pos, step;
}tmp,t;
void bfs(){
    tmp.num = st;
    tmp.pos = 1;
    tmp.step = 0;
    book[st][1] = 0;
    queue<number> que;
    que.push(tmp);
    int x = 0 ,y = 0;
    while(!que.empty()){
        tmp = que.front();
        que.pop();
        //TODO press swap0
        if(tmp.pos != 1){
            x = tmp.num / a[2];
            y = (tmp.num / a[tmp.pos + 1] * a[tmp.pos + 1] % 10);
            t.num = tmp.num - x * a[1] - y * a[tmp.pos] + x * a[tmp.pos] + y * a[1];
            printf("%d - %d * %d - %d * %d + %d * %d + %d * %d = %d\n",tmp.num , x , a[1] , y , a[tmp.pos] , x , a[tmp.pos] , y , a[1],t.num);
            t.step = tmp.step + 1;
            t.pos = tmp.pos;
            if(!book[t.num][t.pos] || (book[t.num][t.pos] != 0 && t.step < book[t.num][t.pos])){
                book[t.num][t.pos] = t.step;
                que.push(t);
            }
            if(t.num == ed){
                ans = t.step;
                return;
            }
        }
        //TODO press swap1
        if(tmp.pos != 6){
            x = tmp.num % 10;
            y = (tmp.num / a[tmp.pos + 1] * a[tmp.pos + 1]) % 10;
            t.num = tmp.num - x * a[6] - y * a[tmp.pos] + x * a[tmp.pos] + y * a[6];
            t.step = tmp.step + 1;
            t.pos = tmp.pos;
            if(!book[t.num][t.pos] || (book[t.num][t.pos] != 0 && t.step < book[t.num][t.pos])){
                book[t.num][t.pos] = t.step;
                que.push(t);
            }
            if(t.num == ed){
                ans = t.step;
                return;
            }
        }
        //TODO press up
        if((tmp.num / a[tmp.pos - 1] * a[tmp.pos - 1]) % a[tmp.pos + 1] != 9){
            t = tmp;
            t.num = a[tmp.pos] + tmp.num;
            t.step = tmp.step + 1;
            if(!book[t.num][t.pos] || (book[t.num][t.pos] != 0 && t.step < book[t.num][t.pos])){
                book[t.num][t.pos] = t.step;
                que.push(t);
            }
            if(t.num == ed){
                ans = t.step;
                return;
            }
        }
        //TODO press down
        if((tmp.num / a[tmp.pos - 1] * a[tmp.pos - 1]) % a[tmp.pos + 1] != 0){
            t = tmp;
            t.num = tmp.num - a[tmp.pos];
            t.step = tmp.step + 1;
            if(!book[t.num][t.pos] || (book[t.num][t.pos] != 0 && t.step < book[t.num][t.pos])){
                book[t.num][t.pos] = t.step;
                que.push(t);
            }
            if(t.num == ed){
                ans = t.step;
                return;
            }
        }
        //TODO press left
        if(tmp.pos != 1){
            t = tmp;
            t.pos = tmp.pos - 1;
            t.step = tmp.step + 1;
            if(!book[t.num][t.pos] || (book[t.num][t.pos] != 0 && t.step < book[t.num][t.pos])){
                book[t.num][t.pos] = t.step;
                que.push(t);
            }
        }
        //TODO press right
        if(tmp.pos != 6){
            t = tmp;
            t.step = tmp.step + 1;
            t.pos = tmp.pos + 1;
            if(!book[t.num][t.pos] || (book[t.num][t.pos] != 0 && t.step < book[t.num][t.pos])){
                book[t.num][t.pos] = t.step;
                que.push(t);
            }
        }
    }
}
int main(){
    scanf("%d%d",&st,&ed);
    if(st == ed){
        puts("0");
        return 0;
    }
    memset(book,0x3f,sizeof(book));
    bfs();
    printf("%d\n",ans);
    return 0;
}