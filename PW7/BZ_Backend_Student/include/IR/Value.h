#ifndef BAZINGA_COMPILER_VALUE_H
#define BAZINGA_COMPILER_VALUE_H

#include <string>
#include <list>
#include <iostream>

class Type;
class Value;

struct Use
{
    Value *val_;
    unsigned arg_no_;
    Use(Value *val, unsigned no) : val_(val), arg_no_(no) {}

    friend bool operator==(const Use & lhs, const Use & rhs){
        return lhs.val_ == rhs.val_ && lhs.arg_no_ == rhs.arg_no_;
    }
};

class Value
{
public:
    explicit Value(Type *ty, const std::string &name = "");
    ~Value() = default;


    Type *get_type() const { return type_; }

    std::list<Use> &get_use_list() { return use_list_; }

    void add_use(Value *val, unsigned arg_no = 0);

    bool set_name(std::string name) { 
        if (name_ == "")
        {
            name_=name;
            return true;
        }   
        return false; 
    }
    std::string get_name() const;

    void replace_all_use_with(Value *new_val);
    void remove_use(Value *val);

    virtual std::string print() { return ""; }
protected:
    Type *type_;
    std::list<Use> use_list_;
    std::string name_;
};

#endif
