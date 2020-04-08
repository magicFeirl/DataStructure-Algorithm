#include <iostream>
#include <algorithm>

using namespace std;

int n;
const int N = 1e6;
int a[N], s[N];


int main(){
	int i, j, res = 0;
	cin >> n;
	
	for(i=0; i<n; i++){
		cin >> a[i];
	}

	for(i=0, j=0; i<n; i++){
		s[a[i]]++;
		
		while(s[a[i]] > 1){
			s[a[j++]]--;
		}
		
		res = max(res, i - j + 1);
	}
	
	cout << res << endl ;
	
	return 0;
}
