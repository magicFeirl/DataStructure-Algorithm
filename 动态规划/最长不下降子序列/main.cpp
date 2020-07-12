/*
    给定一个序列，求其中最长的不下降子序列的长度（子序列可以不连续）
    如 A[] = {1, 2, 3, -1, -2, 7, 9}，其最长不下降子序列为 {1, 2, 3, 7, 9}，长度为5
*/

#include <iostream>

using namespace std;

int main(){
    int A[] = {1, 2, 3, 4, -5, -1}, size = sizeof(A) / sizeof(A[0]);
    int dp[size];
    
    dp[0] = 1;
    
    int ans = -1;
    for(int i=0; i<size; i++){
        dp[i] = 1;
        for(int j=0; j<i; j++){
            if(A[j] <= A[i]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        
        ans = max(ans, dp[i]);
    }
    
    cout << ans << endl;
    
    return 0;
}
