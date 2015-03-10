package problems;

public class AVLRankNode {
	int v;
	AVLRankNode l, r;
	int height;
	int size;
	public AVLRankNode(int v){
		this.v = v;
		l=r=null;
		height = 1;
		size = 1;
	}
	@Override
	public String toString() {
		return (v + " : " + " (" + ((l != null)?""+l.v:'#') + " , " + ((r != null)?"" + r.v:'#') + ") size:" + size);
	}
	public int updateDfAndHeight(){
		int lh = (l == null)? 0: l.height;
		int rh = (r == null)? 0: r.height;
		height = Math.max(lh, rh) +1;
		int ls = (l == null)? 0: l.size;
		int rs = (r == null)? 0: r.size;
		size = ls + rs + 1;
		int df = lh - rh;
		return df;
	}
	
	public void copyFileds(AVLRankNode other){
		v = other.v;
		l=other.l;
		r=other.r;
		size = other.size;
		height = other.height;
	}
	
}
