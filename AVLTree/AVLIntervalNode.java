package problems;

public class AVLIntervalNode {
	AVLIntervalNode l, r;
	int height;
	int upper;
	int lower;
	int max;
	public AVLIntervalNode(int upper, int lower){
		this.upper = upper;
		this.lower = lower;
		this.max = upper;
		l=r=null;
		height = 1;
	}
	@Override
	public String toString() {
		return ("[" + lower + ":" +upper+"]: (" 
				+ ((l != null)?""+l.lower:'#') + " , " 
				+ ((r != null)?"" + r.lower:'#') + ")");
	}
	public int updateDfAndHeight(){
		int lh = (l == null)? 0: l.height;
		int rh = (r == null)? 0: r.height;
		height = Math.max(lh, rh) +1;
		int df = lh - rh;
		return df;
	}
	
	public void copyFileds(AVLIntervalNode other){
		upper = other.upper;
		lower = other.lower;
		max = other.upper;
		l=other.l;
		r=other.r;
		height = other.height;
	}
	
}
