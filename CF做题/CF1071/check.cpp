#include<bits/stdc++.h>
using namespace std;

pair<pair<int,int>,pair<int,int> > ans[1 << 12];
bool book[114514] = {0};

int getid(){
    int ans = 0;
    for(int i = 1;i <= 6;i++){
        ans = (ans << 1) + book[i];
    }
    return ans;
}

void solve(){
    for(int i = 2;i <= 10;i++){
        for(int r = 1;i - r >= 1 && i + r <= 11;r++){
            book[i] ^= 1;book[i - r] ^= 1;book[i + r] ^= 1;
            ans[getid()] = make_pair(make_pair(i,r),make_pair(-1,-1));
            for(int j = 2;j <= 10;j++){
                for(int l = 1;j - l >= 1 && j + l <= 11;l++){
                    book[j] ^= 1;book[j - l] ^= 1;book[j + l] ^= 1;
                    ans[getid()] = make_pair(make_pair(i,r),make_pair(j,l));
                    book[j] ^= 1;book[j - l] ^= 1;book[j + l] ^= 1;
                }
            }
            book[i] ^= 1;book[i - r] ^= 1;book[i + r] ^= 1;
        }
    }
    for(int i = 0;i < (1 << 6);i++){
        int x1, x2, x3, x4, x5, x6;
        int pos1, r1, pos2, r2;
        pos1 = ans[i].first.first;
        r1 = ans[i].first.second;
        pos2 = ans[i].second.first;
        r2 = ans[i].second.second;
        x1 = pos1 - r1;x2 = pos1;x3 = pos1 + r1;
        x4 = pos2 - r2;x5 = pos2;x6 = pos2 + r2;
        printf("{%d,%d,%d,%d,%d,%d},\n",x1,x2,x3,x4,x5,x6);
    }
}

pair<int,int> res[1 << 8][20];
bool flag = false;
bool chose[20];

int pr[20][2] = {
{2,1},
{3,1},
{3,2},
{4,1},
{4,2},
{4,3},
{5,1},
{5,2},
{5,3},
{6,1},
{6,2},
{7,1}
};

void dfs(int step,int sta,int nsta){
    if(flag)return;
    if(nsta == sta){
        int cnt = 0;
        for(int i = 0;i < 12;i++){
            if(chose[i]){
                res[sta][cnt++] = make_pair(pr[i][0],pr[i][1]);
            }
        }
        flag = true;
        return;
    }
    if(step == -1){return;}
    chose[step] = 1;
    int x1 = pr[step][0] - pr[step][1],x2 = pr[step][0],x3 = pr[step][0] + pr[step][1];
    x1 = 8 - x1;x2 = 8 - x2;x3 = 8 - x3;
    nsta ^= (1 << x1);nsta ^= (1 << x2);nsta ^= (1 << x3);
    dfs(step - 1,sta,nsta);
    nsta ^= (1 << x1);nsta ^= (1 << x2);nsta ^= (1 << x3);
    chose[step] = 0;dfs(step - 1,sta,nsta);
}

void solve1(){
    for(int i = 0;i < (1 << 8);i++){
        flag = false;dfs(11,i,0);
        // printf("flag = %d\n",flag);
        putchar('{');
        for(int j = 0;j < 12;j++){
            int pos = res[i][j].first, r = res[i][j].second;
            printf("{%d,%d,%d}%c",pos - r,pos,pos + r,",}"[j == 11]);
        }
        puts(",");
    }
}

inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
void check(){
    scanf("%*s");
    int n = read();
    for(int i = 1;i <= n;i++){
        book[read()] ^=  1;book[read()] ^= 1;book[read()] ^= 1;
    }
    printf("%d\n",100000);
    for(int i = 1;i <= 100000;i++)printf("%d ",book[i]);
    puts("");
}
void datamaker(){
    int n = 1e5;srand(time(0));int srd = rand();
    printf("%d\n",n);
    for(int i = 1;i <= n;i++){
        srd = srd + rand() % n;
        putchar((srd & 1) ? '1' : '0');
        putchar(' ');
    }
    puts("");
}

signed main(){
    // solve1();
    // datamaker();
    check();
    return 0;
}