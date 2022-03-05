#ifndef BAZINGA_COMPILER_TYPE_H
#define BAZINGA_COMPILER_TYPE_H

#include <vector>
#include <iostream>

class Module;
class IntegerType;
class FunctionType;
class ArrayType;
class PointerType;
class FloatType;

class Type
{
public:
    enum TypeID {
        VoidTyID,
        LabelTyID,
        IntegerTy1ID,
        IntegerTy32ID,
        FunctionTyID,
        ArrayTyID,
        PointerTyID,
        FloatTyID
    };

    explicit Type(TypeID tid, Module *m);
    ~Type() = default;

    TypeID get_type_id() const { return tid_; }

    bool is_void_type() const { return get_type_id() == VoidTyID; }
    
    bool is_label_type() const { return get_type_id() == LabelTyID; }

    bool is_integer_type() const { return get_type_id() == IntegerTy32ID || get_type_id() == IntegerTy1ID; }
        
    bool is_function_type() const { return get_type_id() == FunctionTyID; }

    bool is_array_type() const { return get_type_id() == ArrayTyID; }

    bool is_pointer_type() const { return get_type_id() == PointerTyID; }

    bool is_float_type() const { return get_type_id() == FloatTyID; }

    bool is_int32_type() const { return get_type_id() == IntegerTy32ID; }

    bool is_int1_type() const { return get_type_id() == IntegerTy1ID; }

    static bool is_eq_type(Type *ty1, Type *ty2);

    static Type *get_void_type(Module *m);

    static Type *get_label_type(Module *m);

    static IntegerType *get_int1_type(Module *m);

    static IntegerType *get_int32_type(Module *m);

    static PointerType *get_int32_ptr_type(Module *m);

    static FloatType *get_float_type(Module *m);

    static PointerType *get_float_ptr_type(Module *m);

    static PointerType *get_pointer_type(Type *contained);

    static ArrayType *get_array_type(Type *contained, unsigned num_elements);

    Type *get_pointer_element_type();

    Type *get_array_element_type();

    int get_size(bool extended=true);
    
    Module *get_module();

    std::string print();



private:
    TypeID tid_;
    Module *m_;
    virtual void _t(){};
};

class IntegerType : public Type {
public:
    explicit IntegerType(unsigned num_bits ,Module *m);

    static IntegerType *get(unsigned num_bits, Module *m );

    unsigned get_num_bits();
private:
    unsigned num_bits_;
};

class FunctionType : public Type {
public:
    FunctionType(Type *result, std::vector<Type *> params);

    static bool is_valid_return_type(Type *ty);
    static bool is_valid_argument_type(Type *ty);

    static FunctionType *get(Type *result,
                            std::vector<Type*> params);

    unsigned get_num_of_args() const;

    Type *get_param_type(unsigned i) const;
    std::vector<Type *>::iterator param_begin() { return args_.begin(); }
    std::vector<Type *>::iterator param_end() { return args_.end(); }
    Type *get_return_type() const;
private:
    Type *result_;
    std::vector<Type *> args_;
};

class ArrayType : public Type {
public:
    ArrayType(Type *contained, unsigned num_elements);

    static bool is_valid_element_type(Type *ty);

    static ArrayType *get(Type *contained, unsigned num_elements);

    Type *get_element_type() const { return contained_; }
    unsigned get_num_of_elements() const { return num_elements_; }

private:
    Type *contained_;
    unsigned num_elements_;
};

class PointerType : public Type {
public:
    PointerType(Type *contained);
    Type *get_element_type() const { return contained_; }

    static PointerType *get(Type *contained);

private:
    Type *contained_;
};

class FloatType : public Type {
public:
    FloatType (Module *m);
    static FloatType *get(Module *m);
private:
};

#endif