import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class AlmostSortedInterval {
       static int count(int idx, int[] tree){
                int sum = 0;
                while (idx > 0){
                        sum += tree[idx];
                        idx -= (idx & -idx);
                }
                return sum;
        }
        static void update(int idx ,int val,int max,int[] tree){
                while (idx <= max){
                        tree[idx] += val;
                        idx += (idx & -idx);
                }
        }

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        
        for(int i=0;i<t;i++){
            int n = in.nextInt();
            int[] ar = new int[n];
            for(int j=0;j<n;j++){
                ar[j]=in.nextInt();
            }
            int[] left = new int[n];
            int[] right = new int[n];
            Stack<Integer> st = new Stack<Integer>();
            for(int i = 0; i < ar.length; ++i){
                while(!st.isEmpty() && ar[st.peek()] < ar[i] ){
                    st.pop();
                }
                if(st.isEmpty()){
                    left[i] = -1;
                }else{
                    left[i] = st.peek();
                }
                st.push(i);
            }
            st.clear();
            for(int i = ar.length -1; i >= 0; --i){
                while(!st.isEmpty() && ar[st.peek()] < ar[i] ){
                    st.pop();
                }
                if(st.isEmpty()){
                    left[i] = ar.length;
                }else{
                    left[i] = st.peek();
                }
                st.push(i);
            }
            int[] tree = new int[ar.length+1];
            Map<Integer, List<Integer>> m = new HashMap<Integer, List<Integer>>();
            for(int i = ar.length -1; i >= 0; --i){
                m.remove(i);
                if(left[i] >= 0){
                    if(!m.containsKey(left[i])){
                        m.put(left[i], new ArrayList<Integer>());
                    }
                    m.get(left[i]).add(i);
                }
            }
        }
    }
}
