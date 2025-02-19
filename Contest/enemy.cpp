#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N; // 敵の数
    cin >> N;

    vector<long long> ex(N), ey(N), R(N); // 敵の座標と攻撃範囲
    for (int i = 0; i < N; ++i) {
        cin >> ex[i] >> ey[i] >> R[i];
    }

    long long px, py; // プレイヤーの座標
    cin >> px >> py;

    // プレイヤーが攻撃範囲内かどうかを判定
    for (int i = 0; i < N; ++i) {
        long long dx = ex[i] - px;
        long long dy = ey[i] - py;

        // 距離の二乗と半径の二乗を比較
        if (dx * dx + dy * dy <= R[i] * R[i]) {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;

    return 0;
}