#include <utility>

int main()
{
    int x =2;
    int k = 4;
    auto y = std::exchange(x, std::string("stuff"));

    int i = 3;
    int j = 4;
    std::swap(i, 4);
    // i ==4
    // j == 3
}