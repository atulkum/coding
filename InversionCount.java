import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class InversionCount {
    //static int sz = 1000000 + 111;
    //static int[] tree = new int[sz];
    public static void main(String[] args) {
        
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        
        for(int i=0;i<t;i++){
            int n = in.nextInt();
            int[] ar = new int[n];
            int max = Integer.MIN_VALUE;
            for(int j=0;j<n;j++){
                ar[j]=in.nextInt();
                if(ar[j] > max){
                    max = ar[j];
                }
            }
            long c = insertSort(ar, max);      
            System.out.println(c);
        }
}
    
    
    public static long insertSort(int[] ar, int max)
    {
        long count = 0;
        //Arrays.fill(tree, 0);
        
        int[] tree = new int[max+1];
        for(int a : ar){
            count += count(max, tree) - count(a, tree);
            update(a, 1, max, tree);
          
        }
        return count;
        
    }
    
   
    
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
    
}
