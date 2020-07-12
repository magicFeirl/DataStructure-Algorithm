#include <iostream>

using namespace std;

const int MAXN = 1e5;
int prime[MAXN];

void init_prime(){
	// 默认所有数都是素数
    for(int i=2; i<MAXN; i++){
        prime[i] = 1;
    }

    for(int i=2; i*i<MAXN; i++){
    	// 判断是否为素数 & 防止溢出
        if(prime[i] && i*i < MAXN){
			// 如果该数是素数，那么它的所有倍数都不是素数
            for(int j=i; i*j<MAXN; j++){
                prime[i*j] = 0;
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
