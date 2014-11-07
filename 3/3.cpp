#include <fstream>


/*
 * @brief Computes the max xor value between L and R.
 */
int getMaxXor(int L, int R)
{
    int max = L ^ L;
    for (int i = L; i <= R; ++i)
        for (int j = L + 1; j <= R; ++j)
            if ((i ^ j) > max)
                max = i ^ j;

    return max;
}


int main()
{
    std::ifstream fin("Input3.txt");
    std::ofstream fout("Output3.txt");

    int L, R;
    fin >> L >> R;

    fout << getMaxXor(L, R) << std::endl;
    return 0;
}
