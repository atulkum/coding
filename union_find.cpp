#include <vector>
using namespace std;

class UnionFind{
private:
  vector<int> Arr;
  vector<int> size;
  int N;
public:
  UnionFind(int _N): Arr(N), size(N), N(_N){
    initialize();
  }
  void initialize(){
    for(int i = 0;i<N;i++){
      Arr[ i ] = i ;
      size[ i ] = 1;
    }
  }

  void weighted-union(int A,int B){
    int root_A = root(A);
    int root_B = root(B);
    if(root_A == root_B) {
    	return;
    }
    if(size[root_A] < size[root_B ]){
      Arr[ root_A ] = Arr[root_B];
      size[root_B] += size[root_A];
    }else{
      Arr[ root_B ] = Arr[root_A];
      size[root_A] += size[root_B];
    }
  }
  int root (int i){
    while(Arr[ i ] != i){
      Arr[ i ] = Arr[ Arr[ i ] ] ; 
      i = Arr[ i ]; 
    }
    return i;
  }

  bool find(int A,int B){
    return root(A)==root(B);
  }
};
