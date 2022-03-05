#include <iostream>
#include <memory>

#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "IRStmtBuilder.h"
#include "Module.h"
#include "Type.h"

#ifdef DEBUG
#define DEBUG_OUTPUT std::cout << __LINE__ << std::endl;
#else
#define DEBUG_OUTPUT
#endif

#define CONST_INT(num) ConstantInt::get(num, module)

#define CONST_FP(num) \
    ConstantFP::get(num, module)  // 得到常数值的表示,方便后面多次用到

int main() {
    auto module = new Module("Func_gen-code");
    auto builder = new IRStmtBuilder(nullptr, module);
    Type *Int32Type = Type::get_int32_type(module);

    // add函数
    std::vector<Type *> Ints(2, Int32Type);
    auto addFuncType = FunctionType::get(Int32Type, Ints);
    auto addFunc = Function::create(addFuncType, "add", module);
    auto bb = BasicBlock::create(module, "entry", addFunc);
    builder->set_insert_point(bb);
    auto retAlloca = builder->create_alloca(Int32Type);     // 在内存中分配返回值的位置
    auto aAlloca = builder->create_alloca(Int32Type);       // 在内存中分配两个参数a, b的位置
    auto bAlloca = builder->create_alloca(Int32Type);

    std::vector<Value *> args;
    for (auto arg = addFunc->arg_begin(); arg != addFunc->arg_end(); arg++) {
        args.push_back(*arg);
    }

    builder->create_store(args[0], aAlloca);
    builder->create_store(args[1], bAlloca);

    auto aLoad = builder->create_load(aAlloca);
    auto bLoad = builder->create_load(bAlloca);

    auto add = builder->create_iadd(aLoad, bLoad);
    auto sub = builder->create_isub(add, CONST_INT(1));

    builder->create_store(sub, retAlloca);
    auto retLoad = builder->create_load(retAlloca);
    builder->create_ret(retLoad);

    // main函数
    auto mainFunc =
        Function::create(FunctionType::get(Int32Type, {}), "main", module);
    bb = BasicBlock::create(module, "entry", mainFunc);
    builder->set_insert_point(bb);

    retAlloca = builder->create_alloca(Int32Type);

    aAlloca = builder->create_alloca(Int32Type);
    bAlloca = builder->create_alloca(Int32Type);
    auto cAlloca = builder->create_alloca(Int32Type);

    builder->create_store(CONST_INT(3), aAlloca);
    builder->create_store(CONST_INT(2), bAlloca);
    builder->create_store(CONST_INT(5), cAlloca);

    aLoad = builder->create_load(aAlloca);
    bLoad = builder->create_load(bAlloca);
    auto cLoad = builder->create_load(cAlloca);
    auto call = builder->create_call(addFunc, {aLoad, bLoad});
    add = builder->create_iadd(cLoad, call);

    builder->create_ret(add);

    std::cout << module->print();
    delete module;
    return 0;
}
