#include <iostream>
#include <vector>
#include <queue>    // priority_queue
#include <cmath>    // abs()
#include <utility>  // pair

using namespace std;

int H, W;
vector<string> grid;
pair<int, int> start, goal;
vector<vector<int>> directionV = {{1, 0}, {-1, 0}};
vector<vector<int>> directionH = {{0, 1}, {0, -1}};

struct Node
{
  int x, y, cost, heuristic, lastMove;
  bool operator<(const Node &other) const
  {
    return cost + heuristic > other.cost + other.heuristic; // 経路コスト（ 実コスト＋ 推定コスト ）
  }
};

int heuristic(int x, int y, int gx, int gy)
{
  return abs(x - gx) + abs(y - gy); // マンハッタン距離
}

int a_star()
{
  priority_queue<Node> pq; // 優先度付きキュー（総コストが最小になるように）
  vector<vector<vector<int>>> visited(H, vector<vector<int>>(W, vector<int>(3, 0)));
  pq.push({start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second), 0});

  while (!pq.empty())
  {
    Node current = pq.top();
    pq.pop();

    if (current.x == goal.first && current.y == goal.second)
    {
      return current.cost;
    }

    if (visited[current.x][current.y][current.lastMove])
      continue;
    visited[current.x][current.y][current.lastMove] = 1;

    // 移動に制限があるタイプ（縦移動したら横移動。横移動したら縦移動）
    if (current.lastMove != 1)
    {
      for (auto &dir : directionV)
      {
        int nx = current.x + dir[0];
        int ny = current.y + dir[1];
        if (nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] != '#' && !visited[nx][ny][1])
        {
          pq.push({nx, ny, current.cost + 1, heuristic(nx, ny, goal.first, goal.second), 1});
        }
      }
    }

    if (current.lastMove != 2)
    {
      for (auto &dir : directionH)
      {
        int nx = current.x + dir[0];
        int ny = current.y + dir[1];
        if (nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] != '#' && !visited[nx][ny][2])
        {
          pq.push({nx, ny, current.cost + 1, heuristic(nx, ny, goal.first, goal.second), 2});
        }
      }
    }
  }

  return -1;
}

int main()
{
  cin >> H >> W;
  grid.resize(H);
  for (int i = 0; i < H; i++)
  {
    cin >> grid[i];
    for (int j = 0; j < W; j++)
    {
      if (grid[i][j] == 'S')
        start = {i, j};
      if (grid[i][j] == 'G')
        goal = {i, j};
    }
  }

  cout << a_star() << endl;
  return 0;
}

/*
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <tuple>

int heuristic(int x1, int y1, int x2, int y2)
{
  return std::abs(x1 - x2) + std::abs(y1 - y2);
}

int bfs(const std::vector<std::string> &dungeon, int startX, int startY, int goalX, int goalY)
{
  int n = dungeon.size();
  int m = dungeon[0].size();
  std::vector<std::vector<int>> dist(n, std::vector<int>(m, -1));
  std::queue<std::pair<int, int>> q;

  q.push({startX, startY});
  dist[startX][startY] = 0;

  while (!q.empty())
  {
    auto [x, y] = q.front();
    q.pop();

    if (x == goalX && y == goalY)
    {
      return dist[x][y];
    }

    for (auto [dx, dy] : std::vector<std::pair<int, int>>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}})
    {
      int nx = x + dx, ny = y + dy;
      if (nx >= 0 && nx < n && ny >= 0 && ny < m && dungeon[nx][ny] != '#' && dist[nx][ny] == -1)
      {
        dist[nx][ny] = dist[x][y] + 1;
        q.push({nx, ny});
      }
    }
  }
  return -1;
}

void generateDungeon(int k)
{
  int n = 50, m = 50;
  std::vector<std::string> dungeon(n, std::string(m, '#'));
  srand(static_cast<unsigned>(time(0)));
  int startX = rand() % n;
  int startY = rand() % m;
  dungeon[startX][startY] = 'S';

  int goalX = -1, goalY = -1;

  if (k <= 50)
  {
    for (int i = 0; i < n && goalX == -1; ++i)
    {
      for (int j = 0; j < m; ++j)
      {
        if (heuristic(startX, startY, i, j) == k && dungeon[i][j] == '#')
        {
          goalX = i;
          goalY = j;
          break;
        }
      }
    }
    if (goalX != -1 && goalY != -1)
    {
      dungeon[goalX][goalY] = 'G';
      using Node = std::tuple<int, int, int, int>;
      std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
      openList.push({0, startX, startY, 0});
      std::vector<std::vector<int>> distance(n, std::vector<int>(m, INT_MAX));
      distance[startX][startY] = 0;
      while (!openList.empty())
      {
        auto [currentCost, x, y, steps] = openList.top();
        openList.pop();
        if (x == goalX && y == goalY)
        {
          break;
        }
        for (auto [dx, dy] : std::vector<std::pair<int, int>>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}})
        {
          int nx = x + dx, ny = y + dy;
          if (nx >= 0 && nx < n && ny >= 0 && ny < m && dungeon[nx][ny] == '#')
          {
            dungeon[nx][ny] = '.';
            distance[nx][ny] = steps + 1;
            int heuristicValue = heuristic(nx, ny, goalX, goalY);
            openList.push({steps + 1 + heuristicValue, nx, ny, steps + 1});
          }
        }
      }
    }
  }
  else
  {
    int currentX = startX, currentY = startY;
    int steps = 0;

    while (steps < k)
    {
      if (steps % 2 == 0)
      {
        if (currentY + 1 < m)
        {
          currentY++;
        }
        else if (currentX + 1 < n)
        {
          currentX++;
        }
        else
        {
          break;
        }
      }
      else
      {
        if (currentY - 1 >= 0)
        {
          currentY--;
        }
        else if (currentX + 1 < n)
        {
          currentX++;
        }
        else
        {
          break;
        }
      }
      dungeon[currentX][currentY] = '.';
      steps++;
    }

    dungeon[currentX][currentY] = 'G';
    goalX = currentX;
    goalY = currentY;
  }

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if (dungeon[i][j] == '#' && rand() % 5 == 0)
      {
        dungeon[i][j] = '.';
      }
    }
  }

  int actualDistance = bfs(dungeon, startX, startY, goalX, goalY);
  if (actualDistance != k)
  {
    return;
  }

  std::cout << n << " " << m << "\n";
  for (const auto &row : dungeon)
  {
    std::cout << row << "\n";
  }
}

int main()
{
  int k;
  std::cin >> k;
  generateDungeon(k);
  return 0;
}

*/