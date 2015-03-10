package problems;

import java.util.ArrayList;
import java.util.List;

public class AVL {
	public static AVLNode insert(AVLNode subtreeRoot, int val){
		if(subtreeRoot == null){
			return new AVLNode(val);
		}
		if(val < subtreeRoot.v){
			subtreeRoot.l = insert(subtreeRoot.l, val);
		}else{
			subtreeRoot.r = insert(subtreeRoot.r, val);
		}
		//fix balancing 
		int newDf = subtreeRoot.updateDfAndHeight();
		
		// tree becomes left heavy 
	    if (newDf > 1){
	    	if(val > subtreeRoot.l.v){
	    		//key inserted in right subtree of left child
	    		//this will fix the left subtree
	    		subtreeRoot.l =  leftRotate(subtreeRoot.l);
	    	}else{
	    		//key inserted in left subtree of left child
	    	}
	    	//this will fix the left heavy part
	    	return rightRotate(subtreeRoot);
	    }
	    // tree becomes right heavy 
	    if (newDf < -1){
	    	if(val < subtreeRoot.r.v){
	    		//key inserted in left subtree of right child
	    		//this will fix the right subtree
	    		subtreeRoot.r =  rightRotate(subtreeRoot.r);
	    	}else{
	    		//key inserted in right subtree of right child
	    	}
	    	//this will fix the right heavy part
	    	return leftRotate(subtreeRoot);
	    }
	    return subtreeRoot;
	}
	public static AVLNode delete(AVLNode subtreeRoot, int val){
		if(subtreeRoot == null){
			return subtreeRoot;
		}
		if(val < subtreeRoot.v){
			subtreeRoot.l = delete(subtreeRoot.l, val);
		}else if(val > subtreeRoot.v){
			subtreeRoot.r = delete(subtreeRoot.r, val);
		}else{
			//this is the key to delete
			//case 1: child < 2
			if(subtreeRoot.l == null || subtreeRoot.r  != null){
				AVLNode nonNullChild = (subtreeRoot.l != null)?subtreeRoot.l:subtreeRoot.r;
				if(nonNullChild != null){
					subtreeRoot.copyFileds(nonNullChild);
				}else{
					subtreeRoot = null;
				}
			}else{
			//case 2: child == 2
				//get inorder successor
				AVLNode inSuccessor = subtreeRoot.r;
				while(inSuccessor.l != null){
					inSuccessor = inSuccessor.l;
				}
				subtreeRoot.v = inSuccessor.v;
				subtreeRoot.r = delete(subtreeRoot.r, inSuccessor.v);
			}
		}
		
		if(subtreeRoot == null){
			return subtreeRoot;
		}
		//fix balancing 
		int newDf = subtreeRoot.updateDfAndHeight();
		// tree becomes left heavy 
	    if (newDf > 1){
	    	int lDf = subtreeRoot.l.updateDfAndHeight();
	    	if(lDf < 0){
	    		//left subtree is right heavy
	    		subtreeRoot.l =  leftRotate(subtreeRoot.l);
	    	}else{
	    		//left subtree is left heavy
	    	}
	    	//this will fix the left heavy part
	    	return rightRotate(subtreeRoot);
	    }
	    // tree becomes right heavy 
	    if (newDf < -1){
	    	int rDf = subtreeRoot.r.updateDfAndHeight();
	    	if(rDf > 0){
	    		//right subtree is left heavy
	    		subtreeRoot.r =  rightRotate(subtreeRoot.r);
	    	}else{
	    		//right subtree is right heavy
	    	}
	    	//this will fix the right heavy part
	    	return leftRotate(subtreeRoot);
	    }
	    return subtreeRoot;
	}
	public static AVLNode rightRotate(AVLNode subtreeRoot){
		AVLNode newRoot = subtreeRoot.l;
		subtreeRoot.l = newRoot.r;
		newRoot.r = subtreeRoot;
		subtreeRoot.updateDfAndHeight();
		newRoot.updateDfAndHeight();
		return newRoot;
	}
	public static AVLNode leftRotate(AVLNode subtreeRoot){
		AVLNode newRoot = subtreeRoot.r;
		subtreeRoot.r = newRoot.l;
		newRoot.l = subtreeRoot;
		subtreeRoot.updateDfAndHeight();
		newRoot.updateDfAndHeight();
		return newRoot;
	}
	
	public static void printLevelOrder(AVLNode root){
		List<AVLNode> q = new ArrayList<AVLNode>();
		q.add(root);
		int i = 0;
		while(!q.isEmpty()){
			System.out.print("Level " + i + " : " );
			List<AVLNode> newq = new ArrayList<AVLNode>();
			for(AVLNode n:q){
				
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
		AVLNode root = null;
		/*root = insert(root, 10);
		root = insert(root, 20);
		root = insert(root, 30);
		root = insert(root, 40);
		root = insert(root, 50);
		root = insert(root, 25);*/
		root = insert(root, 9);
	    root = insert(root, 5);
	    root = insert(root, 10);
	    root = insert(root, 0);
	    root = insert(root, 6);
	    root = insert(root, 11);
	    root = insert(root, -1);
	    root = insert(root, 1);
	    root = insert(root, 2);
		printLevelOrder(root);
		root = delete(root, 10);
		printLevelOrder(root);
	}
}

            
            
            
            



