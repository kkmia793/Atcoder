#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;
int main(void)
{
    int n;

    cin >> n;

    vector<int> a(n);

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int sum = 0;
    int head = 0;

    for(int i = 1; i < n; ++i)
    {
        for(int j = head; j < i; j++)
        {
            if(a[j]*2 > a[i])
            {
                head = j;
                sum += head;
                break;
            }
        }
    }

    cout << sum << endl;

    return 0;

}