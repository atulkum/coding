package problems;

import java.util.ArrayList;
import java.util.List;

public class AVLInterval {
	public static AVLIntervalNode insert(AVLIntervalNode subtreeRoot, int lower, int upper){
		if(subtreeRoot == null){
			return new AVLIntervalNode(lower, upper);
		}
		if(lower < subtreeRoot.lower){
			subtreeRoot.l = insert(subtreeRoot.l, lower, upper);
		}else{
			subtreeRoot.r = insert(subtreeRoot.r, lower, upper);
		}
		//fix balancing 
		int newDf = subtreeRoot.updateDfAndHeight();
		
		// tree becomes left heavy 
	    if (newDf > 1){
	    	if(lower > subtreeRoot.l.lower){
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
	    	if(lower < subtreeRoot.r.lower){
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
	public static AVLIntervalNode delete(AVLIntervalNode subtreeRoot, int lower, int upper){
		if(subtreeRoot == null){
			return subtreeRoot;
		}
		if(lower < subtreeRoot.lower){
			subtreeRoot.l = delete(subtreeRoot.l, lower, upper);
		}else if(lower > subtreeRoot.lower){
			subtreeRoot.r = delete(subtreeRoot.r, lower, upper);
		}else{
			//this is the key to delete
			//case 1: child < 2
			if(subtreeRoot.l == null || subtreeRoot.r  != null){
				AVLIntervalNode nonNullChild = (subtreeRoot.l != null)?subtreeRoot.l:subtreeRoot.r;
				if(nonNullChild != null){
					subtreeRoot.copyFileds(nonNullChild);
				}else{
					subtreeRoot = null;
				}
			}else{
			//case 2: child == 2
				//get inorder successor
				AVLIntervalNode inSuccessor = subtreeRoot.r;
				while(inSuccessor.l != null){
					inSuccessor = inSuccessor.l;
				}
				subtreeRoot.lower = inSuccessor.lower;
				subtreeRoot.upper = inSuccessor.upper;
				subtreeRoot.r = delete(subtreeRoot.r, inSuccessor.lower, inSuccessor.upper);
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
	public static AVLIntervalNode rightRotate(AVLIntervalNode subtreeRoot){
		AVLIntervalNode newRoot = subtreeRoot.l;
		subtreeRoot.l = newRoot.r;
		newRoot.r = subtreeRoot;
		subtreeRoot.updateDfAndHeight();
		newRoot.updateDfAndHeight();
		return newRoot;
	}
	public static AVLIntervalNode leftRotate(AVLIntervalNode subtreeRoot){
		AVLIntervalNode newRoot = subtreeRoot.r;
		subtreeRoot.r = newRoot.l;
		newRoot.l = subtreeRoot;
		subtreeRoot.updateDfAndHeight();
		newRoot.updateDfAndHeight();
		return newRoot;
	}
	
	public static void printLevelOrder(AVLIntervalNode root){
		List<AVLIntervalNode> q = new ArrayList<AVLIntervalNode>();
		q.add(root);
		int i = 0;
		while(!q.isEmpty()){
			System.out.print("Level " + i + " : " );
			List<AVLIntervalNode> newq = new ArrayList<AVLIntervalNode>();
			for(AVLIntervalNode n:q){
				
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
		AVLIntervalNode root = null;
		
	}
}

            
            
            
            



