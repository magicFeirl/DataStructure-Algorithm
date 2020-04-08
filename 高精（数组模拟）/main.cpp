#include <iostream>
#include <vector>


using namespace std;

string add(string& a, string& b){
	int i;
	vector<int> r, A, B;
	string result = "";

	for(i=a.size()-1; i>=0; A.push_back(a[i] - '0'), i--);
	for(i=b.size()-1; i>=0; B.push_back(b[i] - '0'), i--);
	
	int t = 0;
	
	for(int i=0; i<A.size() || i<B.size(); i++){
		if(i < A.size()) t += A[i];
		if(i < B.size()) t += B[i];
		
		r.push_back(t%10);
		t /= 10;
	}
	
	if(t) r.push_back(1);
	
	for(i=r.size()-1; i>=0; i--){
		result += char(r[i] + '0');
	}
	
	return result;
}

string sub(string& a, string& b){
	int i;
	string prefix = "", result = "";
	vector<int> temp, A, B;
	
	if(a < b){
		string t = a;
		a = b;
		b = t;
		prefix = "-";
	}
	
	for(i=a.size()-1; i>=0; A.push_back(a[i] - '0'), i--);
	for(i=b.size()-1; i>=0; B.push_back(b[i] - '0'), i--);
	
	for(i=0; i<A.size(); i++){
		if(A[i] - B[i] < 0){
			A[i+1] -= 10;
			A[i] += 10;
		}
		
		temp.push_back(A[i] - B[i] + '0');
	}
	
	for(i=0; i<temp.size(); i++){
		result = result + char(temp[i]);
	}
	
	return prefix + result;
}

int main(){
	int i;
	string a, b;
	
	while(true){
		cin >> a >> b;

		cout << add(a, b) << endl;
		cout << sub(a, b) << endl;
	}
	
	return 0;
}
