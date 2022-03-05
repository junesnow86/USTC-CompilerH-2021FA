#ifndef BAZINGA_COMPILER_GLOBALVARIABLE_H
#define BAZINGA_COMPILER_GLOBALVARIABLE_H

#include "Module.h"
#include "User.h"
#include "Constant.h"

class GlobalVariable : public User
{
private:
    bool is_const_ ;
    Constant* init_val_;
    std::vector<int> _flatten_init_val;
    GlobalVariable(std::string name, Module *m, Type* ty, bool is_const, Constant* init = nullptr);
public:
    static GlobalVariable *create(std::string name, Module *m, Type* ty, bool is_const, 
                                Constant* init );

    Constant *get_init() { return init_val_; }
    bool is_const() const { return is_const_; }
    void setFlattenInit(const std::vector<int> &i) { _flatten_init_val = i; }
    std::vector<int> getFlattenInit() const { return _flatten_init_val; }
    std::string print();
};
#endif
