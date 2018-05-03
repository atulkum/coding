#include<vector>
#include <iostream>
using namespace std;

int burstBaloon(vector<int>& a){
	int n = a.size();
	vector<vector<int>> dp(n, vector<int>(n, 0));
	
	for(int i = 1; i <= n; ++i){
		for(int s = 0; s+i-1 < n; ++s){
			int e = s + i - 1;
			//which baloon to burst last among s to e
			for(int k = s; k <= e; k++){
				int m = 0;
				int mul = a[k];
				if(k > 0){
					m += dp[s][k-1];
				}
				if(k + 1 < n){
					m += dp[k+1][e];
				}
				if(s > 0){
					mul *= a[s-1];
				}
				if(e+1 < n){
					mul *= a[e+1];
				}
				dp[s][e] = max(dp[s][e], m+mul);  
			} 
		}
	}
	/*
	cout << "=========" << endl; 	
	for(int s = 0; s < n; ++s){
		for(int e = 0; e < n; ++e){
			cout << dp[s][e] << " ";
		}
		cout << endl;
	}
	cout << "=========" << endl; 	
	*/
	return dp[0][n-1];
}

int main(){
	vector<int> m = {3,1,5,8};
	cout << burstBaloon(m) << endl;
}


