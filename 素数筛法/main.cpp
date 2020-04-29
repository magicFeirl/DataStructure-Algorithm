#include <iostream>

using namespace std;

const int MAXN = 1e5;
int prime[MAXN];

void init_prime(){
    for(int i=2; i<MAXN; i++){
        prime[i] = 1;
    }

    for(int i=2; i*i<MAXN; i++){
        if(prime[i]){
            // 防止溢出
            if(i*i < MAXN){
                for(int j=i; i*j<MAXN; j++){
                    prime[i*j] = 0;
                }
            }
        }
    }
}

int main(){
    init_prime();
    
    while(true){
        int k;
        cin >> k;
        
        cout << prime[k] << endl;
    }
    
    return 0;
}