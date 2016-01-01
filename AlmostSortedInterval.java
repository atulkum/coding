import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class AlmostSortedInterval{
        public static void main(String[] args) {
            Scanner in = new Scanner(System.in);

            int n = in.nextInt();
            int[] ar = new int[n];
            for(int j=0;j<n;j++){
                ar[j]=in.nextInt();
            }
            //nearest left higher 
	    //key is the nearest higher for values indices   
            Map<Integer, Set<Integer>> leftMap = new HashMap<Integer, Set<Integer>>();
            Stack<Integer> st = new Stack<Integer>();
            for(int i = 0; i < n; ++i){
                while(!st.isEmpty() && ar[st.peek()] < ar[i] ){
                    st.pop();
                }
                int l;
                if(st.isEmpty()){
                    l = -1;
                }else{
                        l = st.peek();
                }
                if(!leftMap.containsKey(l)){
                	leftMap.put(l, new HashSet<Integer>());
                }
                leftMap.get(l).add(i);
                st.push(i);
            }
            st.clear();
	    //nearest right lower
            int[] right = new int[n];
            for(int i = n -1; i >= 0; --i){
                while(!st.isEmpty() && ar[st.peek()] > ar[i] ){
                    st.pop();
                }
                if(st.isEmpty()){
                    right[i] = n;
                }else{
                    right[i] = st.peek();
                }
                st.push(i);
            }
            //i, j =>  j < right[i] and i > left[j]
            //if i is the current index 
	    //count of sets start with i  
	    // all the js should have left[j] < i
	    // remove form B all the js which has left[j] < i
            //count all the js which has < right[i]
            //count till right[i] - 1
            int[] tree = new int[n+2];
            long count = 0;
            for(int i = n -1; i >= 0; --i){
                if(leftMap.containsKey(i)){
                        for(int lval : leftMap.get(i)){
                                update(lval, -1, n+1, tree);
                        }
                }
                update(i, 1, n+1, tree);
                count += count(right[i]-1, tree);
            }
            System.out.println(count);
        }
       static int count(int idx, int[] tree){
                idx++;
                int sum = 0;
                while (idx > 0){
                        sum += tree[idx];
                        idx -= (idx & -idx);
                }
                return sum;
        }
        static void update(int idx ,int val,int max,int[] tree){
                idx++;
                while (idx <= max){
                        tree[idx] += val;
                        idx += (idx & -idx);
                }
        }

}
