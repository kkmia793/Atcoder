#include <bits/stdc++.h> 
using namespace std;

// u -> v と v -> u の個数を管理する構造体
struct EdgeInfo {
    long long forwardCount = 0;  // u -> v
    long long backwardCount = 0; // v -> u
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    long long selfLoopCount = 0; // 自己ループ（u == v）の数

    unordered_map<long long, EdgeInfo> mp;
    mp.reserve(M); // メモリ確保（ハッシュ衝突減らす）

    // (a, b) を一意な数値に変換（a < b を前提）
    auto encodePair = [&](int a, int b) {
        return (static_cast<long long>(a) << 20) + b;
    };

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;

        if (u == v) {
            selfLoopCount++; // 自己ループならカウント
        } else {
            int x = min(u, v);
            int y = max(u, v);
            long long key = encodePair(x, y);

            if (u < v) mp[key].forwardCount++; // u -> v
            else mp[key].backwardCount++;      // v -> u
        }
    }

    long long ans = selfLoopCount; // まず自己ループぶん加算

    for (const auto& [_, info] : mp) {
        long long c1 = info.forwardCount;
        long long c2 = info.backwardCount;

        if (c1 > 0 && c2 > 0) ans += (c1 + c2 - 1); // 両方向あるならその分
        else ans += (c1 + c2 - 1); // 片方向だけならその分
    }

    cout << ans << "\n";
    return 0;
}