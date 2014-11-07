#include <fstream>


/*
 * @brief Computes the max xor value between L and R.
 */
int getMaxXor(int L, int R)
{
    int ret = 1;
    L ^= R;

    while (L) {
        ret <<= 1;
        L >>= 1;
    }

    return ret - 1;
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
