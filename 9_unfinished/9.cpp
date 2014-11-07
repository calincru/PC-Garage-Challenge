#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


/*
 * @brief Checks validity of the given puzzle.
 * @return true if the puzzle can be solved.
 */
bool checkValidity(const std::vector<std::vector<int>> &mat)
{
    int count_invs = 0;
    int blank_square_row = -1;

    for (auto it = mat.cbegin(); it != mat.cend(); ++it)
        for (auto jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
            if (*jt < *(jt - 1))
                ++count_invs;
            if (*jt == 0)
                blank_square_row = it - mat.cbegin();
        }

    // If the board size is odd, then the puzzle can be solved
    // if and only if the nr of inversions is even.
    //
    // If the board size is even and the sum between the nr of
    // inversions and the row of the blank square is even, then
    // this board cannot lead to the goal board.
    return mat.size() % 2 ? count_invs % 2 == 0 :
                            (count_invs + blank_square_row) % 2 == 1;
}

/*
 * @brief Computes the manhattan distance used as a heuristic in the A*
 * algorithm.
 */
int manhattanDist(const std::vector<std::vector<int>> &mat)
{
    std::vector<int> linear;
    for (auto &row : mat)
        for (auto &i : row)
            linear.push_back(i);

    int count = 0;
    for (auto it = linear.cbegin(); it != linear.cend(); ++it) {
        if (!*it)
            continue;

        int i = (it - linear.cbegin())/mat.size();
        int j = it - linear.cbegin() - i*mat.size();
        int goalRow = (*it - 1)/mat.size();
        int goalColumn = *it - goalRow*mat.size() - 1;

        count += (abs(goalRow - i) + abs(goalColumn - j));
    }

    return count;
}

struct BinaryPredicate
{
    bool operator()(const std::vector<std::vector<int>> &first,
                    const std::vector<std::vector<int>> &second) {
        return manhattanDist(first) > manhattanDist(second);
    }
};

/*
 * @brief: Solve the problem using the A* algorithm.
 */
int solve(std::vector<std::vector<int>> &mat)
{
    std::priority_queue< std::vector<std::vector<int>>,
                         std::vector<std::vector<std::vector<int>>>,
                         BinaryPredicate > pq;
    pq.push(mat);

    int movesSoFar = 0;
    std::vector<std::vector<int>> previous;

    // TODO
    while (1) {
        std::vector<std::vector<int>> curr = pq.top();
        // ..
    }

    return movesSoFar;
}

int main()
{
    std::ifstream fin("Input9.txt");
    std::ofstream fout("Output9.txt");

    int K;
    fin >> K;

    std::vector<std::vector<int>> mat(K, std::vector<int>(K));
    for (auto &row : mat)
        for (auto &i : row)
            fin >> i;

    if (!checkValidity(mat)) {
        fout << "Imposibil";
        return 0;
    }

    std::cout << solve(mat) << std::endl;
    return 0;
}
