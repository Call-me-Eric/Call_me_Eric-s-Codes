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
    ////����½�������O(N2)�㷨 
    int ans = 1;
    for(int i = 2; i <= n; i++){
        for(int j = 1; j < i; j++)
            if(a[j] >= a[i] ) f[i] = max(f[i],f[j]+1);
        ans = max(ans, f[i]);
    }
    /////��Сϵͳ�㷨 
    int k = 1;	l[1] =a[1];	//��ʼ��Ϊ1��ϵͳ�����ص�һ������ 
    for(int i = 2; i <= n;i++){ //ö��ÿ������ 
        int p = 0;
        for(int j = 1; j <= k; j++){ //ö��ÿ��ϵͳ 
            if(a[i] <= l[j]) {		//���Ա�ĳһ��ϵͳ���� 
                if(p == 0) 	p = j;  //ֻ��һ�ף������ǵ�һ�� 
                else if(l[j] < l[p]) p = j; //̰�ģ�������Сϵͳ 
            }
        } 
        if(p == 0) {
            k++; l[k] = a[i];
        }
        else 
            l[p] = a[i]; //������С 
    }
    cout << ans << endl << k << endl;	
    return 0;
}


