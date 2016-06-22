struct Feed{
    int ts;
    int score;
    int sz;
    int id;
    Feed(int _ts, int _score, int _sz, int _id)
        :ts(_ts), score(_score), sz(_sz), id(_id)
    {}
};
std::vector<int> knapsake(std::list<Feed>& q, int h){
    using namespace std;
    vector<int> ret;
    if(q.empty()){
        ret.push_back(0);
        return ret;
    }
    vector<Feed> feeds(q.begin(), q.end());
    sort(feeds.begin(), feeds.end(), 
         [](const Feed& f1, const Feed& f2){
             if(f1.score == f2.score){
                 return f1.sz > f2.sz;
             }else {
                 return f1.score > f2.score; 
             }
         });
    int W = h+1;
    int N = feeds.size() + 1;
    vector<vector<int>> dp(N, vector<int>(W, 0));
    vector<vector<bool>> dpi(N, vector<bool>(W, false));
    
    for(int o = 1; o < N; ++o){
        for(int w = 1; w < W; ++w){
            //i knapsake , j object =>  max score
            dp[o][w] = dp[o-1][w];
            Feed feed = feeds[o-1];
            int left = w - feed.sz;
            if(left >= 0 
               && dp[o][w] < dp[o-1][left] + feed.score){
                dp[o][w] = dp[o-1][left] + feed.score;
                dpi[o][w] = true;
            }
        }
    }
    int o = N-1;
    int w = W-1;
    while(o >0 && w >0){
        if(dpi[o][w]){
            w -= feeds[o-1].sz; 
            ret.push_back(feeds[o-1].id);
        }
        o--;
    }
    sort(ret.begin(), ret.end());
    ret.insert(ret.begin(), dp[N-1][W-1]);

    return ret;
}
std::vector<std::vector<int>> feedOptimizer(int span, int h, std::vector<std::vector<int>> events) {
    using namespace std;
    list<Feed> q;
    int id = 1;
    vector<vector<int>> ret;
    for(std::vector<int> event: events){
        if(event.size() == 1){
            int currTime = event[0];
            while(!q.empty() && q.front().ts < currTime - span){
                q.pop_front();
            }
            ret.push_back(knapsake(q, h));
        }else{
            Feed feed(event[0], event[1], event[2], id++);
            q.push_back(feed);
        }
    }
    return ret;
}
