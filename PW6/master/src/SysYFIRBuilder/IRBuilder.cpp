#include "IRBuilder.h"
#include "GlobalVal.h"
#include <vector>

#define CONST_INT(num) ConstantInt::get(num, module.get())
#define CONST_FLOAT(num) ConstantFloat::get(num, module.get())

#define DEBUG
#ifdef DEBUG
#define DBGLOG(text) std::cout << text << std::endl
#endif
#ifndef DEBUG
#define DBGLOG(text)
#endif

// You can define global variables and functions here
// to store state
bool _first_in_func;
Value *_ret_addr;
Value *_exp_val;
Value *_left_val;
Function *_func_parent;
BasicBlock *_ret_bb;

bool _get_literal = false;
int _label_num = 0;

std::vector<BasicBlock *> _break_addr;
std::vector<BasicBlock *> _continue_addr;

GlobalVal _global_val = GlobalVal();

// store temporary value
Value *tmp_val = nullptr;

// types
Type *VOID_T;
Type *INT1_T;
Type *INT32_T;
Type *FLOAT_T;
Type *INT32PTR_T;
Type *FLOATPTR_T;

void IRBuilder::visit(SyntaxTree::Assembly &node)
{
    VOID_T = Type::get_void_type(module.get());
    INT1_T = Type::get_int1_type(module.get());
    INT32_T = Type::get_int32_type(module.get());
    FLOAT_T = Type::get_float_type(module.get());
    INT32PTR_T = Type::get_int32_ptr_type(module.get());
    FLOATPTR_T = Type::get_float_ptr_type(module.get());
    for (const auto &def : node.global_defs)
    {
        def->accept(*this);
    }
}

// You need to fill them

void IRBuilder::visit(SyntaxTree::InitVal &node)
{
    /*expr：调用表达式*/
    //只处理一维数组
    if (node.isExp)
    {
        node.expr->accept(*this);
    }
    DBGLOG("Get expr val as left value.");
}

void IRBuilder::visit(SyntaxTree::FuncDef &node)
{
    /*先遍历形参列表获取类型，创建函数类型并记录到scope
      定义全局变量：_first_in_func，创建BB，并且分配返回值（f放到_ret_addr）、形参（记录scope）
      进入body
      退出的时候exit scope
    */
    Type *retType;
    std::vector<Type *> paramTypes;
    //获取返回值
    switch (node.ret_type)
    {
    case SyntaxTree::Type::INT:
        retType = INT32_T;
        DBGLOG("Function Type: INT.");
        break;
    case SyntaxTree::Type::FLOAT:
        retType = FLOAT_T;
        DBGLOG("Function Type: FLOAT.");
        break;
    case SyntaxTree::Type::VOID:
        retType = VOID_T;
        DBGLOG("Function Type: VOID.");
        break;
    default:
        DBGLOG("Function Type: Unknown.");
        break;
    }
    //获取参数类型
    for (auto param : node.param_list->params)
    {
        if (param->array_index.size() == 0)
        {
            //若0说明不是数组
            switch (param->param_type)
            {
            case SyntaxTree::Type::INT:
                paramTypes.push_back(INT32_T);
                DBGLOG("Param Type: INT.");
                break;
            case SyntaxTree::Type::FLOAT:
                paramTypes.push_back(FLOAT_T);
                DBGLOG("Param Type: FLOAT.");
                break;
            default:
                DBGLOG("Param Type: Unknown.");
                break;
            }
        }
        else
        {
            //否则只处理一维数组的情况（当作指针）
            switch (param->param_type)
            {
            case SyntaxTree::Type::INT:
                paramTypes.push_back(INT32PTR_T);
                DBGLOG("Param Type: pINT.");
                break;
            case SyntaxTree::Type::FLOAT:
                paramTypes.push_back(FLOATPTR_T);
                DBGLOG("Param Type: pFLOAT.");
                break;
            default:
                DBGLOG("Param Type: Unknown.");
                break;
            }
        }
    }
    //创建函数
    auto funcType = FunctionType::get(retType, paramTypes);
    auto func = Function::create(funcType, node.name, module.get());
    DBGLOG("Create function.");
    //设置_func_parent
    _func_parent = func;
    DBGLOG("_func_parent set.");
    //记录函数类型到scope
    scope.push(node.name, func);
    scope.enter();
    DBGLOG("Push function type to scope.");
    //创建BB并进入
    auto funcBB = BasicBlock::create(module.get(), node.name + "_Label", func);
    builder->set_insert_point(funcBB);
    DBGLOG("Create BasicBlock and enter.");
    //设置_first_in_func
    _first_in_func = true;
    DBGLOG("_first_in_func set.");
    //若为void类型，则不需要返回值
    if (retType != VOID_T)
    {
        //分配返回值
        auto retValue = builder->create_alloca(retType);
        //预先为返回值设置为0
        builder->create_store(ConstantZero::get(retType, module.get()), retValue);
        DBGLOG("return value alloca & auto set.");
        //设置_ret_addr
        _ret_addr = retValue;
        DBGLOG("_ret_addr set.");
    }
    //创建一个return block
    auto retBB = BasicBlock::create(module.get(), node.name + "_retBB", func);
    _ret_bb = retBB;
    DBGLOG("return basic block create& set to _ret_bb.");
    //声明参数并记录到符号表
    std::vector<Value *> args;
    for (auto arg = func->arg_begin(); arg != func->arg_end(); arg++)
    {
        args.push_back(*arg);
    }
    int paramIndex = 0;
    for (auto param : node.param_list->params)
    {
        auto pType = paramTypes[paramIndex];
        auto paramAlloca = builder->create_alloca(pType);
        builder->create_store(args[paramIndex], paramAlloca);
        scope.push(param->name, paramAlloca);
        paramIndex++;
        DBGLOG("alloca&push scope: arg" << paramIndex);
    }
    //调用body
    node.body->accept(*this);
    //需要检查是否没有return语句，如果没有则跳转到retBB所在位置
    if (!builder->get_insert_block()->get_terminator())
        builder->create_br(retBB);
    //返回语句放到函数末尾
    builder->set_insert_point(retBB);
    if (retType == VOID_T)
        builder->create_void_ret();
    else
    {
        auto value_to_ret = builder->create_load(retType, _ret_addr);
        builder->create_ret(value_to_ret);
    }
}

void IRBuilder::visit(SyntaxTree::FuncFParamList &node) {}

void IRBuilder::visit(SyntaxTree::FuncParam &node) {}

void IRBuilder::visit(SyntaxTree::FuncCallStmt &node)
{
    /*实参类型转换：i1->i32 i_f
        返回到_exp_val
    */
    //查表
    auto func = dynamic_cast<Function *>(scope.find(node.name, true));
    DBGLOG("Entering funcCall." << node.name);
    auto funcType = func->get_function_type();
    DBGLOG("lookup ftype");
    std::vector<Value *> params;
    int pId = 0;
    for (auto param : node.params)
    {
        param->accept(*this);
        auto pValue = _exp_val;
        auto pType = funcType->get_param_type(pId);
        if (pType->is_array_type() || pType->is_pointer_type())
        {
            //指针类型，不做处理
            DBGLOG("Pointer param.");
            params.push_back(pValue);
        }
        else if (pType != pValue->get_type())
        {
            //类型不同，做转换
            if (pType == INT32_T)
            {
                if (pValue->get_type() == INT1_T)
                {
                    auto correctVal = builder->create_zext(pValue, INT32_T);
                    params.push_back(correctVal);
                    DBGLOG("(INT)(int1 param).");
                }
                else if (pValue->get_type() == FLOAT_T)
                {
                    auto correctVal = builder->create_fptosi(pValue, INT32_T);
                    params.push_back(correctVal);
                    DBGLOG("(INT)(float param).");
                }
                else
                {
                    DBGLOG("Unknown param value unmatched.");
                }
            }
            else if (pType == FLOAT_T)
            {
                if (pValue->get_type() == INT1_T || pValue->get_type() == INT32_T)
                {
                    auto correctVal = builder->create_sitofp(pValue, FLOAT_T);
                    params.push_back(correctVal);
                    DBGLOG("(FLOAT)(int param).");
                }
                else
                {
                    DBGLOG("Unknown param value unmatched.");
                }
            }
            else
            {
                DBGLOG("Unknown param type unmatched.");
            }
        }
        else
        {
            DBGLOG("Matched param.");
            params.push_back(pValue);
        }
        pId++;
    }
    _exp_val = builder->create_call(func, params);
    DBGLOG("Exiting funcCall.");
}

void IRBuilder::visit(SyntaxTree::VarDef &node)
{
    /*获取类型、判断全局、写表、分配值、初始值（store）*/
    Type *varType;
    if (node.btype == SyntaxTree::Type::INT)
        varType = INT32_T;
    else
        varType = FLOAT_T;
    if (scope.in_global())
    {
        //全局变量
        if (node.array_length.size())
        {
            //数组类型
            //一维数组，获取node.array_length[0]对应的literal值
            SyntaxTree::Expr *arr_first_len = node.array_length[0].get();
            arr_first_len->accept(*this);
            int arr_len = 0;
            if(_global_val.top_is_int()){
                arr_len = _global_val.pop_int();
            }
            else{
                DBGLOG("Array length is float!!!");
            }
            auto *arrayType = ArrayType::get(varType, arr_len);
            DBGLOG("get global array type.");
            //初始值
            if (node.is_inited)
            {
                //然后对每个初始值进行store
                std::vector<Constant *> init_val;
                //一维数组，第二层initVal就必须是expr
                for (auto ival : node.initializers->elementList)
                {
                    ival->expr->accept(*this);
                    if (_global_val.top_is_int())
                    {
                        int popVal = _global_val.pop_int();
                        if (varType == INT32_T)
                        {
                            init_val.push_back(CONST_INT(popVal));
                            DBGLOG("initialize " << node.name << " with " << popVal);
                            //若为常量则需要添加到表中
                            if (node.is_constant)
                            {
                                _global_val.addConst(node.name, (int)popVal);
                                DBGLOG("add INT CONST " << popVal << " to " << node.name);
                            }
                        }
                        else
                        {
                            init_val.push_back(CONST_FLOAT(_global_val.pop_int()));
                            DBGLOG("initialize " << node.name << " with " << popVal);
                            if (node.is_constant)
                            {
                                _global_val.addConst(node.name, (float)popVal);
                                DBGLOG("add FLOAT CONST " << popVal << " to " << node.name);
                            }
                        }
                    }
                    else
                    {
                        float popVal = _global_val.pop_float();
                        if (varType == INT32_T)
                        {
                            init_val.push_back(CONST_INT((int)_global_val.pop_float()));
                            DBGLOG("initialize " << node.name << " with " << popVal);
                            if (node.is_constant)
                            {
                                _global_val.addConst(node.name, (int)popVal);
                                DBGLOG("add INT CONST " << popVal << " to " << node.name);
                            }
                        }
                        else
                        {
                            init_val.push_back(CONST_FLOAT(_global_val.pop_float()));
                            DBGLOG("initialize " << node.name << " with " << popVal);
                            if (node.is_constant)
                            {
                                _global_val.addConst(node.name, (float)popVal);
                                DBGLOG("add FLOAT CONST " << popVal << " to " << node.name);
                            }
                        }
                    }
                }
                //剩余的部分初始化为0或0.0
                for (int i = init_val.size(); i < arr_len; i++)
                {
                    if (varType == INT32_T)
                    {
                        init_val.push_back(CONST_INT(0));
                        DBGLOG("initialize " << node.name << " with " << 0);
                        if (node.is_constant)
                        {
                            _global_val.addConst(node.name, 0);
                            DBGLOG("add INT CONST " << 0 << " to " << node.name);
                        }
                    }
                    else
                    {
                        init_val.push_back(CONST_FLOAT(0));
                        DBGLOG("initialize " << node.name << " with " << 0.0);
                        if (node.is_constant)
                        {
                            _global_val.addConst(node.name, 0.0f);
                            DBGLOG("add FLOAT CONST " << 0.0 << " to " << node.name);
                        }
                    }
                }
                auto initializer = ConstantArray::get(arrayType, init_val);
                auto globalArrVar = GlobalVariable::create(node.name, module.get(), arrayType, node.is_constant, initializer);
                DBGLOG("global array defined and initialized.");
                scope.push(node.name, globalArrVar);
            }
            else
            {
                //全部初始化为0
                if (node.is_constant)
                {
                    for (int i = 0; i < arr_len; i++)
                    {
                        if (varType == INT32_T)
                        {
                            _global_val.addConst(node.name, 0);
                            DBGLOG("add INT CONST " << 0 << " to " << node.name);
                        }
                        else
                        {
                            _global_val.addConst(node.name, 0.0f);
                            DBGLOG("add FLOAT CONST " << 0.0 << " to " << node.name);
                        }
                    }
                }
                DBGLOG("AUTO initialize " << node.name << " with " << 0);
                auto initializer = ConstantZero::get(varType, module.get());
                auto globalArrVar = GlobalVariable::create(node.name, module.get(), arrayType, node.is_constant, initializer);
                DBGLOG("global array var defined and AUTO initialized.");
                scope.push(node.name, globalArrVar);
            }
        }
        else
        {
            //若是普通变量
            if (node.is_inited)
            {
                //初始化
                node.initializers->expr->accept(*this);
                Constant *init_val;
                if (varType == INT32_T)
                {
                    if (_global_val.top_is_int())
                    {
                        int popVal = _global_val.pop_int();
                        init_val = CONST_INT(popVal);
                        DBGLOG("initialize " << node.name << " with " << popVal);
                        if (node.is_constant)
                        {
                            _global_val.addConst(node.name, (int)popVal);
                            DBGLOG("add INT CONST " << popVal << " to " << node.name);
                        }
                    }
                    else
                    {
                        int popVal = _global_val.pop_float();
                        init_val = CONST_INT(popVal);
                        DBGLOG("initialize " << node.name << " with " << popVal);
                        if (node.is_constant)
                        {
                            _global_val.addConst(node.name, (int)popVal);
                            DBGLOG("add INT CONST " << popVal << " to " << node.name);
                        }
                    }
                }
                else
                {
                    if (_global_val.top_is_int())
                    {
                        float popVal = _global_val.pop_int();
                        init_val = CONST_FLOAT(popVal);
                        DBGLOG("initialize " << node.name << " with " << popVal);
                        if (node.is_constant)
                        {
                            _global_val.addConst(node.name, (float)popVal);
                            DBGLOG("add FLOAT CONST " << popVal << " to " << node.name);
                        }
                    }
                    else
                    {
                        float popVal = _global_val.pop_float();
                        init_val = CONST_FLOAT(popVal);
                        DBGLOG("initialize " << node.name << " with " << popVal);
                        if (node.is_constant)
                        {
                            _global_val.addConst(node.name, (float)popVal);
                            DBGLOG("add FLOAT CONST " << popVal << " to " << node.name);
                        }
                    }
                }
                auto globalVar = GlobalVariable::create(node.name, module.get(), varType, node.is_constant, init_val);
                DBGLOG("global var defined and initialized.");
                scope.push(node.name, globalVar);
            }
            else
            {
                DBGLOG("AUTO initialize " << node.name << " with " << 0);
                auto initializer = ConstantZero::get(varType, module.get());
                auto globalVar = GlobalVariable::create(node.name, module.get(), varType, node.is_constant, initializer);
                DBGLOG("global var defined and AUTO initialized.");
                if (node.is_constant)
                {
                    if(varType == INT32_T){
                        _global_val.addConst(node.name, 0);
                        DBGLOG("add INT CONST " << 0 << " to " << node.name);
                    }
                    else{
                        _global_val.addConst(node.name, 0.0f);
                        DBGLOG("add FLOAT CONST " << 0.0 << " to " << node.name);
                    }
                }
                scope.push(node.name, globalVar);
            }
        }
    }
    else
    {
        //局部变量
        if (node.array_length.size())
        {
            //数组类型
            //一维数组，获取node.array_length[0]对应的literal值
            SyntaxTree::Expr *arr_first_len = node.array_length[0].get();
            //设置_get_literal
            _get_literal = true;
            arr_first_len->accept(*this);
            _get_literal = false;
            //获取记录在全局变量计算器栈顶的值
            int arr_len = 0;
            if(_global_val.top_is_int()){
                arr_len = _global_val.pop_int();
                DBGLOG("Array length:"<<arr_len);
            }
            else{
                DBGLOG("Array length is float!!!");
            }
            auto *arrayType = ArrayType::get(varType, arr_len);
            DBGLOG("get array type.");
            auto ArrVar = builder->create_alloca(arrayType);
            DBGLOG("array var defined.");
            if (node.is_inited)
            {
                //然后对每个初始值进行store
                //一维数组，第二层initVal就必须是expr
                int arrIndex = 0;
                for (auto ival : node.initializers->elementList)
                {
                    ival->expr->accept(*this);
                    //gep & store
                    if (_exp_val->get_type() != varType)
                    {
                        //类型转换
                        if (varType == INT32_T)
                        {
                            _exp_val = builder->create_fptosi(_exp_val, INT32_T);
                            DBGLOG("FP2SI in INIT.");
                        }
                        else
                        {
                            _exp_val = builder->create_sitofp(_exp_val, FLOAT_T);
                            DBGLOG("SI2FP in INIT.");
                        }
                    }
                    auto iGep = builder->create_gep(ArrVar, {CONST_INT(0), CONST_INT(arrIndex)});
                    builder->create_store(_exp_val, iGep);
                    arrIndex++;
                }
                DBGLOG("array initialized.");
            }
            scope.push(node.name, ArrVar);
        }
        else
        {
            //非数组类型
            auto Var = builder->create_alloca(varType);
            DBGLOG("var defined.");
            if (node.is_inited)
            {
                node.initializers->expr->accept(*this);
                //store
                if (_exp_val->get_type() != varType)
                {
                    //类型转换
                    if (varType == INT32_T)
                    {
                        _exp_val = builder->create_fptosi(_exp_val, INT32_T);
                        DBGLOG("FP2SI in INIT.");
                    }
                    else
                    {
                        _exp_val = builder->create_sitofp(_exp_val, FLOAT_T);
                        DBGLOG("SI2FP in INIT.");
                    }
                }
                builder->create_store(_exp_val, Var);
                DBGLOG("var initialized.");
            }
            scope.push(node.name, Var);
        }
    }
}

void IRBuilder::visit(SyntaxTree::LVal &node)
{
    //全局变量初始化使用Lval当且仅当左值表达式为常量
    if (scope.in_global() || _get_literal)
    {
        if (node.array_index.size() != 0)
        {
            //只考虑一维数组
            //若为数组类型，则先取下标
            node.array_index[0]->accept(*this);
            int offset;
            if (_global_val.top_is_int())
                offset = _global_val.pop_int();
            else
                offset = _global_val.pop_float();
            _global_val.pushConst(node.name, offset);
            DBGLOG("cal CONST of " << node.name << " at offset " << offset);
        }
        else
        {
            _global_val.pushConst(node.name, 0);
            DBGLOG("cal CONST of " << node.name);
        }
    }
    else
    {
        DBGLOG("using lval:" << node.name);
        auto lAddr = scope.find(node.name, false);
        //左值表达式可以作为赋值对象，也可以作为表达式
        if (node.array_index.size() != 0)
        {
            //数组变量
            //一维数组，要先计算偏移量
            node.array_index[0]->accept(*this);
            if (lAddr->get_type()->get_pointer_element_type()->is_array_type())
            {
                //作为左值，gep
                _left_val = builder->create_gep(lAddr, {CONST_INT(0), _exp_val});
                //作为表达式，gep之后还要load
                _exp_val = builder->create_load(_left_val);
                DBGLOG("array data as lval.");
            }
            else
            {
                //指针类型，先取得指针的值（int*），然后对其作_exp_val的偏移
                auto ptemp = builder->create_load(lAddr);
                _left_val = builder->create_gep(ptemp, {_exp_val});
                _exp_val = builder->create_load(_left_val);
                DBGLOG("pointer data as lval.");
            }
        }
        else if (lAddr->get_type()->get_pointer_element_type()->is_array_type())
        {
            //若为指数组变量
            /*这里存疑**/
            //作为左值
            _left_val = lAddr;
            //数组作为表达式（即数组作函数实参），将其转化为指针：
            //取第一个元素的地址
            _exp_val = builder->create_gep(lAddr, {CONST_INT(0),CONST_INT(0)});
            DBGLOG("array as lval.");
        }
        else if(lAddr->get_type()->get_pointer_element_type()->is_pointer_type()){
            //指针类型变量
            _left_val = lAddr;
            //作为表达式
            _exp_val = builder->create_load(lAddr);
            DBGLOG("pointer as lval.");
        }
        else
        {
            //作为左值
            _left_val = lAddr;
            //作为表达式
            _exp_val = builder->create_load(lAddr);
            DBGLOG("normal var as lval.");
        }
    }
}

void IRBuilder::visit(SyntaxTree::AssignStmt &node)
{
    //store
    //先左值，再表达式（否则会被覆盖）
    node.target->accept(*this);
    auto target_addr = _left_val;
    node.value->accept(*this);
    auto right_value = _exp_val;
    //类型转换(被赋值的变量类型只能是INT或FLOAT)
    auto lvalType = target_addr->get_type()->get_pointer_element_type();
    auto expType = right_value->get_type();
    if (expType == INT1_T)
    {
        right_value = builder->create_zext(right_value, INT32_T);
        expType = INT32_T;
        DBGLOG("Zext in assign.");
    }
    if (lvalType != expType)
    {
        if (lvalType == INT32_T)
        {
            right_value = builder->create_fptosi(right_value, INT32_T);
            DBGLOG("FP2SI in assign.");
        }
        else
        {
            right_value = builder->create_sitofp(right_value, FLOAT_T);
            DBGLOG("SI2FP in assign.");
        }
    }
    builder->create_store(right_value, target_addr);
}

void IRBuilder::visit(SyntaxTree::Literal &node)
{
    if (scope.in_global()||_get_literal)
    {
        if (node.literal_type == SyntaxTree::Type::INT)
            _global_val.push(node.int_const);
        else
            //可能会涉及到浮点数范围的问题
            _global_val.push((float)node.float_const);
    }
    else
    {
        if (node.literal_type == SyntaxTree::Type::INT)
        {
            _exp_val = CONST_INT(node.int_const);
            DBGLOG("INT literal:" << node.int_const);
        }
        else
        {
            _exp_val = CONST_FLOAT(node.float_const);
            DBGLOG("FLOAT literal:" << node.float_const);
        }
    }
}

/*********************************/

void IRBuilder::visit(SyntaxTree::EmptyStmt &node) {}

void IRBuilder::visit(SyntaxTree::ExprStmt &node) { node.exp->accept(*this); }

void IRBuilder::visit(SyntaxTree::UnaryCondExpr &node)
{
    /*i/fcmp与0相比，返回到全局变量_exp_val i1*/
    if (scope.in_global()||_get_literal)
    {
        node.rhs->accept(*this);
        _global_val.cal(node.op);
    }
    else
    {
        node.rhs->accept(*this);
        auto rhs = _exp_val;
        Type *rhsType = rhs->get_type();

        if (node.op == SyntaxTree::UnaryCondOp::NOT)
        {
            if (rhsType->is_float_type())
            {
                // auto zero = ConstantFloat::get(0.0, module.get());
                auto zero = CONST_FLOAT(0.0);
                _exp_val = this->builder->create_fcmp_eq(zero, rhs);
                DBGLOG("NOT FLOAT.");
            }
            else if (rhsType->is_integer_type())
            {
                // auto zero = ConstantInt::get(0, module.get());
                auto zero = CONST_INT(0);
                if (Type::is_eq_type(rhsType, INT1_T))
                {
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_eq(zero, int1_to_32);
                }
                else
                    _exp_val = this->builder->create_icmp_eq(zero, rhs);
                DBGLOG("NOT INT.");
            }
            else
            {
                // rhsType是ptr
                _exp_val = CONST_INT(false);
                DBGLOG("NOT PTR.");
            }
        }
    }
}

void IRBuilder::visit(SyntaxTree::BinaryCondExpr &node)
{
    if (scope.in_global()||_get_literal)
    {
        node.lhs->accept(*this);
        node.rhs->accept(*this);
        _global_val.cal(node.op);
    }
    else
    {
        
        node.lhs->accept(*this);
        auto lhs = _exp_val;
        auto lhsType = lhs->get_type();
        node.rhs->accept(*this);
        auto rhs = _exp_val;
        auto rhsType = rhs->get_type();
        

        switch (node.op)
        {
        case SyntaxTree::BinaryCondOp::EQ:
            if (lhsType->is_float_type() || rhsType->is_float_type())
            {
                if (lhsType->is_integer_type())
                {
                    if (Type::is_eq_type(lhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(lhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_eq(int_to_float, rhs);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(lhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_eq(int_to_float, rhs);
                    }
                }
                else if (rhsType->is_integer_type())
                {
                    if (Type::is_eq_type(rhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(rhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_eq(lhs, int_to_float);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(rhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_eq(lhs, int_to_float);
                    }
                }
                else
                    _exp_val = this->builder->create_fcmp_eq(lhs, rhs);
            }
            else
            {
                // 左右操作数都不是float
                // 这里仅考虑左右操作数都是integer的情况
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_icmp_eq(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_eq(lhs, int1_to_32);
                }
                else if (Type::is_eq_type(lhsType, INT1_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto tmp1 = this->builder->create_zext(lhs, INT32_T);
                    auto tmp2 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_eq(tmp1, tmp2);
                }
                else
                    _exp_val = this->builder->create_icmp_eq(lhs, rhs);
            }
            break;
        case SyntaxTree::BinaryCondOp::NEQ:
            if (lhsType->is_float_type() || rhsType->is_float_type())
            {
                if (lhsType->is_integer_type())
                {
                    if (Type::is_eq_type(lhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(lhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_ne(int_to_float, rhs);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(lhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_ne(int_to_float, rhs);
                    }
                }
                else if (rhsType->is_integer_type())
                {
                    if (Type::is_eq_type(rhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(rhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_ne(lhs, int_to_float);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(rhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_ne(lhs, int_to_float);
                    }
                }
                else
                    _exp_val = this->builder->create_fcmp_ne(lhs, rhs);
            }
            else
            {
                // 左右操作数都不是float
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_icmp_ne(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_ne(lhs, int1_to_32);
                }
                else if (Type::is_eq_type(lhsType, INT1_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto tmp1 = this->builder->create_zext(lhs, INT32_T);
                    auto tmp2 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_ne(tmp1, tmp2);
                }
                else
                    _exp_val = this->builder->create_icmp_ne(lhs, rhs);
            }
            break;
        case SyntaxTree::BinaryCondOp::GT:
            if (lhsType->is_float_type() || rhsType->is_float_type())
            {
                if (lhsType->is_integer_type())
                {
                    if (Type::is_eq_type(lhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(lhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_gt(int_to_float, rhs);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(lhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_gt(int_to_float, rhs);
                    }
                }
                else if (rhsType->is_integer_type())
                {
                    if (Type::is_eq_type(rhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(rhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_gt(lhs, int_to_float);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(rhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_gt(lhs, int_to_float);
                    }
                }
                else
                    _exp_val = this->builder->create_fcmp_gt(lhs, rhs);
            }
            else
            {
                // 左右操作数都不是float
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_icmp_gt(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_gt(lhs, int1_to_32);
                }
                else if (Type::is_eq_type(lhsType, INT1_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto tmp1 = this->builder->create_zext(lhs, INT32_T);
                    auto tmp2 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_gt(tmp1, tmp2);
                }
                else
                    _exp_val = this->builder->create_icmp_gt(lhs, rhs);
            }
            break;
        case SyntaxTree::BinaryCondOp::GTE:
            if (lhsType->is_float_type() || rhsType->is_float_type())
            {
                if (lhsType->is_integer_type())
                {
                    if (Type::is_eq_type(lhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(lhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_ge(int_to_float, rhs);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(lhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_ge(int_to_float, rhs);
                    }
                }
                else if (rhsType->is_integer_type())
                {
                    if (Type::is_eq_type(rhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(rhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_ge(lhs, int_to_float);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(rhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_ge(lhs, int_to_float);
                    }
                }
                else
                    _exp_val = this->builder->create_fcmp_ge(lhs, rhs);
            }
            else
            {
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_icmp_ge(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_ge(lhs, int1_to_32);
                }
                else if (Type::is_eq_type(lhsType, INT1_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto tmp1 = this->builder->create_zext(lhs, INT32_T);
                    auto tmp2 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_ge(tmp1, tmp2);
                }
                else
                    _exp_val = this->builder->create_icmp_ge(lhs, rhs);
            }
            break;
        case SyntaxTree::BinaryCondOp::LT:
            if (lhsType->is_float_type() || rhsType->is_float_type())
            {
                if (lhsType->is_integer_type())
                {
                    if (Type::is_eq_type(lhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(lhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_lt(int_to_float, rhs);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(lhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_lt(int_to_float, rhs);
                    }
                }
                else if (rhsType->is_integer_type())
                {
                    if (Type::is_eq_type(rhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(rhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_lt(lhs, int_to_float);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(rhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_lt(lhs, int_to_float);
                    }
                }
                else
                    _exp_val = this->builder->create_fcmp_lt(lhs, rhs);
            }
            else
            {
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_icmp_lt(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_lt(lhs, int1_to_32);
                }
                else if (Type::is_eq_type(lhsType, INT1_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto tmp1 = this->builder->create_zext(lhs, INT32_T);
                    auto tmp2 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_lt(tmp1, tmp2);
                }
                else
                    _exp_val = this->builder->create_icmp_lt(lhs, rhs);
            }
            break;
        case SyntaxTree::BinaryCondOp::LTE:
            if (lhsType->is_float_type() || rhsType->is_float_type())
            {
                if (lhsType->is_integer_type())
                {
                    if (Type::is_eq_type(lhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(lhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_le(int_to_float, rhs);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(lhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_le(int_to_float, rhs);
                    }
                }
                else if (rhsType->is_integer_type())
                {
                    if (Type::is_eq_type(rhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(rhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_le(lhs, int_to_float);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(rhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fcmp_le(lhs, int_to_float);
                    }
                }
                else
                    _exp_val = this->builder->create_fcmp_le(lhs, rhs);
            }
            else
            {
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_icmp_le(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_le(lhs, int1_to_32);
                }
                else if (Type::is_eq_type(lhsType, INT1_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    auto tmp1 = this->builder->create_zext(lhs, INT32_T);
                    auto tmp2 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_icmp_le(tmp1, tmp2);
                }
                else
                    _exp_val = this->builder->create_icmp_le(lhs, rhs);
            }
            break;
        case SyntaxTree::BinaryCondOp::LAND:
        {
            //左右操作数都是INT1_T
            char LabelName[20];
            auto func_parent = _func_parent;
            sprintf(LabelName, "true_cexp_bb_%d", _label_num++);
            auto true_cexp_bb =
                BasicBlock::create(module.get(), LabelName, func_parent);
            sprintf(LabelName, "false_cexp_bb_%d", _label_num++);
            auto false_cexp_bb =
                BasicBlock::create(module.get(), LabelName, func_parent);
            sprintf(LabelName, "next_cexp_bb_%d", _label_num++);
            auto next_cexp_bb =
                BasicBlock::create(module.get(), LabelName, func_parent);
            sprintf(LabelName, "after_cexp_bb_%d", _label_num++);
            auto after_cexp_bb =
                BasicBlock::create(module.get(), LabelName, func_parent);

            // node.lhs->accept(*this);
            // auto lhs_type = _exp_val->get_type();
            if (lhsType->is_eq_type(lhsType, INT1_T)) {
                builder->create_cond_br(_exp_val, next_cexp_bb, false_cexp_bb);
            } else if (lhsType->is_eq_type(lhsType, INT32_T)) {
                auto cond_i1 = builder->create_icmp_ne(_exp_val, CONST_INT(0));
                _exp_val = cond_i1;
                builder->create_cond_br(cond_i1, next_cexp_bb, false_cexp_bb);
            } else if (lhsType->is_eq_type(lhsType, FLOAT_T)) {
                auto cond_i1 =
                    builder->create_fcmp_ne(_exp_val, CONST_FLOAT(0));
                _exp_val = cond_i1;
                builder->create_cond_br(cond_i1, next_cexp_bb, false_cexp_bb);
            } else {
                _exp_val = CONST_INT(true);
                builder->create_br(next_cexp_bb);
            }

            builder->set_insert_point(next_cexp_bb);
            // node.rhs->accept(*this);
            // auto rhs_type = _exp_val->get_type();
            if (rhsType->is_eq_type(rhsType, INT1_T)) {
                builder->create_cond_br(_exp_val, true_cexp_bb, false_cexp_bb);
            } else if (rhsType->is_eq_type(rhsType, INT32_T)) {
                auto cond_i1 = builder->create_icmp_ne(_exp_val, CONST_INT(0));
                _exp_val = cond_i1;
                builder->create_cond_br(cond_i1, true_cexp_bb, false_cexp_bb);
            } else if (rhsType->is_eq_type(rhsType, FLOAT_T)) {
                auto cond_i1 =
                    builder->create_fcmp_ne(_exp_val, CONST_FLOAT(0));
                _exp_val = cond_i1;
                builder->create_cond_br(cond_i1, true_cexp_bb, false_cexp_bb);
            } else {
                _exp_val = CONST_INT(true);
                builder->create_br(true_cexp_bb);
            }


            builder->set_insert_point(true_cexp_bb);
            builder->create_br(after_cexp_bb);

            builder->set_insert_point(false_cexp_bb);
            builder->create_br(after_cexp_bb);

            builder->set_insert_point(after_cexp_bb);
            break;
        }
        case SyntaxTree::BinaryCondOp::LOR:
        {
            char LabelName[20];
            auto func_parent = _func_parent;
            sprintf(LabelName, "true_cexp_bb_%d", _label_num++);
            auto true_cexp_bb =
                BasicBlock::create(module.get(), LabelName, func_parent);
            sprintf(LabelName, "false_cexp_bb_%d", _label_num++);
            auto false_cexp_bb =
                BasicBlock::create(module.get(), LabelName, func_parent);
            sprintf(LabelName, "next_cexp_bb_%d", _label_num++);
            auto next_cexp_bb =
                BasicBlock::create(module.get(), LabelName, func_parent);
            sprintf(LabelName, "after_cexp_bb_%d", _label_num++);
            auto after_cexp_bb =
                BasicBlock::create(module.get(), LabelName, func_parent);

            // node.lhs->accept(*this);
            // auto lhs_type = _exp_val->get_type();
            if (lhsType->is_eq_type(lhsType, INT1_T)) {
                builder->create_cond_br(_exp_val, true_cexp_bb, next_cexp_bb);
            } else if (lhsType->is_eq_type(lhsType, INT32_T)) {
                auto cond_i1 = builder->create_icmp_ne(_exp_val, CONST_INT(0));
                _exp_val = cond_i1;
                builder->create_cond_br(cond_i1, true_cexp_bb, next_cexp_bb);
            } else if (lhsType->is_eq_type(lhsType, FLOAT_T)) {
                auto cond_i1 =
                    builder->create_fcmp_ne(_exp_val, CONST_FLOAT(0));
                _exp_val = cond_i1;
                builder->create_cond_br(cond_i1, true_cexp_bb, next_cexp_bb);
            } else {
                _exp_val = CONST_INT(true);
                builder->create_br(true_cexp_bb);
            }

            builder->set_insert_point(next_cexp_bb);
            // node.rhs->accept(*this);
            // auto rhs_type = _exp_val->get_type();
            if (rhsType->is_eq_type(rhsType, INT1_T)) {
                builder->create_cond_br(_exp_val, true_cexp_bb, false_cexp_bb);
            } else if (rhsType->is_eq_type(rhsType, INT32_T)) {
                auto cond_i1 = builder->create_icmp_ne(_exp_val, CONST_INT(0));
                _exp_val = cond_i1;
                builder->create_cond_br(cond_i1, true_cexp_bb, false_cexp_bb);
            } else if (rhsType->is_eq_type(rhsType, FLOAT_T)) {
                auto cond_i1 =
                    builder->create_fcmp_ne(_exp_val, CONST_FLOAT(0));
                _exp_val = cond_i1;
                builder->create_cond_br(cond_i1, true_cexp_bb, false_cexp_bb);
            } else {
                _exp_val = CONST_INT(true);
                builder->create_br(true_cexp_bb);
            }

            builder->set_insert_point(true_cexp_bb);
            builder->create_br(after_cexp_bb);

            builder->set_insert_point(false_cexp_bb);
            builder->create_br(after_cexp_bb);

            builder->set_insert_point(after_cexp_bb);
            break;
        }
        }
    }
}

void IRBuilder::visit(SyntaxTree::BinaryExpr &node)
{
    if (scope.in_global()||_get_literal)
    {
        node.lhs->accept(*this);
        node.rhs->accept(*this);
        _global_val.cal(node.op);
    }
    else
    {
        node.lhs->accept(*this);
        Value *lhs = _exp_val;
        Type *lhsType = lhs->get_type();
        node.rhs->accept(*this);
        Value *rhs = _exp_val;
        Type *rhsType = rhs->get_type();

        switch (node.op)
        {
        case SyntaxTree::BinOp::PLUS:
        {
            if ((Type::is_eq_type(lhsType, FLOAT_T)) ||
                Type::is_eq_type(rhsType, FLOAT_T))
            {
                // float加法
                if (!Type::is_eq_type(lhsType, FLOAT_T))
                { // lhs不是float型
                    DBGLOG("INT + FLOAT.");
                    if (Type::is_eq_type(lhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(lhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fadd(int_to_float, rhs);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(lhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fadd(int_to_float, rhs);
                    }
                }
                else if (!Type::is_eq_type(rhsType,
                                           FLOAT_T))
                { // rhs不是float型
                    DBGLOG("FLOAT + INT.");
                    if (Type::is_eq_type(rhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(rhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fadd(lhs, int_to_float);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(rhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fadd(lhs, int_to_float);
                    }
                }
                else
                {
                    DBGLOG("FLOAT + FLOAT.");
                    _exp_val = this->builder->create_fadd(lhs, rhs);
                }
            }
            else if (lhsType->is_integer_type() &&
                     rhsType->is_integer_type())
            {
                DBGLOG("INT + INT.");
                // int加法
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    // lhs是INT1，rhs是INT32
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_iadd(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    // lhs是INT32，rhs是INT1
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_iadd(lhs, int1_to_32);
                }
                else
                    _exp_val = this->builder->create_iadd(lhs, rhs);
            }
            else
            {
                // 左右操作数一个是ptr，一个是int32
                // pointer还是array?
                std::vector<Value *> tmp;
                if (lhsType->is_pointer_type())
                {
                    DBGLOG("PTR + INT.");
                    tmp.push_back(rhs);
                    _exp_val = this->builder->create_gep(lhs, tmp);
                }
                else
                {
                    DBGLOG("INT + PTR.");
                    tmp.push_back(lhs);
                    _exp_val = this->builder->create_gep(rhs, tmp);
                }
            }
            break;
        }
        case SyntaxTree::BinOp::MINUS:
        {
            if ((Type::is_eq_type(lhsType, FLOAT_T)) ||
                Type::is_eq_type(rhsType, FLOAT_T))
            {
                // float减法
                if (!Type::is_eq_type(lhsType, FLOAT_T))
                { // lhs不是float型
                    DBGLOG("INT - FLOAT.");
                    if (Type::is_eq_type(lhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(lhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fsub(int_to_float, rhs);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(lhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fsub(int_to_float, rhs);
                    }
                }
                else if (!Type::is_eq_type(rhsType,
                                           FLOAT_T))
                { // rhs不是float型
                    DBGLOG("FLOAT - INT.");
                    if (Type::is_eq_type(rhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(rhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fsub(lhs, int_to_float);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(rhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fsub(lhs, int_to_float);
                    }
                }
                else
                {
                    DBGLOG("FLOAT - FLOAT.");
                    _exp_val = this->builder->create_fsub(lhs, rhs);
                }
            }
            else if (lhsType->is_integer_type() &&
                     rhsType->is_integer_type())
            {
                DBGLOG("INT - INT.");
                // int减法
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    // lhs是INT1，rhs是INT32
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_isub(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    // lhs是INT32，rhs是INT1
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_isub(lhs, int1_to_32);
                }
                else
                    _exp_val = this->builder->create_isub(lhs, rhs);
            }
            else
            {
                DBGLOG("PTR - ?.");
                // 如果是指针减，则只能是左操作数为指针，右操作数为int32
                std::vector<Value *> tmp;
                if (lhsType->is_pointer_type())
                {
                    tmp.push_back(rhs);
                    _exp_val = this->builder->create_gep(lhs, tmp);
                }
            }
            break;
        }
        case SyntaxTree::BinOp::MULTIPLY:
        {
            if ((Type::is_eq_type(lhsType, FLOAT_T)) ||
                Type::is_eq_type(rhsType, FLOAT_T))
            {
                // float乘法
                if (!Type::is_eq_type(lhsType, FLOAT_T))
                { // lhs不是float型
                    DBGLOG("INT * FLOAT.");
                    if (Type::is_eq_type(lhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(lhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fmul(int_to_float, rhs);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(lhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fmul(int_to_float, rhs);
                    }
                }
                else if (!Type::is_eq_type(rhsType,
                                           FLOAT_T))
                { // rhs不是float型
                    DBGLOG("FLOAT * INT.");
                    if (Type::is_eq_type(rhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(rhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fmul(lhs, int_to_float);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(rhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fmul(lhs, int_to_float);
                    }
                }
                else
                {
                    DBGLOG("FLOAT * FLOAT.");
                    _exp_val = this->builder->create_fmul(lhs, rhs);
                }
            }
            else if (lhsType->is_integer_type() &&
                     rhsType->is_integer_type())
            {
                // int乘法
                DBGLOG("INT * INT.");
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    // lhs是INT1，rhs是INT32
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_imul(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    // lhs是INT32，rhs是INT1
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_imul(lhs, int1_to_32);
                }
                else
                    _exp_val = this->builder->create_imul(lhs, rhs);
            }
            break;
        }
        case SyntaxTree::BinOp::DIVIDE:
        {
            if ((Type::is_eq_type(lhsType, FLOAT_T)) ||
                Type::is_eq_type(rhsType, FLOAT_T))
            {
                // float除法
                if (!Type::is_eq_type(lhsType, FLOAT_T))
                { // lhs不是float型
                    DBGLOG("INT / FLOAT.");
                    if (Type::is_eq_type(lhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(lhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fdiv(int_to_float, rhs);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(lhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fdiv(int_to_float, rhs);
                    }
                }
                else if (!Type::is_eq_type(rhsType,
                                           FLOAT_T))
                { // rhs不是float型
                    DBGLOG("FLOAT / INT.");
                    if (Type::is_eq_type(rhsType, INT1_T))
                    {
                        auto int1_to_32 =
                            this->builder->create_zext(rhs, INT32_T);
                        auto int_to_float =
                            this->builder->create_sitofp(int1_to_32, FLOAT_T);
                        _exp_val =
                            this->builder->create_fdiv(lhs, int_to_float);
                    }
                    else
                    {
                        auto int_to_float =
                            this->builder->create_sitofp(rhs, FLOAT_T);
                        _exp_val =
                            this->builder->create_fdiv(lhs, int_to_float);
                    }
                }
                else
                {
                    DBGLOG("FLOAT / FLOAT.");

                    _exp_val = this->builder->create_fdiv(lhs, rhs);
                }
            }
            else if (lhsType->is_integer_type() &&
                     rhsType->is_integer_type())
            {
                // int除法
                DBGLOG("INT / INT.");
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    // lhs是INT1，rhs是INT32
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_isdiv(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    // lhs是INT32，rhs是INT1
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_isdiv(lhs, int1_to_32);
                }
                else
                    _exp_val = this->builder->create_isdiv(lhs, rhs);
            }
            break;
        }
        case SyntaxTree::BinOp::MODULO:
        {
            if (lhsType->is_integer_type() && rhsType->is_integer_type())
            {
                DBGLOG("INT % INT.");
                // 取模运算只能是int类型
                if (Type::is_eq_type(lhsType, INT1_T) &&
                    Type::is_eq_type(rhsType, INT32_T))
                {
                    // lhs是INT1，rhs是INT32
                    auto int1_to_32 = this->builder->create_zext(lhs, INT32_T);
                    _exp_val = this->builder->create_isrem(int1_to_32, rhs);
                }
                else if (Type::is_eq_type(lhsType, INT32_T) &&
                         Type::is_eq_type(rhsType, INT1_T))
                {
                    // lhs是INT32，rhs是INT1
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_isrem(lhs, int1_to_32);
                }
                else
                    _exp_val = this->builder->create_isrem(lhs, rhs);
            }
            break;
        }
        }
    }
}

void IRBuilder::visit(SyntaxTree::UnaryExpr &node)
{
    /*生成0/0.0-node.rhs 返回到全局变量_exp_val*/
    if (scope.in_global()||_get_literal)
    {
        node.rhs->accept(*this);
        _global_val.cal(node.op);
    }
    else
    {
        node.rhs->accept(*this);
        Value *rhs = _exp_val;
        Type *rhsType = rhs->get_type();

        switch (node.op)
        {
        case SyntaxTree::UnaryOp::PLUS:
            // 如果是正号，_exp_val原本就存有该表达式的值，不需要另外的操作
            break;
        case SyntaxTree::UnaryOp::MINUS:
            if (rhsType->is_float_type())
            {
                // auto zero = ConstantFloat::get(0.0, module.get());
                auto zero = CONST_FLOAT(0.0);
                _exp_val = this->builder->create_fsub(zero, rhs);
            }
            else
            {
                // auto zero = ConstantInt::get(0, module.get());
                auto zero = CONST_INT(0);
                if (Type::is_eq_type(rhsType, INT1_T))
                {
                    auto int1_to_32 = this->builder->create_zext(rhs, INT32_T);
                    _exp_val = this->builder->create_isub(zero, int1_to_32);
                }
                else
                {
                    _exp_val = this->builder->create_isub(zero, rhs);
                }
            }
            break;
        }
    }
}

/*********************************/
//zyf
void IRBuilder::visit(SyntaxTree::ReturnStmt &node)
{
    /*获取全局：_ret_addr，检查node.ret*/
    /*modified by hkx*/
    auto funcRetType = builder->get_insert_block()->get_parent()->get_return_type();
    if (funcRetType->is_void_type())
    {
        //函数为VOID类型,直接返回空指令
        builder->create_br(_ret_bb);
        DBGLOG("VOID Func return.");
    }
    else if (node.ret == nullptr)
    {
        //函数非VOID，ret表达式为空，返回0/0.0
        builder->create_br(_ret_bb);
        DBGLOG("Func AUTO return 0.");
    }
    else
    {
        node.ret->accept(*this);
        //类型检查
        if (_exp_val->get_type() == INT1_T)
            _exp_val = builder->create_zext(_exp_val, INT1_T);
        if (_exp_val->get_type() != funcRetType)
        {
            if (funcRetType == FLOAT_T)
            {
                auto retVal = builder->create_sitofp(_exp_val, FLOAT_T);
                builder->create_store(retVal, _ret_addr);
                builder->create_br(_ret_bb);
                DBGLOG("Float Func return(transed).");
            }
            else
            {
                auto retVal = builder->create_fptosi(_exp_val, INT32_T);
                builder->create_store(retVal, _ret_addr);
                builder->create_br(_ret_bb);
                DBGLOG("Int Func return(transed).");
            }
        }
        else
        {
            builder->create_store(_exp_val, _ret_addr);
            builder->create_br(_ret_bb);
            DBGLOG("Func return.");
        }
    }

    /*old code:
    if (node.ret == NULL)
    {
        builder->create_void_ret();
    }
    else
    {
    auto ret_addr = _ret_addr;
    node.ret->accept(*this);
    auto ret_val = _exp_val;
    builder->create_store(ret_val, ret_addr);
    builder->create_ret(ret_val);
    }
    */
}

void IRBuilder::visit(SyntaxTree::BlockStmt &node)
{
    /*是否在函数内，不是第一次在则建立scope*/
    if (_first_in_func == true)
    {
        _first_in_func = false;
    }
    else
    {
        scope.enter();
    }
    for (auto stmt : node.body)
    {
        stmt->accept(*this);
    }
    scope.exit();
}

void IRBuilder::visit(SyntaxTree::IfStmt &node)
{
    char LabelName[20];
    auto func_parent = _func_parent;
    if (node.else_statement != nullptr)
    {
        sprintf(LabelName, "true_if_%d", _label_num++);
        auto true_if_bb = BasicBlock::create(module.get(), LabelName, func_parent);
        sprintf(LabelName, "false_if_%d", _label_num++);
        auto false_if_bb = BasicBlock::create(module.get(), LabelName, func_parent);
        sprintf(LabelName, "after_if_%d", _label_num++);
        auto after_if_bb = BasicBlock::create(module.get(), LabelName, func_parent);

        node.cond_exp->accept(*this);
        //check _exp_val type to i1(i32, float, i1, array(true), pointer(true))
        auto cond_exp_type = _exp_val->get_type();
        if (cond_exp_type->is_eq_type(cond_exp_type, INT1_T))
        {
            builder->create_cond_br(_exp_val, true_if_bb, false_if_bb);
        }
        else if (cond_exp_type->is_eq_type(cond_exp_type, INT32_T))
        {
            auto cond_i1 = builder->create_icmp_ne(_exp_val, CONST_INT(0));
            builder->create_cond_br(cond_i1, true_if_bb, false_if_bb);
        }
        else if (cond_exp_type->is_eq_type(cond_exp_type, FLOAT_T))
        {
            auto cond_i1 = builder->create_fcmp_ne(_exp_val, CONST_FLOAT(0));
            builder->create_cond_br(cond_i1, true_if_bb, false_if_bb);
        }
        else
        {
            builder->create_br(true_if_bb);
        }

        builder->set_insert_point(true_if_bb);
        node.if_statement->accept(*this);
        if (!(builder->get_insert_block()->get_terminator()))
            builder->create_br(after_if_bb);

        builder->set_insert_point(false_if_bb);
        node.else_statement->accept(*this);
        if (!(builder->get_insert_block()->get_terminator()))
            builder->create_br(after_if_bb);

        builder->set_insert_point(after_if_bb);
    }
    else
    {
        sprintf(LabelName, "true_if_%d", _label_num++);
        auto true_if_bb = BasicBlock::create(module.get(), LabelName, func_parent);
        sprintf(LabelName, "after_if_%d", _label_num++);
        auto after_if_bb = BasicBlock::create(module.get(), LabelName, func_parent);

        node.cond_exp->accept(*this);
        //check _exp_val type to i1(i32, float, i1, array(true), pointer(true))
        auto cond_exp_type = _exp_val->get_type();
        if (cond_exp_type->is_eq_type(cond_exp_type, INT1_T))
        {
            builder->create_cond_br(_exp_val, true_if_bb, after_if_bb);
        }
        else if (cond_exp_type->is_eq_type(cond_exp_type, INT32_T))
        {
            auto cond_i1 = builder->create_icmp_ne(_exp_val, CONST_INT(0));
            builder->create_cond_br(cond_i1, true_if_bb, after_if_bb);
        }
        else if (cond_exp_type->is_eq_type(cond_exp_type, FLOAT_T))
        {
            auto cond_i1 = builder->create_fcmp_ne(_exp_val, CONST_FLOAT(0));
            builder->create_cond_br(cond_i1, true_if_bb, after_if_bb);
        }
        else
        {
            builder->create_br(true_if_bb);
        }

        builder->set_insert_point(true_if_bb);
        node.if_statement->accept(*this);
        if (!(builder->get_insert_block()->get_terminator()))
            builder->create_br(after_if_bb);

        builder->set_insert_point(after_if_bb);
    }
}

void IRBuilder::visit(SyntaxTree::WhileStmt &node)
{
    /*栈实现的_break_addr
     栈实现的_continue_addr*/
    char LabelName[20];
    auto func_parent = _func_parent;
    sprintf(LabelName, "cond_while_%d", _label_num++);
    auto cond_while_bb = BasicBlock::create(module.get(), LabelName, func_parent);
    sprintf(LabelName, "true_while_%d", _label_num++);
    auto true_while_bb = BasicBlock::create(module.get(), LabelName, func_parent);
    sprintf(LabelName, "after_while_%d", _label_num++);
    auto after_while_bb = BasicBlock::create(module.get(), LabelName, func_parent);
    _break_addr.push_back(after_while_bb);
    _continue_addr.push_back(cond_while_bb);

    builder->create_br(cond_while_bb);

    builder->set_insert_point(cond_while_bb);
    node.cond_exp->accept(*this);
    auto cond_exp_type = _exp_val->get_type();
    if (cond_exp_type->is_eq_type(cond_exp_type, INT1_T))
    {
        builder->create_cond_br(_exp_val, true_while_bb, after_while_bb);
    }
    else if (cond_exp_type->is_eq_type(cond_exp_type, INT32_T))
    {
        auto cond_i1 = builder->create_icmp_ne(_exp_val, CONST_INT(0));
        builder->create_cond_br(cond_i1, true_while_bb, after_while_bb);
    }
    else if (cond_exp_type->is_eq_type(cond_exp_type, FLOAT_T))
    {
        auto cond_i1 = builder->create_fcmp_ne(_exp_val, CONST_FLOAT(0));
        builder->create_cond_br(cond_i1, true_while_bb, after_while_bb);
    }
    else
    {
        builder->create_br(true_while_bb);
    }
    //check _exp_val type to i1(i32, float, i1, array(true), pointer(true))

    builder->set_insert_point(true_while_bb);
    node.statement->accept(*this);
    if (!(builder->get_insert_block()->get_terminator()))
        builder->create_br(cond_while_bb);

    builder->set_insert_point(after_while_bb);

    _break_addr.pop_back();
    _continue_addr.pop_back();
}

void IRBuilder::visit(SyntaxTree::BreakStmt &node)
{
    char LabelName[20];
    auto func_parent = _func_parent;
    sprintf(LabelName, "after_break_%d", _label_num++);
    auto after_break_bb = BasicBlock::create(module.get(), LabelName, func_parent);

    auto break_target = _break_addr.back();
    builder->create_br(break_target);
    builder->set_insert_point(after_break_bb);
}

void IRBuilder::visit(SyntaxTree::ContinueStmt &node)
{
    char LabelName[20];
    auto func_parent = _func_parent;
    sprintf(LabelName, "after_cont_%d", _label_num++);
    auto after_cont_bb = BasicBlock::create(module.get(), LabelName, func_parent);

    auto cont_target = _continue_addr.back();
    builder->create_br(cont_target);
    builder->set_insert_point(after_cont_bb);
}
