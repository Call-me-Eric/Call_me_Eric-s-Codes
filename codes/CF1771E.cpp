#include<bits/stdc++.h>
using namespace std;
const int maxn = 400 + 10;
int n, m;char ch[maxn][maxn];
int up[maxn][maxn][2], down[maxn][maxn][2];

signed main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){scanf("%s",ch[i] + 1);}
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            bool passed = 0, stop = 0;
            up[i][j][0] = up[i][j][1] = down[i][j][0] = down[i][j][1] = 0;
            for(int k = i - 1;k && !stop;k--){
                switch(ch[k][j]){
                    case '.':
                        if(!passed)up[i][j][0]++;
                        up[i][j][1]++;
                    break;
                    case '#':
                        stop = 1;
                    break;
                    case 'm':
                        if(passed){stop = 1;break;}
                        passed = 1; up[i][j][1]++;
                    break;
                    default:break;
                }
            }
            passed = 0;stop = 0;
            for(int k = i + 1;k <= n && !stop;k++){
                switch(ch[k][j]){
                    case '.':
                        if(!passed)down[i][j][0]++;
                        down[i][j][1]++;
                    break;
                    case '#':
                        stop = 1;
                    break;
                    case 'm':
                        if(passed){stop = 1;break;}
                        passed = 1; down[i][j][1]++;
                    break;
                    default:break;
                }
            }
            if(!up[i][j][0])up[i][j][0] = -114514;
            if(!up[i][j][1])up[i][j][1] = -114514;
            if(!down[i][j][0])down[i][j][0] = -114514;
            if(!down[i][j][1])down[i][j][1] = -114514;
        }
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 3;j <= m;j++){
            bool passed = (ch[i][j] == 'm');
            if(ch[i][j] == '#' || ch[i][j - 1] == '#')continue;
            if((ch[i][j - 1] == 'm')){if(passed)continue;passed = 1;}
            for(int k = j - 2;k;k--){
                if(ch[i][k] == '#')break;
                if(ch[i][k] == 'm'){if(passed)break;passed = 1;}

                int up1 = min(up[i][k][0],up[i][j][0]);
                int down1 = min(down[i][k][0],down[i][j][0]);
                if(!passed){
                    int up2 = max(min(up[i][k][0],up[i][j][1]),min(up[i][k][1],up[i][j][0]));
                    int down2 = max(min(down[i][k][0],down[i][j][1]),min(down[i][k][1],down[i][j][0]));
                    ans = max(ans,j - k + 1 + 2 * max(up1 + down2,up2 + down1));
                }
                ans = max(ans,j - k + 1 + 2 * (up1 + down1));

            }
        }
    }
    printf("%d\n",ans);
    return 0;
}