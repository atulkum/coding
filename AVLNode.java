package problems;

public class AVLNode {
	int v;
	AVLNode l, r;
	int height;
	public AVLNode(int v){
		this.v = v;
		l=r=null;
		height = 1;
	}
	@Override
	public String toString() {
		return (v + " : " + height + " (" + ((l != null)?""+l.v:'#') + " , " + ((r != null)?"" + r.v:'#') + ")");
	}
	public int updateDfAndHeight(){
		int lh = (l == null)? 0: l.height;
		int rh = (r == null)? 0: r.height;
		height = Math.max(lh, rh) +1;
		int df = lh - rh;
		return df;
	}
	
	public void copyFileds(AVLNode other){
		v = other.v;
		l=other.l;
		r=other.r;
		height = other.height;
	}
	
}
