## custom priority_queue


```
#include <queue>
auto comp = [](pair<int, int> a, pair<int, int> b){return a.first < b.first;};
typedef priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> mypq; 

mypq q(comp);
```

```
#include <functional>

typedef std::pair<string,string> Name;
 
namespace std {
    template <>
        class hash<Name>{
        public :
            size_t operator()(const Name &name ) const{
                return hash<string>()(name.first) ^ hash<string>()(name.second);
            }
    };
};
```
