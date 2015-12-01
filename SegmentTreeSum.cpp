#include <iostream>
#include <cmath>
#include<vector>

using namespace std;

class SegmentTree{
	public:
	SegmentTree(vector<int> _arr):arr(_arr){
		n = _arr.size();
		double ht = ceil(log2(n));
		size = 2*pow(2,ceil(log2(n))) - 1; 
		vector<int> _tree(size, 0);
		tree = _tree;
		construct(0, n-1, 0);	
	}	
	
	void update(int i, int v){
		int diff = v - arr[i];
		_update(0, n-1, i, diff, 0);
	}
	int getSum(int s, int e){
		return _sum(0, n-1, s, e, 0);
	}
	private:
	
	int size, n;
	vector<int> tree;
	vector<int> arr;
	
	int _sum(int s, int e, int qs, int qe, int curr){
		if(qs <= s && e <= qe){
			return tree[curr];
		}
		if(qs > e || qe  < s){
			return 0;	
		}
		int mid = s + (e-s)/2;
		return _sum(s, mid, qs, qe, curr*2 +1)
		+ _sum(mid+1,e,qs,qe, curr*2 +2);
	}
	void _update(int s, int e, int i, int diff, int curr){
		if(i < s || i > e){
			return;	
		}
		tree[curr] += diff;
		if(s != e){
			int mid = s + (e-s)/2;
			_update(s, mid, i, diff, curr*2 +1);
			_update(mid+1,e,i, diff, curr*2 +2);
		}
	}
	int construct(int s, int e, int curr){
		if(s == e){
			tree[curr] = arr[s];
		}else{
			int mid = s + (e-s)/2;
			tree[curr] = construct(s, mid, curr*2 +1)
			+ construct(mid+1,e, curr*2 +2);
		}
		return tree[curr];
	}
};

int main(){
	int arr[] = {1, 3, 5, 7, 9, 11};
	vector<int> a(&arr[0], &arr[0] + 6);
	SegmentTree st(a);
	cout << " sum " << st.getSum(1,3) << endl;
	st.update(1, 10);
	cout << " sum " << st.getSum(1,3) << endl;
	
	return 0;
}
