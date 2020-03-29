#include <iostream>

const int N = 10;
int arr[N] = {1, -1, 5, 6, 3}, temp[N];

void merge_sort(int q[], int l, int r){
	if(l >= r) return ;
	
	int mid = (l + r) / 2;
	merge_sort(q, l, mid);
	merge_sort(q, mid+1, r);
	
	int i = l, j = mid + 1, cur = 0;
	while(i <= mid && j <= r){
		if(q[i] <= q[j]){
			temp[cur++] = q[i++];
		}else{
			temp[cur++] = q[j++];
		}
	}
	
	while(i <= mid) temp[cur++] = q[i++];
	while(j <= r) temp[cur++] = q[j++];
	
	for(int i=l, j=0; i<=r; j++, i++) q[i] = temp[j];
}

void prt_array(int arr[], int size){
	for(int i=0; i<size; i++){
		printf("%d ", arr[i]);
	}
	
	printf("\n");
}

int main(){
	int n;
			
	merge_sort(arr, 0, N-1);
	prt_array(temp, N);

	return 0;
}
