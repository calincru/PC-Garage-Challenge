#include <stack>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>


using namespace std;
using AreaMatrix = vector<vector<char>>;


ofstream& operator<<(ofstream& strim, AreaMatrix& area);
void generateRandomMaze(AreaMatrix& area);

int main()
{
    ifstream fin("Input10.txt");
    ofstream fout("Output10.txt");

    int i, j;
    fin >> i >> j;

    vector<vector<char>> area(i, vector<char>(j, ' '));
    srand(time(NULL));
    for (auto& line : area)
        for (auto& caracter : line)
            caracter = (rand() %  2) ? ' ' : '#';

    generateRandomMaze(area);
    fout << area;

    return 0;
}

/*
 * @brief Overload the << operator for printing.
 */
ofstream& operator<<(ofstream& strim, AreaMatrix& area)
{
    for (auto k = 0ul; k <= area[0].size(); k++)
        strim << '#';
    strim << '\n';

    for (auto it = area.cbegin(); it != area.cend(); ++it) {
        for (auto jt = it->cbegin(); jt != it->cend(); ++jt)
            strim << *jt;
        if (it != area.cend() - 1)
            strim << "#";
        strim << "\n";
    }

    for (auto k = 0ul; k <= area[0].size(); k++)
        strim << '#';

    return strim;
}

/*
 * @brief Overload the += operator for pairs to easiely sum up pairs.
 */
pair<int, int> &operator+=(pair<int, int> &ret, pair<int, int> &x)
{
    ret.first += x.first;
    ret.second += x.second;
    return ret;
}

/*
 * @brief Randomly find a path using a modified BFS algorithm from the first
 * left square to the last, right square.
 */
void generateRandomMaze(AreaMatrix& area)
{
    queue<pair<int, int>> q;
    vector<vector<bool>> wasHere(area.size(),
                                 vector<bool>(area[0].size(), false));
    vector<vector<pair<int, int>>> res(area.size(),
                                       vector<pair<int, int>>(area[0].size()));

    q.push(make_pair(0, 0));
    pair<int, int> exit = make_pair(area.size() - 1, area[0].size() - 1);
    vector<pair<int, int>> directions = { make_pair(1, 0),
                                          make_pair(-1, 0),
                                          make_pair(0, 1),
                                          make_pair(0, -1) };

    while (!q.empty()) {
        auto curPos = q.front();
        if (curPos == exit)
            break;

        q.pop();
        random_shuffle(directions.begin(), directions.end());
        for (auto& direction: directions) {
            auto newPos = curPos;
            newPos += direction;
            if (newPos.first >= area.size() || newPos.second >= area[0].size())
                continue;
            if (newPos.first < 0 || newPos.second < 0)
                continue;
            if (wasHere[newPos.first][newPos.second])
                continue;

            q.push(newPos);
            res[newPos.first][newPos.second] = curPos;
            wasHere[newPos.first][newPos.second] = true;
        }
    }

    area[0][0] = 'K';
    for (pair<int, int> p = exit; p != make_pair(0, 0);
         p = res[p.first][p.second]) {
        area[p.first][p.second] = 'K';
        if (p.first && area[p.first - 1][p.second] == ' ')
            area[p.first - 1][p.second] = '#';

        if (p.second && area[p.first][p.second - 1] == ' ')
            area[p.first][p.second - 1] = '#';

        if (p.first < area.size() - 1 && area[p.first + 1][p.second] == ' ')
            area[p.first + 1][p.second] = '#';

        if (p.second < area[0].size() - 1 && area[p.first][p.second + 1] == ' ')
            area[p.first][p.second + 1] = '#';
    }

    for (auto &line : area)
        for (auto &caracter : line)
            if (caracter == 'K')
                caracter = ' ';
}
