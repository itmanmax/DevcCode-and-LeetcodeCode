#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight;
    int profit;
};

vector<Item> items;
vector<int> x, bestx;
int n, M, maxp = 0, cp = 0, cw = 0;

void Backtrack(int i) {
    if (i >= n) {
        if (cp > maxp) {
            maxp = cp;
            bestx = x;
        }
        return;
    }
    int r = 0;
    for (int j = i; j < n; j++) r += items[j].profit;
    if (cw + items[i].weight <= M) {
        x[i] = 1;
        cp += items[i].profit;
        cw += items[i].weight;
        if (cp + r > maxp) Backtrack(i + 1);
        cp -= items[i].profit;
        cw -= items[i].weight;
    }
    if (cp + r - items[i].profit > maxp) {
        x[i] = 0;
        Backtrack(i + 1);
    }
}

int main() {
    cin >> n >> M;
    items.resize(n);
    x.resize(n);
    bestx.resize(n);
    for (int i = 0; i < n; i++) cin >> items[i].profit;
    for (int i = 0; i < n; i++) cin >> items[i].weight;
    Backtrack(0);
    cout << maxp << endl;
    for (int i = 0; i < n; i++) cout << bestx[i] << (i == n - 1 ? "\n" : " ");
    return 0;
}

