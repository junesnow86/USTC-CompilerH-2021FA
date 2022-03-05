#include "../../../include/SysYFIR/BasicBlock.h"
#include "../../../include/SysYFIR/Constant.h"
#include "../../../include/SysYFIR/Function.h"
#include "../../../include/SysYFIR/IRStmtBuilder.h"
#include "../../../include/SysYFIR/Module.h"
#include "../../../include/SysYFIR/Type.h"
#include <iostream>
#include <memory>
#include <vector>
#define CONST_INT(num) ConstantInt::get(num, module)

int main() {
  auto module = new Module("SysY code while_test"); // module name是什么无关紧要
  auto builder = new IRStmtBuilder(nullptr, module);
  Type *Int32Type = Type::get_int32_type(module);
  auto zero_initializer = ConstantZero::get(Int32Type, module);

  auto a =
      GlobalVariable::create("a", module, Int32Type, false, zero_initializer);
  auto b =
      GlobalVariable::create("b", module, Int32Type, false, zero_initializer);

  std::vector<Type *> ParamMain;
  auto mainFunTy = FunctionType::get(Int32Type, ParamMain);
  auto mainFun = Function::create(mainFunTy, "main", module);

  auto main_entry_bb = BasicBlock::create(module, "entry", mainFun);
  builder->set_insert_point(main_entry_bb);

  auto retAlloca = builder->create_alloca(Int32Type);
  builder->create_store(CONST_INT(0), b);
  builder->create_store(CONST_INT(3), a);
  auto cond_while_bb = BasicBlock::create(module, "condBB_while", mainFun);
  builder->create_br(cond_while_bb);

  auto true_while_bb = BasicBlock::create(module, "trueBB_while", mainFun);
  auto false_while_bb = BasicBlock::create(module, "falseBB_while", mainFun);

  builder->set_insert_point(cond_while_bb);
  auto aLoad = builder->create_load(a);
  auto icmp = builder->create_icmp_gt(aLoad, CONST_INT(0));
  builder->create_cond_br(icmp, true_while_bb, false_while_bb);

  builder->set_insert_point(true_while_bb);
  auto bLoad = builder->create_load(b);
  aLoad = builder->create_load(a);
  auto addba = builder->create_iadd(bLoad, aLoad);
  builder->create_store(addba, b);
  auto suba1 = builder->create_isub(aLoad, CONST_INT(1));
  builder->create_store(suba1, a);
  builder->create_br(cond_while_bb);

  builder->set_insert_point(false_while_bb);
  bLoad = builder->create_load(b);
  builder->create_store(bLoad, retAlloca);
  auto retLoad = builder->create_load(retAlloca);
  builder->create_ret(retLoad);

  std::cout << module->print();
  delete module;
  return 0;
}
