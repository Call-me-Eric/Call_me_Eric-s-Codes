#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1300;
struct block{
    vector<int> vec;
    int id, col;
    block(int col = 0,int id = 0):col(col),id(id){}
    void ins(int x){this->vec.push_back(x);}
}b[maxn];
int tot, n, fa[maxn];
int ind[maxn];
stack<block> stk;
bool book[maxn];
stack<int> que,que1,que2;
signed main(){
    n = read() * 3;
    for(int i = 1;i <= n;i++){book[read()] = 1;}n *= 2;
    for(int i = 1;i <= n;i++){
        if(stk.empty() || stk.top().col != book[i]){
            stk.push(block(book[i],++tot));
            stk.top().ins(i);b[tot] = stk.top();
        }
        else{
            stk.top().ins(i);b[stk.top().id].ins(i);
            if(stk.top().vec.size() >= 3){
                block tmp = stk.top();stk.pop();
                if(stk.empty())continue;
                fa[tmp.id] = stk.top().id;
                ind[stk.top().id]++;
            }
        }
    }
    for(int i = 1;i <= tot;i++){
        if(!ind[b[i].id]){
            if(b[i].col == 1){que.push(b[i].id);}
            else{
                if(!fa[b[i].id])que2.push(b[i].id);
                else que1.push(b[i].id);
            }
        }
    }
    int now = 1,cnt = 0;n /= 3;
    while(cnt < n){
        block tmp = block();
        if(now){tmp = b[que.top()];que.pop();}
        else{
            if(!que1.empty()){tmp = b[que1.top()];que1.pop();}
            else {tmp = b[que2.top()];que2.pop();}
        }
        for(int i : tmp.vec){printf("%d ",i);}puts("");
        ind[fa[tmp.id]]--;
        if(!ind[fa[tmp.id]]){
            if(b[fa[tmp.id]].col == 1){que.push(b[fa[tmp.id]].id);}
            else{
                if(!fa[b[fa[tmp.id]].id]){que2.push(b[fa[tmp.id]].id);}
                else que1.push(b[fa[tmp.id]].id);
            }
        }
        now ^= 1;cnt++;
    }
    return 0;
}