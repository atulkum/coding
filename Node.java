package problems;

public class Node {
	int v;
	Node l, r;
	int rank =0;
	public Node(int v){
		this.v = v;
		l=r=null;
	}
	@Override
	public String toString() {
		return (v + " : " + rank + " (" + ((l != null)?""+l.v:'#') + " , " + ((r != null)?"" + r.v:'#') + ")");
	}
}
