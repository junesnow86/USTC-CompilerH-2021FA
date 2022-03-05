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

    //global var: int a;
    auto zero_initializer = ConstantZero::get(Int32Type,module);
    auto a = GlobalVariable::create("a",module,Int32Type,false,zero_initializer);

    auto mainFunc = Function::create(FunctionType::get(Int32Type,{}),
                                     "main",module);
    auto bb = BasicBlock::create(module, "entry", mainFunc);

    builder->set_insert_point(bb);

    auto retAlloca = builder->create_alloca(Int32Type);
    //a = 10;
    builder->create_store(CONST_INT(10),a);
    //a>0 cond
    auto aLoad = builder->create_load(a);
    auto cmpl = builder->create_icmp_gt(aLoad,CONST_INT(0));
    auto iftruebb = BasicBlock::create(module,"if_true",mainFunc);
    auto retbb = BasicBlock::create(module,"if_false_ret",mainFunc);
    builder->create_cond_br(cmpl,iftruebb,retbb);
    //if true bb
    builder->set_insert_point(iftruebb);
    //return a
    aLoad = builder->create_load(a);
    builder->create_store(aLoad,retAlloca);
    auto retLoad = builder->create_load(retAlloca);
    builder->create_ret(retLoad);
    //if false bb & return 0
    builder->set_insert_point(retbb);
    builder->create_store(CONST_INT(0),retAlloca);
    retLoad = builder->create_load(retAlloca);
    builder->create_ret(retLoad);
    std::cout << module->print();
    delete module;
    return 0;
}
