/*
01�������ӣ����ʼǡ��Ǹ�ò���е�����

70 3
71 100
69 1
1 2
*/

#include <iostream>

using namespace std;


int w[110], c[110];

int dp[110][1010];

int main(){
    int V, N;

    cin >> V >> N;

    for(int i=1; i<=N; i++){
        cin >> w[i] >> c[i];
    }

    for(int i=1; i<=N; i++){
        // ���ű���
        for(int v=V; v>=0; v--){
            // ���пռ��ʱ��
            if(v >= w[i]){
                // ���ż�Ϊ
                // ǰһ����Ʒ��ǰ�ռ� �� ǰһ����Ʒ�������Ʒ����ϵ�ǰ��Ʒ�ļ�ֵ�нϴ���
                dp[i][v] = max(dp[i-1][v], dp[i-1][v-w[i]] + c[i]);
            }else{
                // û�пռ�Ļ����Ž����ǰһ����Ʒ����Ϊ v �����Ž�
                dp[i][v] = dp[i-1][v];
            }
        }
    }

    cout << dp[N][V] << endl;

    return 0;
}
