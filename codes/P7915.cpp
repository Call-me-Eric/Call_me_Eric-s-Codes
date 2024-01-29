#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
const int maxn = 1e6 + 100;
int T;
int n;
int a[maxn];
char ans[maxn];
int s[maxn];
int first[maxn],second[maxn];
int tp, pt;
bool check(int x,int l,int r,int y){//[x,y] as a ;[l,r] as b
    if(x == l && r == y)return 1;//finished
    if(x > l || r > y)return 0;//no solution
    if(a[x] == a[l - 1] && check(x + 1,l - 1,r,y)){
        ans[++tp] = 'L';
        return 1;
    }
    if(a[x] == a[r + 1] && check(x + 1,l,r + 1,y)){
        ans[++tp] = 'L';
        return 1;
    }
    if(a[y] == a[l - 1] && check(x,l - 1,r,y - 1)){
        ans[++tp] = 'R';
        return 1;
    }
    if(a[y] == a[r + 1] && check(x,l,r + 1,y - 1)){
        ans[++tp] = 'R';
        return 1;
    }
    return 0;
}
int main(){
    scanf("%d",&T);
    while(T--){
        pt = tp = 0;
        scanf("%d",&n);
        n *= 2;
        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
            if(first[a[i]] == 0)first[a[i]] = i;
            else second[a[i]] = i;
        }
        if(check(2,second[a[1]],second[a[1]],n)){//first as L
            ans[++tp] = 'L';
            int x = 1,y = n;
            while(tp){
                if(ans[tp] == 'L') s[++pt] = a[x++];
                else s[++pt] = a[y--];
                putchar(ans[tp--]);
            }
            while(pt){
                if(a[x] == s[pt]){
                    putchar('L');
                    x++;
                }
                else{
                    putchar('R');
                    y--;
                }
                --pt;
            }
        }
        else if(check(1,first[a[n]],first[a[n]],n - 1)){//first as R
            ans[++tp] = 'R';
            int x = 1,y = n;
            while(tp){
                if(ans[tp] == 'L') s[++pt] = a[x++];
                else s[++pt] = a[y--];
                putchar(ans[tp--]);
            }
            while(pt){
                if(a[x] == s[pt]){
                    putchar('L');
                    x++;
                }
                else{
                    putchar('R');
                    y--;
                }
                --pt;
            }
            
        }

        else printf("-1");//no solution
        putchar('\n');
        for(int i = 1;i <= n;i++){
            first[i] = second[i] = 0;
        }
    }
    return 0;
}
/*
2
5
4 1 2 4 5 3 1 2 3 5
3
3 2 1 2 1 3

*/
