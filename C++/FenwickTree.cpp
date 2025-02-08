/*

空の配列 A があります。 i=1,2,…,N の順に以下の操作を行います。
数 i を、A の前から P i番目の位置になるように挿入する。より正確には、「A の Pi−1 項目まで」「 i 」「A の P i項目以降」をこの順に連結したもので A を置き換える。全ての操作を終えた後のA を出力してください。

*/

#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
public:
    vector<int> tree;
    int size;

    FenwickTree(int n) : size(n), tree(n + 1, 0) {}

    void add(int idx, int value) {
        while (idx <= size) {
            tree[idx] += value;
            idx += idx & -idx;
        }
    }

    int sum(int idx) {
        int res = 0;
        while (idx > 0) {
            res += tree[idx];
            idx -= idx & -idx;
        }
        return res;
    }

    int find_position(int target) {
        int idx = 0, bit_mask = 1;
        while (bit_mask <= size) bit_mask <<= 1;
        for (int step = bit_mask >> 1; step > 0; step >>= 1) {
            if (idx + step <= size && tree[idx + step] < target) {
                target -= tree[idx + step];
                idx += step;
            }
        }
        return idx + 1;
    }
};

int main() {
    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }

    FenwickTree fenwick(N);
    vector<int> result(N);

    for (int i = 1; i <= N; i++) {
        fenwick.add(i, 1);
    }

    for (int i = N - 1; i >= 0; i--) {
        int pos = fenwick.find_position(P[i]);
        result[pos - 1] = i + 1;
        fenwick.add(pos, -1);
    }

    for (int i = 0; i < N; i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;

    return 0;
}