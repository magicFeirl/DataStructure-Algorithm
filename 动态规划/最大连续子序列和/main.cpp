/*
    ����һ�����У������������е�����
    ���� 1 3 -4 5 6 7
    ��������Ϊ 5 6 7 ʱ�����
    
    �ܼ򵥵�һά dp��״̬����Ϊ
    dp[i] = max(dp[i-1] + arr[i], arr[i]);
    ���ͣ�
    dp[i] ��ʾ�� i ��������������кͣ�����ͺ͵� i-1 �����й�
    ȡ dp[i-1] + arr[i] �� arr[i] �нϴ�����Ϊ dp[i] ��ֵ
*/
#include <iostream>

using namespace std;

int main(){
    int arr[] = {1, 3, -4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    int dp[size];
    
    dp[0] = arr[0];
    
    int ans = dp[0];
    for(int i=1; i<size; i++){
        dp[i] = max(dp[i-1] + arr[i], arr[i]);
        ans = max(ans, dp[i]);
    }
    
    cout << ans << endl;
    
    return 0;
}
