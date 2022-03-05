#ifndef BAZINGA_COMPILER_CONSTANT_H
#define BAZINGA_COMPILER_CONSTANT_H
#include "User.h"
#include "Value.h"
#include "Type.h"

class Constant : public User
{
private:
public:
    Constant(Type *ty, const std::string &name = "", unsigned num_ops = 0)
        : User(ty, name, num_ops) {}
    ~Constant() = default;
};

class ConstantInt : public Constant
{
private:
    int value_;
    ConstantInt(Type* ty,int val) 
        : Constant(ty,"",0),value_(val) {}
public:
    
    static int get_value(ConstantInt *const_val) { return const_val->value_; }
    int get_value() const { return value_; }
    static ConstantInt *get(int val, Module *m);
    static ConstantInt *get(bool val, Module *m);
    std::string print() override;
};

class ConstantArray : public Constant
{
private:
    std::vector<Constant*> const_array;

    ConstantArray(ArrayType *ty, const std::vector<Constant*> &val);
public:
    
    ~ConstantArray()=default;

    Constant* get_element_value(int index);

    unsigned get_size_of_array() { return const_array.size(); } 

    static ConstantArray *get(ArrayType *ty, const std::vector<Constant*> &val);

    std::string print() override;

    static std::vector<Constant *> IntegerList2Constant(const std::vector<int> &dim, const std::vector<int> &init, Module *m) {
        std::vector<Constant *> st;
        std::vector<Constant *> ost;
        Type *ty = Type::get_int32_type(m);
        for (int i : init) {
            ost.emplace_back(ConstantInt::get(i, m));
        }
        int num_group = init.size();
        for (int i = (int)dim.size() - 1; i > 0; --i) {
            num_group /= dim[i];
            int offset = 0;
            ty = ArrayType::get(ty, dim[i]);
            for (int gp = 0; gp < num_group; ++gp) {
                std::vector<Constant *> arr;
                for (int j = 0; j < dim[i]; ++j) {
                    arr.push_back(ost[offset + j]);
                }
                st.push_back(ConstantArray::get(dynamic_cast<ArrayType *>(ty), arr));
                offset += dim[i];
            }
            ost = st;
            st.clear();
        }
        return ost;
    };
};

class ConstantZero : public Constant 
{
private:
    explicit ConstantZero(Type *ty)
        : Constant(ty,"",0) {}
public:
    static ConstantZero *get(Type *ty, Module *m);
    std::string print() override;
};

class ConstantFP : public Constant 
{
private:
    float val_;
    ConstantFP(Type *ty, float val)
        : Constant(ty,"",0), val_(val) {}
public:
    static ConstantFP *get(float val, Module *m);
    float get_value() const { return val_; }
    std::string print() override;
};

#endif //BAZINGA_COMPILER_CONSTANT_H
