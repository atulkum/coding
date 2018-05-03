import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

class Vertex implements Comparable<Vertex>{
	public int x;
	public int y;
	public int z;
	public int height;
	public static int N;
	public static int M;

	public int minDistance = Integer.MAX_VALUE;
	public Vertex pre;

	public int compareTo(Vertex other){
        	return Integer.compare(minDistance, other.minDistance);
    	}
	public Vertex(int x, int y, int height, int z){
		this.x = x;
		this.y = y;
		this.z = z;
		this.height = height;
	}
	public void reset(){
		minDistance = Integer.MAX_VALUE;
		pre = null;
	}
	public int getWeight(){
		return Math.abs(height - z);  
	}
	public List<Vertex> neighbours(Vertex[][][] mat){
		int[] d = {-1,1};
		List<Vertex> neighs = new ArrayList<Vertex>();
		for(int df : d){
			if(0 <= (x + df) && (x + df) < N){
				neighs.add(mat[x + df][y][z]);
				if(0 <= z-1){
					neighs.add(mat[x + df][y][z-1]);
				}
			} 
			if(0 <= (y + df) && (y + df) < M){
				neighs.add(mat[x][y+df][z]);
				if(0 <= z-1){
					neighs.add(mat[x][y+df][z-1]);
				}
			} 
		}
		return neighs;
	}
	public String toString(){
		return  "(" + x + "," + y +"," +z + ") => h: " + 
			height + " dist:" + minDistance;
	}
	/*public boolean equals(Vertex other){
		return (x == other.x) && (y == other.y);
	}
	public int hash(){
		return M*x + y;
	}*/
}
public class OptimalTerraforming {
	public static Vertex dijkstra(Vertex src, Vertex dest, Vertex[][][] mat){
		src.minDistance = src.getWeight();
		PriorityQueue<Vertex> minHeap = new PriorityQueue<Vertex>();
		minHeap.add(src);
		int minValue = Integer.MAX_VALUE;
		Vertex ret = null;
		while(!minHeap.isEmpty()){
			Vertex u = minHeap.poll();
			if(u.x == dest.x && u.y == dest.y && minValue > u.minDistance){
				minValue = u.minDistance;
				ret = u;
			}
			for(Vertex v:u.neighbours(mat)){
				int distuv = u.minDistance + v.getWeight();
				if(distuv < v.minDistance){
					minHeap.remove(v);
					v.pre = u;
					v.minDistance = distuv;
					minHeap.add(v); 		
				}
			}
		}
		return ret;
	}
    	public static void main(String[] args) {
        	Scanner in = new Scanner(System.in);
        	int N = in.nextInt();
		int M = in.nextInt();
		Vertex.N = N;
		Vertex.M = M;
		int startX = in.nextInt();
		int startY = in.nextInt();
		int endX = in.nextInt();
		int endY = in.nextInt();
		//System.out.println(N + " : " + M + ":" + startX + ":" + startY + ":" + endX + ":" + endY);
		Vertex[][][] mat = new Vertex[N][M][10];
		in.nextLine();
		for(int i =0;i<N;++i){
			char[] row = in.nextLine().toCharArray();
			//System.out.println(Arrays.toString(row));
			for(int j =0;j<M;++j){
				for(int l = 0; l < 10; l++){
					mat[i][j][l] = new Vertex(i, j, row[j]-'0', l);
				}
			}	
		}
		int cost = Integer.MAX_VALUE;
		for(int level = 0; level <= 9; ++level){
			Vertex src = mat[startX-1][startY-1][level];
			for(int leveld = 0; leveld <= 9; ++leveld){
				//System.out.println("level:" + level + " leveld:" + leveld);	
				Vertex dest = mat[endX-1][endY-1][leveld];
				dest = dijkstra(src, dest, mat);
				if(dest != null){
					if(cost > dest.minDistance){
						cost = dest.minDistance;
					}
					/*System.out.println("path:");
					Vertex curr = dest;
					while(1==1){
						System.out.println(curr);
						if(curr == src)break;
						curr = curr.pre;
					}*/
				}else{
					//System.out.println("dest NULL");
				}
				//System.out.println();
		
				for(int i =0;i<N;++i){
                        		for(int j =0;j<M;++j){
                        			for(int k =0;k<10;++k){
                                			mat[i][j][k].reset(); 
						}
                        		}
                		}
			
			}
		}
////////////

	/*		Vertex src = mat[startX-1][startY-1][2];
			Vertex dest = mat[endX-1][endY-1][1];
			dest = dijkstra(src, dest, mat);
			if(dest != null){
				if(cost > dest.minDistance){
					cost = dest.minDistance;
				}
				System.out.println("path:");
				Vertex curr = dest;
				while(1==1){
					System.out.println(curr);
					if(curr == src)break;
					curr = curr.pre;
				}
			}else{
				System.out.println("dest NULL");
			}
			System.out.println();
	*/	
////////////
		System.out.println(cost);
	}

}
