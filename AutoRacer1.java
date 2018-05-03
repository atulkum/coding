import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
/*
The particular rating algorithm you have chosen is to assign 
each racer R a score that equals the number of other 
racers who both started after R started and also finished before R finished.
*/
class Racer{
	int racerId;
	long startTime;
	long endTime;
	
	public Racer(int id, long start, long end){
		racerId = id;
		startTime = start;
		endTime = end;
	}
	int startRank;
	int score;
}
class BIT{
	int n;
	int[] tree;
	public BIT(int size){
		n = size;
		tree = new int[n+1];
	}
       	public int count(int i){
        	i++;
                int sum = 0;
                while (i > 0){
                        sum += tree[i];
                        i -= (i & -i);
                }
                return sum;
        }
        public void update(int i ,int val){
                i++;
                while (i <= n){
                        tree[i] += val;
                        i += (i & -i);
                }
        }
	
}
public class AutoRacer{
	
	public static void main(String[] args) {
            	Scanner in = new Scanner(System.in);
            	int n = in.nextInt();
		List<Racer> racers = new ArrayList<Racer>();
		for(int i = 0 ; i < n; ++i){
			int id = in.nextInt();
			long start = in.nextLong(); 
			long end = in.nextLong();
			Racer racer = new Racer(id, start, end);
			racers.add(racer); 
		}	
		Collections.sort(racers, new Comparator<Racer>(){
			@Override
    			public int compare(Racer a, Racer b) {
				int ret = Long.compare(a.startTime,b.startTime);
				if(ret == 0){
        				return Integer.compare(a.racerId, b.racerId);
				}else{
					return ret;
				}
    			}
		});
		for(int i = 0 ;i < n; ++i){
			racers.get(i).startRank = i;
		}
		
		Collections.sort(racers, new Comparator<Racer>(){
			@Override
    			public int compare(Racer a, Racer b) {
				int ret = Long.compare(a.endTime,b.endTime);
				if(ret == 0){
        				return Integer.compare(a.racerId, b.racerId);
				}else{
					return ret;
				}
    			}
		});
		BIT bit = new BIT(n);
		
		for(int i = 0 ;i < n; ++i){
			Racer racer = racers.get(i);
			bit.update(racer.startRank, 1);
			racer.score = bit.count(n-1) - bit.count(racer.startRank);
		}
		Collections.sort(racers, new Comparator<Racer>(){
                        @Override 
                        public int compare(Racer a, Racer b) {
                                int ret = Integer.compare(a.score,b.score);
                                if(ret == 0){
        				return Integer.compare(a.racerId, b.racerId);
                                }else{
                                        return ret;
                                }
                        }
                });
		for(int i = 0 ;i < n; ++i){
			Racer racer = racers.get(i);
			System.out.println(racer.racerId + " " + racer.score);
                }
	}
}
