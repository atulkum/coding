import java.util.*;
import java.lang.*;

class MatrixSum
{
	static void update(int x , int y , int val, int n, int m, int[][] tree){
		while (x <= n){
			while (y <= m){
				tree[x][y] += val;
				y += (y & -y); 
			}
			x += (x & -x); 
		}
	}
	
	static int sum(int x , int y, int[][] tree){
		int sum = 0;
		while (x > 0){
			while (y > 0){
				sum += tree[x][y];
				y -= (y & -y); 
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
        		int size = in.nextInt();
        		int n = 1;
        		while(size > n){
        			n *= 2;
        		}
        		int[][] tree = new int[n+1][n+1];
        		while(true){
        			String line = in.nextLine();
        			String[] parts = line.split(" ");
        			if(parts[0].equals("END")){
        				System.out.println();
        				break;
        			}else if(parts[0].equals("SET")){
        				//SET x y num
        				int x = Integer.parseInt(parts[1]) + 1;
        				int y = Integer.parseInt(parts[2]) + 1;
        				int num = Integer.parseInt(parts[3]);
        				update(x,y,num, n, n, tree);
					for(int i = 1; i <= n; ++i){
						for(int j = 1; j <= n; ++j){
        						System.out.print( tree[i][j] + "  ");
						}
        					System.out.println();
					}
        			}else if(parts[0].equals("SUM")){
        				//SUM x1 y1 x2 y2
        				int x1 = Integer.parseInt(parts[1])+1;
        				int y1 = Integer.parseInt(parts[2])+1;
        				int x2 = Integer.parseInt(parts[3])+1;
        				int y2 = Integer.parseInt(parts[4])+1;
        				System.out.println(sum(x2,y2,tree) + ":" + sum(x1,y1,tree) 
						+ " : " + sum(x1,y2,tree) +" : "+ sum(x2,y1,tree));
        			}
        		}
        	}
	}
}
