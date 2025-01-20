/*ヘビの待ち行列があります。最初、列は空です。

クエリが 
Q 個与えられるので、与えられた順に処理してください。クエリは以下の 
3 種類です。

タイプ 1 : 1 l の形式で与えられる。長さ l のヘビが列の末尾に追加される。このとき追加するヘビの頭の位置は、元の列が空の場合は座標 0、そうでない場合は最後尾のヘビの頭の座標に最後尾のヘビの長さを加えた座標となる。
タイプ 2 : 2 の形式で与えられる。列の先頭にいるヘビが列から抜ける。このとき、列が空でないことは保証される。抜けたヘビの長さをm として、列に残っている全てのヘビの頭の座標が m だけ減少する。
タイプ 3 : 3 k の形式で与えられる。列の先頭から数えて k 番目にいるヘビの頭の座標を出力せよ。このとき、列には少なくとも k 匹のヘビがいることが保証される。

*/

/* 入力
入力は以下の形式で標準入力から与えられる。

Q
query 1
query 2
⋮
query Q
 
1 l
2
3 k
*/

/* 出力

タイプ 3 のクエリの個数を 
q として、
q 行出力せよ。
i 行目には、i 個目のタイプ 3 のクエリに対する答えを出力せよ。

*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    // 各ヘビの頭の位置を記録する配列
    long long snake_positions[303300];
    int head_index = 0;  // 列の先頭を指すインデックス
    int tail_index = 0;  // 列の末尾を指すインデックス
    int query_count;     // クエリの数
    cin >> query_count;

    while (query_count--)
    {
        int query_type, value;
        cin >> query_type;
        
        if (query_type == 1) // タイプ 1: ヘビを列の末尾に追加
        {
            cin >> value; 
            tail_index++;
            snake_positions[tail_index] = snake_positions[tail_index - 1] + value;
        }
        else if (query_type == 2) // タイプ 2: 列の先頭のヘビを削除
        {
            ++head_index;
        }
        else if (query_type == 3) // タイプ 3: 指定されたヘビの頭の位置を出力
        {
            cin >> value; 
            cout << snake_positions[head_index + value - 1] - snake_positions[head_index] << endl;
        }
    }

    return 0;
}



