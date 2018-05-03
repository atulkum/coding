#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

struct CriticalPoints{
    int pos;
    bool isX;
    vector<int>* building;
    CriticalPoints(int _pos, vector<int> *_building){
        pos = _pos;
        isX = false;
        building = _building;
    }
};
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
	cout << buildings.size() << endl;
        if(buildings.empty()){
            return vector<pair<int, int>>();
        }
        vector<CriticalPoints> cps;
        for(vector<int> &p:buildings){
            CriticalPoints cpx(p[0], &p);
            CriticalPoints cpy(p[1], &p);
            cpx.isX = true;
	    cps.push_back(cpx);
	    cps.push_back(cpy);
        }

        sort(cps.begin(), cps.end(), [](CriticalPoints a, CriticalPoints b){return a.pos < b.pos;});
        for(CriticalPoints &cp:cps){
            vector<int> b = *(cp.building);
            cout << cp.pos << " " << cp.isX << " [" << b[0] << "," << b[1] << "," << b[2] << "]" << endl;
        }
        auto cmp = [](vector<int>* a, vector<int>* b){return (*a)[2] < (*b)[2];};
        vector<pair<int, int>> ret;

        vector<vector<int>*> heap1;
        int preHt = -1;
        for(CriticalPoints &cp:cps){
            if(cp.isX){
                heap1.push_back(cp.building); push_heap (heap1.begin(),heap1.end(), cmp);
            }else{
                heap1.erase(remove(heap1.begin(), heap1.end(), cp.building), heap1.end());
                make_heap(heap1.begin(),heap1.end(), cmp);
            }
            vector<int> topcp = *(heap1.front());
            if(preHt != topcp[2]){
                ret.push_back(make_pair(cp.pos, topcp[2]));
                preHt = topcp[2];
            }
        }
        return ret;
    }
//[ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ]
int main(){
	vector<vector<int>> in(5);
	in[0] = {2,9,10};
	in[1] = {3,7,15};
	in[2] = {5,12,12};
	in[3] = {15,20,10};
	in[4] = {19,24,8};
	vector<pair<int, int>> ret = getSkyline(in);
	for(auto & p:ret){
		cout << p.first << " " << p.second << endl;
	}
	return 0;
}
