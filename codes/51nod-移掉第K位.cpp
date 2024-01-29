#include<bits/stdc++.h>
using namespace std;
int n;
bool book[10020];
string num;
int k;
int main(){
    cin >> n;
    getchar();
    cin >> num;
    cin >> k;
    for(int i = 1,j = k;i < n && j > 0;i++){
        if(num[i] < num[i - 1]){
            num.erase(i - 1,1);
            i--;
            n--;
            j--;
        }
    }
    cout << num << endl;
    return 0;
}