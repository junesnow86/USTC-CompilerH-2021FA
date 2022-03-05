#include <iostream>
#include <vector>
#include <algorithm>

enum op {
    add,
    sub
};

struct Test {
    int id;
    op opcode;
    int lvalue;
    int rvalue;
    bool operator== (const Test &other) const {
        if (opcode != other.opcode) return false;
        else if (lvalue != other.lvalue) return false;
        else if (rvalue != other.rvalue) return false;
        else return true;
    }
};

int main() {
    struct Test test1;
    test1.id = 1;
    test1.opcode = op::add;
    test1.lvalue = 1;
    test1.rvalue = 2;
    struct Test test2;
    test2.id = 2;
    test2.opcode = op::add;
    test2.lvalue = 1;
    test2.rvalue = 3;
    std::cout << (test1 == test2) << std::endl;
    std::vector<Test> testvec;
    testvec.push_back(test1);
    testvec.push_back(test2);
    auto iter = std::find(testvec.begin(),testvec.end(),test1);
    std::cout << iter-testvec.begin() << std::endl;
    return 0;
}