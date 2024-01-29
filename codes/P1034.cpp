#include<bits/stdc++.h>
using namespace std;
int ans = INT_MAX >> 2;//提前预定大一点防止面积过大导致出错
struct mtrx{
    int left,up,right,down;// up/down:上/下(y) left/right:左/右(x) eg:左下(left,down)
    bool used;
    bool inmtrx(int x,int y){
        return x <= right && x >= left && y <= up && y >= down;
    }
    int S(){
        return (right - left) * (up - down);
    }
    bool intersect(mtrx a){
        if(!a.used || !used)return 0;
        return inmtrx(a.left,a.down)
        || inmtrx(a.right,a.down) || inmtrx(a.left,a.up) || inmtrx(a.right,a.up);
    }
    void add(int x,int y){
        if(!used){
            left = right = x;
            up = down = y;
            used = 1;
        }
        else{
            if(y > up)up = y;
            else if(y < down)down = y;
            if(x > right)right = x;
            else if(x < left)left = x;
        }
    }
    void print(){
        printf("\
left: down:(%d,%d)\
      up  :(%d,%d)\
right:down:(%d,%d)\
      up  :(%d,%d)\n",left,down,left,up,right,down,right,up);
    }
}mtr[5];
int n,k;
int x[100],y[100];
bool check(){
    for(int i = 1;i <= n;i++){//n <= 4请放心食用
        for(int j = i + 1;j <= n;j++){
            if(mtr[i].intersect(mtr[j])) return 0;
        }
    }
    return 1;
}
void dfs(int step,int area){
    if(area >= ans)return;
    if(step == n + 1){
        if(check()){
            if(ans > area){
                ans = area;
            }
        }
    }
    mtrx tmp;
    for(int i = 1;i <= k;i++){
        tmp = mtr[i];
        mtr[i].add(x[step],y[step]);
        dfs(step + 1,area - tmp.S() + mtr[i].S());
        mtr[i] = tmp;
    }
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i = 1;i <= n;i++){
        scanf("%d%d",&x[i],&y[i]);
    }
    dfs(1,0);
    printf("%d",ans);
    return 0;
}