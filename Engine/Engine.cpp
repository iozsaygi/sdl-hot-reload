#include <iostream>

int main(int argc, char* argv[])
{
    auto argcReference = argc;
    auto argvReference = argv[1];

    std::cout << "Entry point" << argcReference << argvReference;
    return 0;
}
