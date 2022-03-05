#include <iostream>
#include <string>

class Value
{
public:
    Value(std::string str) { name = str; }
    std::string getname() { return name; }

private:
    std::string name;
};

int main()
{
    Value obj("James");
    if (obj.getname() == std::string("Jams"))
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;

    return 0;
}