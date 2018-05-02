import java.io.*;
import java.util.*;
public class FSAHopcroftMinimization{
	private Node start;
	private Node finalNode;
	
	public FSAHopcroftMinimization(String fileName){
		finalNode = new Node();
		finalNode.isFinal = true;
		build(fileName);
	}
	
	void build(String fileName) {
		try{
			BufferedReader reader = new BufferedReader(
					new InputStreamReader(new DataInputStream(
							new FileInputStream(fileName))));

			String line = null;
			while((line = reader.readLine()) != null){
				line = line.trim();
				if(!line.equals("")){
					String[] labels = line.split("\\s+");
					start = insert(start, labels, 0);
				}
			}
			setFinal(start);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	Node insert(Node root, String[] labels, int n){
		if (root == null){
			root = new Node();
		}
		if (labels.length == n) {
			root.isFinal = true;
		}
		else {
			if(labels[n].charAt(0) == '-'){
				root.link[26] = insert(root.link[26], labels, n+1);
				root.link[26].parent = root;
			}
			else{
				root.link[labels[n].charAt(0) - 'A'] = insert(root.link[labels[n].charAt(0) - 'A'], labels, n+1);
				root.link[labels[n].charAt(0) - 'A'].parent = root;
			}
			root.hasChild = true;
		}
		return root;
	}
	
	void setFinal(Node root){
		if(root == null){
			return;
		}
		for(int i = 0; i < 27; i++){
			if(root.link[i] != null){
				if(!root.link[i].hasChild){
					root.link[i] = finalNode;
				}
				setFinal(root.link[i]);
			}
		}
	}
	
	void printAll(){		
		System.out.println(finalNode.id);
		print(start);
		System.out.println("(" + finalNode.id + " (" + start.id +" \"_\"))");
	}
	void print(Node root){
		if(root == null){
			return;
		}
		for(int i = 0; i < 27; i++){
			if(root.link[i] != null){
				String tran = "(" + root.id + " (" + root.link[i].id + " \"";				
				if(i != 26){
					tran = tran + (char)(i + 'A');
				}
				else{
					tran = tran + '-';
				}
				tran = tran + "\"))";

				System.out.println(tran);
				if(root.link[i].isFinal && root.link[i].hasChild){
					tran = "(" + root.link[i].id + " (" + finalNode.id + " *e*))";
					System.out.println(tran);
				}
				print(root.link[i]);
			}
		}
	}
	//Hopcroft FSA minimization algorithm
	void minimize(){
		HashMap<Integer, HashSet<Node>> groups = new HashMap<Integer, HashSet<Node>>();
		minInit(groups);
		int groupid = 2;
		int groupSize = groups.size();
		do{
			for(int gid: groups.keySet()){
				HashSet<Node> onegroup = groups.remove(gid);
				
				if(onegroup.size() == 1){
					groups.put(gid, onegroup);
					continue;
				}
				ArrayList<Node> tobedeleted = new ArrayList<Node>();
				
				for(Node member: onegroup){
					if(!member.hasChild  || member.group != gid){
						continue;
					}

					HashSet<Node> newgroup = new HashSet<Node>();
					groupid++;
					member.group = groupid;
					newgroup.add(member);
					groups.put(groupid, newgroup);
					tobedeleted.add(member);
					
					for(Node othermember: onegroup){
						
						if(othermember.id == member.id || othermember.group != gid) {
							continue;
						}
						boolean allMatching = true;
						for(int j = 0; j < 27; ++j){
							if((othermember.link[j] != null && member.link[j] == null)||
									(othermember.link[j] == null && member.link[j] != null)){
								allMatching = false;
							}
							if(othermember.link[j] != null && member.link[j] != null
									&&(othermember.link[j].group != member.link[j].group)){
								allMatching = false;
							}
						}
						if(allMatching){
							othermember.group = member.group;							
							newgroup.add(othermember);
							tobedeleted.add(othermember);
						}
					}
				}
				//remove the group members who are no longer here
				for(Node deletedNode: tobedeleted){
					onegroup.remove(deletedNode);
				}
				if(onegroup.size() > 0){
					groups.put(gid, onegroup);
				}
			}
		}while(groupSize == groups.size());
		
		buildMinimized(groups);
	}
	void buildMinimized(HashMap<Integer, HashSet<Node>> groups){
		HashMap<Integer, Node> groupId2Node = new HashMap<Integer, Node>();
		start.id = start.group;
		groupId2Node.put(start.group, start);
		groups.remove(start.group);
		finalNode.id = finalNode.group;
		groupId2Node.put(finalNode.group, finalNode);
		groups.remove(finalNode.group);
		
		for(Integer i : groups.keySet()){
			HashSet<Node> nodes = groups.get(i);
			Node node = nodes.iterator().next();
			node.id = node.group;
			groupId2Node.put(i, node);
		}
		fixNodes(start, groupId2Node);
	}
	
	void fixNodes(Node root, HashMap<Integer, Node> groupId2Node){
		if(root == null){
			return;
		}
		for(int i = 0; i < 27; i++){
			if(root.link[i] != null){
				root.link[i] = groupId2Node.get(root.link[i].group);
				fixNodes(root.link[i], groupId2Node);
			}
		}
	}
	void minInit(HashMap<Integer, HashSet<Node>> groups){
		HashSet<Node> nonFinalGroup = new HashSet<Node>();
		HashSet<Node> finalGroup = new HashSet<Node>();
		nonFinalGroup.add(start);
		start.group = 1;
		setFinalAndNonFinal(start, finalGroup, nonFinalGroup);
		groups.put(1, nonFinalGroup);
		groups.put(2, finalGroup);
	}
	void setFinalAndNonFinal(Node root, HashSet<Node> finalGroup, HashSet<Node> nonFinalGroup){
		if(root == null){
			return;
		}
		for(int i = 0; i < 27; i++){
			if(root.link[i] != null){
				if(root.link[i].isFinal){
					finalGroup.add(root.link[i]);
					root.link[i].group = 2;
				}
				else{
					nonFinalGroup.add(root.link[i]);
					root.link[i].group = 1;
				}
				setFinalAndNonFinal(root.link[i], finalGroup, nonFinalGroup);
			}
		}
	}
	
	public static void main(String[] args){		
		if(args.length < 1){
			System.out.println("USAGE: java  -Xms1024m -Xmx1024m Trie <filename> [m]  >  <output file name>");
			System.out.println("filename - the dictionary filename.");
			System.out.println("m is optional if you want minimized FSA.");
			System.out.println("minimized FSA needs -Xms1024m -Xmx1024m as it needs lots of memory.");
			return;
		}
		
		boolean isMinimized = false;
		
        FSAHopcroftMinimization t = new FSAHopcroftMinimization(args[0]);
        if(args.length > 1 && args[1].endsWith("m")){
            isMinimized = true;
        }
        if(	isMinimized){
            t.minimize();
        }
        t.printAll();
		
	}
}
class Node{
	boolean isFinal;
	Node[] link;
	int id;
	Node parent;
	int group;
	static int numNodes = 0;
	boolean hasChild;
	public Node(){
		isFinal = false;
		id = numNodes++;
		link = new Node[27];
		hasChild = false;
	}
}
