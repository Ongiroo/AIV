#include <iostream>
#include <functional>

int main()
{
    [out = std::ref(std::cout << "AIV")]() {out.get() << "Testing \n";}();
    return 0;
}