#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "IRStmtBuilder.h"
#include "Module.h"
#include "Type.h"

#include <iostream>
#include <memory>

#ifdef DEBUG  // 用于调试信息,大家可以在编译过程中通过" -DDEBUG"来开启这一选项
#define DEBUG_OUTPUT std::cout << __LINE__ << std::endl;  // 输出行号的简单示例
#else
#define DEBUG_OUTPUT
#endif

#define CONST_INT(num) \
    ConstantInt::get(num, module)

#define CONST_FP(num) \
    ConstantFloat::get(num, module) // 得到常数值的表示,方便后面多次用到

int main(){
    auto module = new Module("ASSIGN GEN");
    auto builder = new IRStmtBuilder(nullptr,module);
    Type *Int32Type = Type::get_int32_type(module);
    Type *FType = Type::get_float_type(module);

    auto mainFunc = Function::create(FunctionType::get(Int32Type,{}),
                                     "main",module);
    auto bb = BasicBlock::create(module, "entry", mainFunc);

    builder->set_insert_point(bb);

    auto retAlloca = builder->create_alloca(Int32Type);
    //float b = 1.8;
    auto bAlloca = builder->create_alloca(FType);
    builder->create_store(CONST_FP(1.8),bAlloca);
    //int a[2] = {2};
    auto *arrayType_a = ArrayType::get(Int32Type,2);
    auto aAlloca = builder->create_alloca(arrayType_a);
    auto a0Gep = builder->create_gep(aAlloca,{CONST_INT(0),CONST_INT(0)});
    builder->create_store(CONST_INT(2),a0Gep);
    //a[1] = a[0]*b;
    //a0Gep = builder->create_gep(aAlloca,{CONST_INT(0),CONST_INT(0)});
    auto a0Load = builder->create_load(a0Gep);
    auto a0toFloat = builder->create_sitofp(a0Load,FType);
    auto bLoad = builder->create_load(bAlloca);
    auto fmul = builder->create_fmul(a0toFloat,bLoad);
    auto fmul2i = builder->create_fptosi(fmul,Int32Type);
    auto a1Gep = builder->create_gep(aAlloca,{CONST_INT(0),CONST_INT(1)});
    builder->create_store(fmul2i,a1Gep);
    //return a[1];
    auto a1Load = builder->create_load(a1Gep);
    builder->create_store(a1Load,retAlloca);
    auto retLoad = builder->create_load(retAlloca);
    builder->create_ret(retLoad);
    std::cout << module->print();
    delete module;
    return 0;
}
