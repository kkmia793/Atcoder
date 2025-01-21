#include <iostream>
#include <set>
using namespace std;

int main() {
    long long n;
    int m, q;
    cin >> n >> m;

    set<long long> reserved; 
    for (int i = 0; i < m; i++) {
        long long a;
        cin >> a;
        reserved.insert(a);
    }

    cin >> q;

    for (int i = 0; i < q; i++) {
        long long l, r;
        cin >> l >> r;

        auto it = reserved.lower_bound(l);
        if (it == reserved.end() || *it > r) {
            cout << l << endl;
        } else {
            bool found = false;
            for (long long j = l; j <= r; j++) {
                if (reserved.find(j) == reserved.end()) {
                    cout << j << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << -1 << endl;
            }
        }
    }

    return 0;
}