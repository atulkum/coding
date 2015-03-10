package problems;

import java.util.ArrayList;
import java.util.List;

//unique key
public class BST {
	private Node root = null;
	public void insert(int val){
		Node parent = null;
		Node current = root;
		while(current != null){
			parent = current;
			if(current.v > val){
				current.rank++;
			}
			current = (current.v > val)? current.l:current.r;
		}
		Node newNode = new Node(val);
		if(root == null){
			parent = newNode;
			root = parent;
		}else{
			if(parent.v > newNode.v){
				parent.l = newNode;
			}else{
				parent.r = newNode;
			}
		}
	}
	public Node search(int val){
		Node current = root;
		while(current != null){
			if(current.v == val){
				return current;
			}
			current = (current.v > val)? current.l:current.r;
		}
		return null;
	}
	public void delete(int val){
		Node parent = null;
		Node current = root;
		while(current != null){
			if(current.v == val){
				break;
			}
			parent = current;
			if(current.v > val){
				current.rank--;
			}
			current = (current.v > val)? current.l:current.r;
		}
		if(current != null){
			if(current.r != null){
				Node currRightLowest = current.r;
				Node currRightLowestP = current;
				while(currRightLowest.l != null){
					currRightLowestP = currRightLowest;
					currRightLowest = currRightLowest.l;
				}
				current.v = currRightLowest.v;
				if(currRightLowest == currRightLowestP.l){
					currRightLowestP.l =  currRightLowest.r;
				}else{
					currRightLowestP.r =  currRightLowest.r;
				}
			}else{
				if(current == root){
					root = current.l;
				}else if(current == parent.l){
					parent.l = current.l;
				}else{
					parent.r = current.l;
				}
			}
		}
	}
	public Node kthsmallest(int k){
		Node current = root;
		while(current != null){
			if(current.rank+1 == k){
				return current;
			}else if(current.rank < k){
				k -= (current.rank+1);
				current = current.r;
			}else{
				current = current.l;
			}
		}
		return null;
	}
	public void printLevelOrder(){
		List<Node> q = new ArrayList<Node>();
		q.add(root);
		int i = 0;
		while(!q.isEmpty()){
			System.out.print("Level " + i + " : " );
			List<Node> newq = new ArrayList<Node>();
			for(Node n:q){
				
				if(n.l != null){
					newq.add(n.l);
				}
				if(n.r != null){
					newq.add(n.r);
				}
				System.out.print(n + " , ");
			}
			i++;
			q = newq;
			System.out.println();
		}
		System.out.println();
	}
	public static void main(String[] args){
		int[] vals = {20, 8, 22, 4, 12, 10, 14};
		BST tree = new BST();
		for(int val:vals){
			tree.insert(val);
		}
		tree.printLevelOrder();
		/*tree.delete(8);
		tree.printLevelOrder();*/
		for(int i = 1; i <= vals.length; ++i){
			System.out.println(tree.kthsmallest(i));
		}
		
	}
}
