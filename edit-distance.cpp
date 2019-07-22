#include <iostream>
#include <vector>
#include <string>
using namespace std;

int edit_distance(const string& a, const string& b) {
    if (a.empty() || b.empty()) {
        return a.size() ^ b.size();
    }

    vector<vector<int>> dp(a.size()+1, vector<int>(b.size()+1, 0));

    for (int i = 0; i <= b.size(); ++i) {
        dp[0][i] = i;
    }

    for (int i = 0; i <= a.size(); ++i) {
        dp[i][0] = i;
    }

    for (int i = 1; i <= a.size(); ++i) {
        for (int j = 1; j <= b.size(); ++j) {
            dp[i][j] = std::min(dp[i-1][j-1] + (a[i-1] == b[j-1] ? 0 : 1),
                    std::min(dp[i-1][j]+1, dp[i][j-1]+1));
        }
    }

    return dp.back().back();
}

int main(int argc, char const *argv[]) {
    string a = "cats";
    string b = "fast";

    int res = edit_distance(a, b);

    cout << res << endl;

    return 0;
}

/**
 * MacBook-Pro:algorithm qingdujun$ ./a.out 
 * 0 1 2 3 4 
 * 1 1 2 3 4 
 * 2 2 1 2 3 
 * 3 3 2 2 2 
 * 4 4 3 2 3
 */