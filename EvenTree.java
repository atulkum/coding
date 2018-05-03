import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class EvenTree {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
      
        Scanner scan = new Scanner(System.in);
        int N = scan.nextInt(); 
        int M = scan.nextInt();
        int[] parentTree = new int[N+1];
        int[] count = new int[N+1];
        Arrays.fill(count, 1);
        for(int i=0;i<M;i++){
            int v = scan.nextInt();
            int u = scan.nextInt();
            parentTree[v] = u;
            
            while(parentTree[u] != 0){
                count[u]++;
                u = parentTree[u];
            }
        }
	System.out.println(Arrays.toString(parentTree));
	System.out.println(Arrays.toString(count));

        int c = 0;
        for(int i = 1; i < count.length; i++){
            if(count[i]%2 == 0){
                c++;
            }
        }
        System.out.println(c);
    }
}
