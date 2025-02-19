#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    string S;
    cin >> N >> S;

    vector<int> positions;
    
    for (int i = 0; i < N; ++i) {
        if (S[i] == '1') {
            positions.push_back(i);
        }
    }

    int medianIndex = positions.size() / 2;
    int median = positions[medianIndex];  

    long long operations = 0;
    for (int i = 0; i < positions.size(); ++i) {
        operations += abs(positions[i] - (median - (medianIndex - i)));
    }

    cout << operations << endl;
    return 0;
}