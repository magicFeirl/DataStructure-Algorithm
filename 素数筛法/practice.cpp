#include <stdio.h>

const int N = 1e5;
int prime_array[N];

void init_prime(){
	for(int i=2; i<N; i++){
		prime_array[i] = 1;
	}
	
	for(int i=2; i*i<N; i++){
		if(prime_array[i] && i*i < N){
			for(int j=i; i*j<N; j++){
				prime_array[i*j] = 0;
			}
		}
	}
}

int main(){
	int k;
	
	init_prime();
	
	while(true){
		scanf("%d", &k);
		if(k < N){
			printf("%d %s a prime\n",
			k, prime_array[k] ? "is" : "isn't");
		}
	}
	
	return 0;
}
