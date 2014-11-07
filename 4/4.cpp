#include <fstream>
#include <vector>
#include <cassert>


enum Operations {
    SUM = 0,
    DIFF = 1,
    MULT = 2
};

int getTotal(const std::vector<int> &nrs, const std::vector<int> &ops)
{
    int total = nrs.front();

    for (auto it = nrs.cbegin() + 1; it != nrs.cend(); ++it) {
        switch (ops[it - nrs.cbegin() - 1]) {
        case SUM:
            total += *it;
            break;

        case DIFF:
            total -= *it;
            break;

        case MULT:
            total *= *it;
            break;
        }
    }

    return total;
}

void printSol(const std::vector<int> &input, const std::vector<int> &ops,
              std::ofstream &fout)
{
    fout << input.front();
    for (auto it = input.cbegin() + 1; it != input.cend(); ++it) {
        switch (ops[it - input.cbegin() - 1]) {
        case SUM:
            fout << " + ";
            break;

        case DIFF:
            fout << " - ";
            break;

        case MULT:
            fout << " * ";
            break;
        }
        fout << *it;
    }

    fout << " = ";
    for (std::size_t i = 0; i < ops.size(); ++i)
        fout << "(";

    fout << input.front();
    for (auto it = input.cbegin() + 1; it != input.cend(); ++it) {
        switch (ops[it - input.cbegin() - 1]) {
        case SUM:
            fout << " + ";
            break;

        case DIFF:
            fout << " - ";
            break;

        case MULT:
            fout << " * ";
            break;
        }
        fout << *it;
        fout << ")";
    }

    fout << " = " << getTotal(input, ops) << std::endl;
}

void recursCheck(const std::vector<int> &input, std::vector<int> &ops, int pos,
                 std::ofstream &fout)
{
    if (static_cast<std::size_t>(pos) == input.size() - 1) {
        if (getTotal(input, ops) % 101 == 0) {
            printSol(input, ops, fout);
            exit(0);
        }
        return;
    }

    for (int i = 0; i < 3; ++i) {
        ops[pos] = i;
        recursCheck(input, ops, pos + 1, fout);
    }
}


void checkSol(const std::vector<int> &input, std::ofstream &fout)
{
    std::vector<int> ops(input.size() - 1);
    recursCheck(input, ops, 0, fout);
}


int main()
{
    std::ifstream fin("Input4.txt");
    std::ofstream fout("Output4.txt");

    int N;
    fin >> N;

    std::vector<int> v(N);
    for (int i = 0; i < N; ++i)
        fin >> v[i];

    checkSol(v, fout);
    return 0;
}
