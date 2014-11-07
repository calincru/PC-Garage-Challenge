#include <iostream>


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
    int L, R;
    std::cin >> L >> R;

    std::cout << getMaxXor(L, R) << std::endl;
    return 0;
}
