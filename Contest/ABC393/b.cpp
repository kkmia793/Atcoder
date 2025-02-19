#include <bits/stdc++.h>
using namespace std;

int main() {
    string S;
    cin >> S;
    int N = S.size();

    int ans = 0;

    for (int j = 1; j < N - 1; j++) {
        if (S[j] != 'B') continue; 

        for (int i = 0; i < j; i++) {
            if (S[i] != 'A') continue;
            int k = 2 * j - i;
            if (k < N && S[k] == 'C') {
                ans++;
            }
        }
    }

    cout << ans << endl;
    return 0;
}