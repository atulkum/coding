import java.util.*;
import java.lang.*;

class MatrixSum
{
	static void update(int x , int y , int val, int n, int m, int[][] tree){
		x = x + 1;
		y = y + 1;
		while (x <= n){
			int y1 = y;
			while (y1 <= m){
				tree[x][y1] += val;
				y1 += (y1 & -y1); 
			}
			x += (x & -x); 
		}
	}
	
	static int sum(int xx , int yy, int[][] tree){
		int x = xx + 1;
		int y = yy + 1;
		int sum = 0;
		while (x > 0){
			int y1 = y;
			while (y1 > 0){
				sum += tree[x][y1];
				y1 -= (y1 & -y1); 
			}
			x -= (x & -x);
		}
		
		return sum;
	}
	public static void main (String[] args) throws java.lang.Exception
	{
		Scanner in = new Scanner(System.in);
        	int T = in.nextInt();
 
        	for(int t=0;t<T;t++){
        		int n = in.nextInt();
        		int[][] tree = new int[n + 1][n + 1];
        		int[][] vals = new int[n][n];
        		while(true){
        			String line = in.nextLine();
        			String[] parts = line.split(" ");
        			if(parts[0].equals("END")){
        				System.out.println();
        				break;
        			}else if(parts[0].equals("SET")){
        				//SET x y num
        				int x = Integer.parseInt(parts[1]);
        				int y = Integer.parseInt(parts[2]);
        				int num = Integer.parseInt(parts[3]);
        				update(x,y,num-vals[x][y], n, n, tree);
					vals[x][y] = num;
        			}else if(parts[0].equals("SUM")){
        				//SUM x1 y1 x2 y2
        				int x1 = Integer.parseInt(parts[1]);
        				int y1 = Integer.parseInt(parts[2]);
        				int x2 = Integer.parseInt(parts[3]);
        				int y2 = Integer.parseInt(parts[4]);
        				System.out.println(sum(x2,y2,tree) + sum(x1-1,y1-1,tree) 
						- sum(x1-1,y2,tree) - sum(x2,y1-1,tree));
        			}
        		}
        	}
	}
}
