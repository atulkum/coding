import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class CountingInversion {
    public static void main(String[] args) {
        
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        
        for(int i=0;i<t;i++){
            int n = in.nextInt();
            int[] ar = new int[n];
            for(int j=0;j<n;j++){
                ar[j]=in.nextInt();
            }
            long c = insertSort(ar);      
            System.out.println(c);
        }
}
    
    
    public static long insertSort(int[] ar)
    {
        int max = Integer.MIN_VALUE;
        for(int a : ar){
            if(max < a){
                max = a;
            }
        }
        int size = 1;
		while(max > size){
			size *= 2;
		}
        size *= 2;
        int[] tree = new int[size];
        long count = 0;
        for(int a : ar){
            count += count(size-1, tree) - count(a, tree);
            update(a, 1, tree, size);
          
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
	static void update(int idx ,int val, int[] tree, int max){
		while (idx < max){
			tree[idx] += val;
			idx += (idx & -idx);
		}
	}
    
}
