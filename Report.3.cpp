#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Item Struct
struct Item {
    int w;  // Weight
    int p;  // Profit
    double r; // Profit-to-Weight Ratio
};

// 6.1 Fractional Knapsack - Greedy
double fractional(vector<Item> a, int C) {
    for (auto &x : a) {
        x.r = (double)x.p / x.w;
    }

    // Sort in decreasing order of ratio
    sort(a.begin(), a.end(), [](Item x, Item y) {
        return x.r > y.r;
    });

    double profit = 0;
    for (auto x : a) {
        if (C >= x.w) {
            C -= x.w;
            profit += x.p;
        } else {
            profit += x.r * C;
            break;
        }
    }
    return profit;
}

// 6.2 0/1 Knapsack - Greedy
int greedy01(vector<Item> a, int C) {
    for (auto &x : a) {
        x.r = (double)x.p / x.w;
    }

    // Sort in decreasing order of ratio
    sort(a.begin(), a.end(), [](Item x, Item y) {
        return x.r > y.r;
    });

    int profit = 0;
    for (auto x : a) {
        if (x.w <= C) {
            C -= x.w;
            profit += x.p;
        }
    }
    return profit;
}

// 6.3 0/1 Knapsack - Dynamic Programming
int knapsackDP(vector<Item> a, int C) {
    int n = a.size();
    vector<vector<int>> dp(n + 1, vector<int>(C + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int c = 0; c <= C; c++) {
            dp[i][c] = dp[i - 1][c];
            if (a[i - 1].w <= c) {
                dp[i][c] = max(dp[i][c], a[i - 1].p + dp[i - 1][c - a[i - 1].w]);
            }
        }
    }
    return dp[n][C];
}

int main() {
    // Test Case 3 from Lab Report: Capacity = 50
    // Items: (Weight, Profit) = (10, 60), (20, 100), (30, 120)
    int C = 50;
    vector<Item> items = {
        {10, 60, 0.0},
        {20, 100, 0.0},
        {30, 120, 0.0}
    };

    cout << "--- Test Case Results ---" << endl;
    cout << "1. Fractional Knapsack (Greedy): " << fractional(items, C) << endl;
    cout << "2. 0/1 Knapsack (Greedy): " << greedy01(items, C) << endl;
    cout << "3. 0/1 Knapsack (DP): " << knapsackDP(items, C) << endl;

    return 0;
}