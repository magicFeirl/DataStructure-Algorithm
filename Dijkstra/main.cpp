/**
裸 dijkstra 版子
2021年2月2日14:20:40
代码基本还记得，但是有点小问题
*/

#include <iostream>
#include <cstring>

using namespace std;

const int N = 510;
int G[N][N], dist[N], vis[N];

int n, m;

int dijkstra(int s, int d){
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;

    for(int i=0; i<n; i++){
        int t = -1;
        for(int j=0; j<n; j++){
            if(!vis[j] && (t == -1 || dist[t] > dist[j])){
                t = j;
            }
        }

        if(t == -1){
            return 0;
        }
        
        vis[t] = 1;

        for(int j=0; j<n; j++){
            if(dist[j] > dist[t] + G[t][j]){
                dist[j] = dist[t] + G[t][j];
            }
        }
    }

    for(int i=0; i<n; i++){
        cout << dist[i] << " ";
    }

    return dist[d];
}

int main(){
    memset(G, 0x3f, sizeof(G));
    int s, d = 0;
    cin >> n >> m >> s;
    
    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        G[a][b] = G[b][a] = c;
    }
    
    dijkstra(s, d);
    
    return 0;
}

/**
6 8 0
0 1 1
0 3 4
0 4 4
1 3 2
2 5 1
3 2 2
3 4 3
4 5 3

0 1 5 3 4 7
*/
