#ifndef BAZINGA_COMPILER_USER_H
#define BAZINGA_COMPILER_USER_H

#include "Value.h"
#include <vector>

class User : public Value
{
public:
    User(Type *ty, const std::string &name = "", unsigned num_ops = 0);
    ~User() = default;

    std::vector<Value *>& get_operands();

    Value *get_operand(unsigned i) const;

    void set_operand(unsigned i, Value *v);
    void add_operand( Value *v);

    unsigned get_num_operand() const;

    void remove_use_of_ops();
    void remove_operands(int index1,int index2);

    void swap_operands(){
        std::swap(operands_[0],operands_[1]);
    }

protected:
    std::vector<Value *> operands_;
    unsigned num_ops_;
};

#endif