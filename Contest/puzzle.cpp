#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// マス間の上下左右の移動を定義
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int n = 15 , m = 15;

// 探索したことのある場所か」を管理する配列
vector<vector<bool>> visited;

// 深さ優先探索の実装
void dfs(vector<vector<int>>& G, int x0, int y0){

    // 最初に訪問する地点をスタックに入れる
    stack<pair<int,int>> st;
    st.push({x0, y0});

    while(!st.empty()){
        auto [x,y] = st.top();
        st.pop();

        // 4方向への移動を試す
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // 新たなマスが、場外ならダメ
            if (nx < 0 || nx >=  n|| ny < 0 || ny >= m) continue;
            // 新たなマスが、島じゃないならダメ
            if (G[nx][ny] == 0) continue;
            // 新たなマスが、訪問済みならダメ
            if (visited[nx][ny]) continue;

            // 新たなマスへ訪問する
            st.push({nx, ny});
            visited[nx][ny] = true;
        }

    }
}

int main(void){
    visited.assign(n, vector<bool>(m, false));
    vector<vector<int>> G(n, vector<int>(m));
    for(int i = 0; i < n; i++){
        for(int j=0;j<m;j++){
                cin >> G[i][j];
        }
    }

    int ans = 0;

    // すべての迷路のマスに対して、幅優先探索を試みる
    for(int x = 0; x < n; x++){
        for(int y = 0; y < m; y++){
            // 島じゃないならしない
            if(G[x][y] == 0) continue;

            // 訪問済みならしない
            if(visited[x][y]) continue;

            // bfs(G, x, y);
            //深さ優先探索
            dfs(G, x, y);

            // DFSが1回終わったら、答えの島の数を1つ増やす
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}

