#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char **argv) {
    string a = "int";
    printf ("%d\n", atoi(a));
    std::cout << string(typeof(a)) << std::endl;
    std::cout << std::string(typeid(a).name()) << std::endl;
    return 0;
}
