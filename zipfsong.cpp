#include <iostream>
#include <algorithm>
#include <vector>

struct Song{
	long q;
	std::string name;
	int i;
};
bool comparator(const Song& s1, const Song& s2) 
                {
                        if(s1.q == s2.q){
                                return s1.i < s2.i;
                        }else{
                                return s1.q > s2.q;
                        }
                }
int main(){
	std::vector<Song> songs;
	int n, m;
	std::cin >> n >> m;
	for(int i = 1; i <= n; ++i ){
		Song s;
		s.i = i;
		std::cin >> s.q >> s.name;
		s.q *= i;
		songs.push_back(s);
	}
	sort(songs.begin(), songs.end(), comparator

 		/*[](const Song& s1, const Song& s2) -> bool
		{
			if(s1.q == s2.q){
				return s1.i < s2.i;
			}else{
				return s1.q > s2.q;
			}
		}*/);
	
	for(int i = 0; i < m && i < n; ++i){
		std::cout << songs[i].name << std::endl;
	}
}
