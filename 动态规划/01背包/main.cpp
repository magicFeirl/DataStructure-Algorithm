/*
    01����
*/
#include <iostream>

using namespace std;

/**
��������:
5 8
3 5 1 2 2
4 5 2 1 3

���������
10
*/

int main(){
    int N, V;
    
    cin >> N >> V;
    
    int w[N+1], c[N+1], dp[N+1][V+1];
    
    // ��ʼ������
    
    for(int i=1; i<=N; i++){
        cin >> w[i];
    }
    
    for(int i=1; i<=N; i++){
        cin >> c[i];
    }
    
    for(int i=0; i<=N; i++){
        fill(dp[i], dp[i]+V+1, 0);
    }
    
    // dp ����
    for(int i=1; i<=N; i++){
        for(int v=w[i]; v<=V; v++){
            dp[i][v] = max(dp[i-1][v], dp[i-1][v-w[i]] + c[i]);
        }
    }
    
    // �����һ����Ʒ������������������ȡ����ֵ
    int ans = -1;
    for(int i=1; i<=V; i++){
        ans = max(ans, dp[N][i]);
    }
    
    cout << ans << endl;
    
    return 0;
}
