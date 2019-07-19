#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/**
 * https://blog.csdn.net/joekwok/article/details/4749713
 * https://www.jianshu.com/p/30ba1d66c729
 * https://jerkwin.github.io/2016/03/17/%E6%97%85%E8%A1%8C%E6%8E%A8%E9%94%80%E5%95%86%E9%97%AE%E9%A2%98TSP%E7%9A%84%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E8%A7%A3%E6%B3%95/
 */

int tsp(vector<vector<int>>& city_dis) {
    if (city_dis.empty()) {
        return 0;
    }

    int size = city_dis.size();
    vector<vector<int>> dp(size, vector<int>(pow(2, size-1), 0));
    for (int i = 0; i < size; ++i) {
        dp[i][0] = city_dis[i][0]; //initialize the first column
    }

    for (int u = 1; u < dp[0].size(); ++u) {
        for (int i = 0; i < dp.size(); ++i) { 
            if (0 == ((1<<(i-1)) & u)) { 
                int min_dis = INT32_MAX;
                for (int k = 1; k < size; ++k) { 
                    if (0 != ((1<<(k-1)) & u)) {
                        int temp = city_dis[i][k] + dp[k][u - (1<<(k-1))];
                        if (temp < min_dis) {
                            min_dis = temp;
                        }
                    }
                }
                dp[i][u] = min_dis;
            }
        }
    }

    for (auto& row : dp) {
        for (auto& val : row) {
            cout << val <<"\t";
        }
        cout << endl;
    }
    /**
     * 0	0	0	0	0	0	0	[10]	
     * 5	0	8	0	6	0	7	0	
     * 6	9	0	0	5	10	0	0	
     * 3	12	11	14	0	0	0	0
     * res = 10
     */

    return dp[0].back();
}

int main(int argc, char const *argv[]) {
    vector<vector<int>> city_dis = {
        {0, 3, 6, 7}, 
        {5, 0, 2, 3}, 
        {6, 4, 0, 2}, 
        {3, 7, 5, 0}};

    int min_dis = tsp(city_dis);
    cout << min_dis << endl;

    return 0;
}
