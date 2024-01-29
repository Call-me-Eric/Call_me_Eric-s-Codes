#include <iostream>
#include <cstdio>
using namespace std;
int a[100001],f[100001],l[100001];
int main(){
    int n = 1;
    while(scanf("%d",&a[n])!=EOF){
        f[n] = 1;	
        n++;
    }
    n--; 
    ////最长不下降子序列O(N2)算法 
    int ans = 1;
    for(int i = 2; i <= n; i++){
        for(int j = 1; j < i; j++)
            if(a[j] >= a[i] ) f[i] = max(f[i],f[j]+1);
        ans = max(ans, f[i]);
    }
    /////最小系统算法 
    int k = 1;	l[1] =a[1];	//初始化为1套系统，拦截第一个导弹 
    for(int i = 2; i <= n;i++){ //枚举每个导弹 
        int p = 0;
        for(int j = 1; j <= k; j++){ //枚举每套系统 
            if(a[i] <= l[j]) {		//可以被某一套系统拦截 
                if(p == 0) 	p = j;  //只有一套，或者是第一套 
                else if(l[j] < l[p]) p = j; //贪心，更新最小系统 
            }
        } 
        if(p == 0) {
            k++; l[k] = a[i];
        }
        else 
            l[p] = a[i]; //拦截最小 
    }
    cout << ans << endl << k << endl;	
    return 0;
}


