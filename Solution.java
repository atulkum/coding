package problems;

import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
    static int sz = 1000000 + 111;
    static int[] tree = new int[sz];
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
        long count = 0;
        Arrays.fill(tree, 0);
        for(int a : ar){
            count += count(sz-1) - count(a);
            update(a, 1);
          
        }
        return count;
        
    }
    
   
    
	static int count(int idx){
		int sum = 0;
		while (idx > 0){
			sum += tree[idx];
			idx -= (idx & -idx);
		}
		return sum;
	}
	static void update(int idx ,int val){
		while (idx < sz){
			tree[idx] += val;
			idx += (idx & -idx);
		}
	}
    
}