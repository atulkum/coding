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
		arr[i] = v;
		_update(0, n-1, i, v, 0);
	}
	int getMin(int s, int e){
		return _min(0, n-1, s, e, 0);
	}
	private:
	
	int size, n;
	vector<int> tree;
	vector<int> arr;
	
	int _min(int s, int e, int qs, int qe, int curr){
		if(qs <= s && e <= qe){
			return tree[curr];
		}
		if(qs > e || qe  < s){
			return INT_MAX;	
		}
		int mid = s + (e-s)/2;
		return min(_min(s, mid, qs, qe, curr*2 +1), _min(mid+1,e,qs,qe, curr*2 +2));
	}
	int _update(int s, int e, int i, int v, int curr){
		if(i < s || i > e){
			return INT_MAX;	
		}
		if(s == e){
			tree[curr] = v;
		}else{
			int mid = s + (e-s)/2;
			tree[curr] = min(_update(s, mid, i, v, curr*2 +1),
			_update(mid+1,e,i, v, curr*2 +2));
		}
		return tree[curr];
	}
	int construct(int s, int e, int curr){
		if(s == e){
			tree[curr] = arr[s];
		}else{
			int mid = s + (e-s)/2;
			tree[curr] = min(construct(s, mid, curr*2 +1), construct(mid+1,e, curr*2 +2));
		}
		return tree[curr];
	}
};

int main(){
	int arr[] = {1, 3, 2, 7, 9, 11};
	vector<int> a(&arr[0], &arr[0] + 6);
	SegmentTree st(a);
	cout << " min " << st.getMin(1,5) << endl; 
	st.update(2, 8);
	cout << " min " << st.getMin(1,5) << endl; 
	return 0;
}
