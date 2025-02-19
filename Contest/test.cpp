#include <bits/stdc++.h>
using namespace std;

// A[i], R, X が最大 1e9 程度想定
// N, Q は最大 2e5 かもしれない
// この実装は最悪計算量が大きく、2秒で通らないケースも多い点に注意

static const int MAXN = 200000;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<long long> A(N);
    for(int i=0; i<N; i++){
        cin >> A[i];
    }

    // pos[v] = { index1, index2, ... } (昇順)
    // 値が最大1e9なので、unordered_map<long long, vector<int>> を使う
    unordered_map<long long, vector<int>> pos;
    pos.reserve(N);
    pos.max_load_factor(0.7f);

    // A[i] を pos に登録
    for(int i=0; i<N; i++){
        pos[A[i]].push_back(i);
    }
    // ソート
    for(auto &pr : pos){
        auto &vec = pr.second;
        sort(vec.begin(), vec.end());
    }

    // distinct values をソートしておく (R=1 用)
    // また、freq[v] = pos[v].size()
    vector<long long> distinctVals;
    distinctVals.reserve(pos.size());
    for(const auto &pr : pos){
        distinctVals.push_back(pr.first);
    }
    sort(distinctVals.begin(), distinctVals.end());

    // freq[i] = distinctVals[i] の出現回数
    vector<long long> freq(distinctVals.size());
    for(int i=0; i<(int)distinctVals.size(); i++){
        freq[i] = pos[ distinctVals[i] ].size();
    }
    // prefixMax[i] = distinctVals[0..i] の freq の最大値
    //  -> R=1 で X 以上の値を無視したいときに使う
    vector<long long> prefixMax(distinctVals.size());
    {
        long long curMax = 0;
        for(int i=0; i<(int)distinctVals.size(); i++){
            curMax = max(curMax, freq[i]);
            prefixMax[i] = curMax;
        }
    }

    while(Q--){
        long long R, X;
        cin >> R >> X;

        // 特別ケース: R=1
        if(R == 1){
            // 「Aの要素のうち X 以下の値」を全部同じ値に揃えた等比数列が最大長をとるには、
            // その値が最も多く出現するものを選べばよい
            // => X以下のdistinctValsの範囲で freq が最大のものを探す
            //    distinctValsは昇順なので、 X以下の範囲を2分探索
            int idx = int(std::upper_bound(distinctVals.begin(), distinctVals.end(), X)
                          - distinctVals.begin());
            if(idx == 0){
                // X より小さい値が存在しない => 部分列を作れない => 長さ0
                // (問題設定上, min(A) <= X と書いてあるなら 0 にはならないはずだが一応)
                cout << 0 << "\n";
            } else {
                // prefixMax[idx-1] が X以下の値の中で最大のfreq
                // そこに+0(連続で同じ値を取るだけ) だが、実際は "部分列" なので
                // freq分すべて取れる => それが最大長
                cout << prefixMax[idx-1] << "\n";
            }
            continue;
        }

        // R>1 の場合

        // 全ての可能な開始点を試す (厳密)
        // 最悪 O(N * (log_R(X)) * logN) で非常に大きくなる
        long long answer = 0;

        for(int startIndex=0; startIndex<N; startIndex++){
            long long v = A[startIndex];
            if(v > X) {
                // この要素自体が X超 => チェーンを作れない
                continue;
            }
            // チェーン構築
            long long length = 1;       // startIndex の要素を使う
            long long curIndex = startIndex;
            long long p = v;

            // 次の値を探していく
            while(true){
                // 次の値 p*R (オーバーフロー防止)
                if(p > LLONG_MAX / R) break; 
                long long nxtVal = p * R;
                if(nxtVal > X) break;

                // nxtVal が配列に存在しないなら終わり
                auto it = pos.find(nxtVal);
                if(it == pos.end()){
                    break;
                }
                auto &vec = it->second;

                // 二分探索: vec の中で curIndex より大きい最小の位置
                // upper_bound(vec.begin(), vec.end(), curIndex)
                auto ub = std::upper_bound(vec.begin(), vec.end(), (int)curIndex);
                if(ub == vec.end()){
                    // 見つからない
                    break;
                }
                // 見つかった次のインデックス
                int nxtIndex = *ub;

                // 更新
                length++;
                curIndex = nxtIndex;
                p = nxtVal;
            }

            answer = max(answer, length);
        }

        cout << answer << "\n";
    }

    return 0;
}