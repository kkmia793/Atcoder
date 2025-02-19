#include <bits/stdc++.h>
using namespace std;

static const int MAXA = 1000000;

static int freq[MAXA + 1];
static int mulCount[MAXA + 1];
static int bestDiv[MAXA + 1];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> A(N);

    memset(freq, 0, sizeof(freq));
    memset(mulCount, 0, sizeof(mulCount));
    memset(bestDiv, 0, sizeof(bestDiv));

    for(int i = 0; i < N; i++){
        cin >> A[i];
        freq[A[i]]++;
    }

    for(int d = 1; d <= MAXA; d++){
        int count = 0;

        for(int m = d; m <= MAXA; m += d){
            count += freq[m];
        }
        mulCount[d] = count;
    }

    for(int d = MAXA; d >= 1; d--){
        if(mulCount[d] < K) {
            continue;
        }
        for(int x = d; x <= MAXA; x += d){
            if(bestDiv[x] == 0){
                bestDiv[x] = d;
            }
        }
    }

    for(int i = 0; i < N; i++){
        cout << bestDiv[A[i]] << "\n";
    }

    return 0;
}