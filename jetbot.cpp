int minDelay = INT_MAX;
std::set<int> vendors; 

void backtrack(std::vector<int>& vd, 
      std::vector<std::vector<int>>& vp,
              std::vector<int>& curr, 
               int left, int delay) {
    int n_vendors = vp.size();
    int items = vp[0].size();
    int itemid = curr.size();
            
    if(itemid == items){
        if(minDelay > delay){
            minDelay = delay;
            vendors.clear();
            vendors.insert(curr.begin(), curr.end());
        }
    }else if(left < 0 || minDelay < delay){
        return;
    }
    
    for(int vid = 0; vid < n_vendors; ++vid){
        if(vp[vid][itemid]>0 && left >= vp[vid][itemid]){
            curr.push_back(vid);
            backtrack(vd, vp, curr, left - vp[vid][itemid],
                     std::max(vd[vid], delay));
            curr.pop_back();
        }
    }
    
}

std::vector<int> minimalBasketPrice(int mp, std::vector<int> vd, std::vector<std::vector<int>> vp) {
	int nItems = vp[0].size();
	int nVendors = vp.size();
	std::vector<std::vector<int>> dp(mp, std::vector<int> (nItems, -1));
	std::vector<std::vector<int>> dpVendor(mp, std::vector<int> (nItems, -1));
	std::vector<std::vector<int>> dpi(mp, std::vector<int> (nItems, -1));
		
	for(int i = 0 ;i < mp; i++){
		for(int j = 0; j < nItems; ++j){
			int minDelay = -1;
			int minDelayVendor = -1;
			int prei = -1;
			for(int k = 0; k < nVendors; ++k){
				if(j == 0){
					if(i > 0){
						minDelay = dp[i-1][j];
						minDelayVendor = dpVendor[i-1][j];
						prei = dpi[i-1][j];
					}
					if(vp[k][j] >= 0){
						if(minDelay == -1 || vd[k] < minDelay){
							minDelay = vd[k];
							minDelayVendor = k;
						}
					}
				}else{
					int left = i+1 - vp[k][j]; 
					if(vp[k][j] >= 0 && left >= 0){
						if(i > 0){
							minDelay = dp[i-1][j];
							minDelayVendor = dpVendor[i-1][j];
							prei = dpi[i-1][j];
						}
						int newDelay = std::max(vd[k], dp[i][left]);
						if(minDelay == -1 || newDelay < minDelay){
							minDelay = newDelay
							minDelayVendor = k;
							prei = dpVendor[i][left];
						}
						
					} 
				}
			}
			dp[i][j] = minDelay;
			dpVendor[i][j] = minDelayVendor;
			dpi[i][j] = prei;
		}
	}
	int minDelay = INT_MAX;
	int mini = -1;
	for(int i = 0 ;i < mp; i++){
		if(dp[i][nItems-1] > 0 && minDelay > dp[i][nItems-1]){
			minDelay = dp[i][nItems-1];
			mini = i;		
		}	
	}
	std::set<int> ret1;
	int i = mini;
	for(int j = nItems; j >= 0; --j){
		ret1.insert(dpVendor[i][j]);
		i = dpi[i][j];
	}
	return std::vector<int>(ret1.begin(), ret1.end());

}
/*

maxPrice = 7, vendorsDelivery = [5, 4, 2, 3] and

vendorsProducts = [[1, 1, 1],
                   [3, -1, 3],
                   [-1, 2, 2],
                   [5, -1, -1]]

[1, 2]
*/
