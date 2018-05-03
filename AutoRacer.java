import java.io.*;
import java.util.*;

/*
Racer data structure
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
	int startSortedIndex;
	int score;
}
/*
Binary Indexed Tree:
data structure to store frequency

*/
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
	/*
		task : for each interval (startTime, endTime) search for all interval which overlap it
		
		algorithm steps:

		basically sort on end time and count the number of racer's (whose end time is less than the current end time) 
		start times ahead of the current racer start time.
 
		1) sort on end time
		2) iterate on end time startig from lowest
		3) mark the start time of current racer as seen (this is implemented using bit.update(racer.startSortedIndex, 1))  
		4) count the number of racer having start time more than current racer and have alreayd been seen.
			this is implememnted by:
			score = number of total seen racer - number of racer seen having start time > current racer start time
			racer.score = bit.count(n-1) - bit.count(racer.startSortedIndex);
		5) sort on score and print result  
	*/
	public static void main(String[] args) throws IOException {
  		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        	String line = br.readLine();
        	int n = Integer.parseInt(line);
		List<Racer> racers = new ArrayList<Racer>();
        	while ((line = br.readLine()) != null) {
            		String[] parts = line.split(" ");
			if(parts.length >= 3){
            			int id = Integer.parseInt(parts[0]);
				long start = Long.parseLong(parts[1]); 
				long end = Long.parseLong(parts[2]);
				Racer racer = new Racer(id, start, end);
				racers.add(racer); 
			}
        	}
		br.close();
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
			racers.get(i).startSortedIndex = i;
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
			bit.update(racer.startSortedIndex, 1);
			racer.score = bit.count(n-1) - bit.count(racer.startSortedIndex);
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
