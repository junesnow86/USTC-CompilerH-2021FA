#include <iostream>
#include <list>
#include <string>
#include <cassert>

class Value
{
public:
    virtual ~Value() {}
};

class BasicBlock : public Value
{
};

/*
class Instruction : public Value
{
};
*/

class Instruction
{
public:
    int flag;
    //virtual ~Instruction() {}
};

class UnaryInst : public Instruction
{
};

class BinaryInst : public Instruction
{
};

int main()
{
    Value *v = new BasicBlock();
    Instruction *inst = new BinaryInst();
    std::cout << typeid(v).name() << std::endl;
    std::cout << typeid(*v).name() << std::endl;
    std::cout << typeid(inst).name() << std::endl;
    std::cout << typeid(*inst).name() << std::endl;
    return 0;
}