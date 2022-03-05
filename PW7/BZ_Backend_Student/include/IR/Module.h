#ifndef BAZINGA_COMPILER_MODULE_H
#define BAZINGA_COMPILER_MODULE_H

#include <string>
#include <list>
#include <map>

#include "Type.h"
#include "GlobalVariable.h"
#include "Value.h"
#include "Function.h"
#include "Instruction.h"

class GlobalVariable;

class Module
{
public:
    explicit Module(std::string name);
    ~Module();
    
    Type *get_void_type();
    Type *get_label_type();
    IntegerType *get_int1_type();
    IntegerType *get_int32_type();
    PointerType *get_int32_ptr_type();
    FloatType *get_float_type();
    PointerType *get_float_ptr_type();

    PointerType *get_pointer_type(Type *contained);
    ArrayType *get_array_type(Type *contained, unsigned num_elements);

    void add_function(Function *f);
    std::list<Function* > get_functions();
    void add_global_variable(GlobalVariable* g);
    void delete_global_variable(GlobalVariable* g){ global_list_.remove(g); }
    std::list<GlobalVariable *> get_global_variable();
    std::string get_instr_op_name( Instruction::OpID instr ) { return instr_id2string_[instr]; }
    void set_print_name();
    virtual std::string print();
private:
    std::list<GlobalVariable *> global_list_;
    std::list<Function *> function_list_;
    std::map<std::string, Value*> value_sym_;
    std::map<Instruction::OpID, std::string> instr_id2string_;
    
    std::string module_name_;
    std::string source_file_name_;
private:
    IntegerType *int1_ty_;
    IntegerType *int32_ty_;
    Type *label_ty_;
    Type *void_ty_;    
    FloatType *float32_ty_;
    
    std::map<Type *, PointerType *> pointer_map_;
    std::map<std::pair<Type *,int >, ArrayType *> array_map_; 
};

#endif // BAZINGA_COMPILER_MODULE_H