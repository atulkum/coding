## custom priority_queue


```
#include <queue>
auto comp = [](pair<int, int> a, pair<int, int> b){return a.first < b.first;};
typedef priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> mypq; 

mypq q(comp);
```
