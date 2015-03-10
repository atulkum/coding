package problems;

public class BIT {
	public int[] tree;
	public int size;
	public BIT(int n){
		size = 1;
		while(n > size){
			size *= 2;
		}
		tree = new int[size];
	}
	int cumulativeSum(int idx){
		int sum = 0;
		while (idx > 0){
			sum += tree[idx];
			idx -= (idx & -idx);
		}
		return sum;
	}
	void update(int idx ,int val){
		while (idx < size){
			tree[idx] += val;
			idx += (idx & -idx);
		}
	}
}
