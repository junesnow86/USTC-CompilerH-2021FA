#include <iostream>
#include <list>
#include <string>
#include <cassert>

class Value
{
public:
    Value()
    {
        setName("Value");
    }
    virtual ~Value() {}
    void setName(std::string n)
    {
        name = n;
    }
    std::string getName()
    {
        return name;
    }
    virtual void print()
    {
        std::cout << "I'm a " << getName() << std::endl;
    }

protected:
    std::string name;
};

class Instruction : public Value
{
public:
    Instruction()
    {
        setName("Instruction");
    }
    virtual void print() override
    {
        std::cout << getName() << std::endl;
    }
};

class UnaryInst : public Instruction
{
public:
    UnaryInst()
    {
        setName("UnaryInst");
    }
};

class BinaryInst : public Instruction
{
public:
    BinaryInst()
    {
        setName("BinaryInst");
    }
};

class BasicBlock : public Value
{
public:
    BasicBlock()
    {
        setName("BasicBlock");
    }
    ~BasicBlock()
    {
        for (auto v : values)
        {
            delete v;
        }
    }
    virtual void print() override
    {
        int unary_cnt = 0, binary_cnt = 0;
        for (auto v : values)
        {
            if (dynamic_cast<UnaryInst *>(v))
            {
                unary_cnt++;
            }
            else if (dynamic_cast<BinaryInst *>(v))
            {
                binary_cnt++;
            }
            else
            {
                std::cerr << "Unspported instruction: " << v->getName() << std::endl;
                abort();
            }
        }
        std::cout << name << ": " << std::endl
                  << binary_cnt << " BinaryInst" << std::endl
                  << unary_cnt << " UnaryInst" << std::endl;
        std::cout << std::endl;
        for (auto v : values)
        {
            std::cout << "  " << v->getName() << std::endl;
        }
    }
    void addValue(Value *v)
    {
        values.push_back(v);
    }

private:
    std::list<Value *> values;
};

int main()
{
    BasicBlock *bb = new BasicBlock();
    bb->addValue(new UnaryInst());
    bb->addValue(new UnaryInst());
    bb->addValue(new BinaryInst());
    bb->addValue(new UnaryInst());
    bb->addValue(new BinaryInst());
    bb->print();
    delete bb;
    return 0;
}