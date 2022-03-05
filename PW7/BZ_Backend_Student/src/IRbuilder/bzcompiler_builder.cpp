#include "bzcompiler_builder.hpp"
#include <stack>

#define CONST(num) ConstantInt::get(num, &*module)
#define MEMSET_SIZE 40
#define _IRBUILDER_ERROR_(str)                                                  \
{                                                                               \
    std::cerr << "Error in IRbuilder-> " << str << std::endl;                   \
    std::abort();                                                               \
}

Type * TyInt32;
// store temporary value
Value *tmp_val = nullptr;
// detect scope pre-enter (for elegance only)
std::vector<Argument *> cur_fun_param;
int cur_fun_param_num = 0;
bool pre_enter_scope = false;
bool need_load = true;
int label_idx = 0;

BranchInst *builder_tmp_br;

std::string getNewLabel() {
    return "lb" + std::to_string(label_idx++);
}

Function * currentfunc;

std::stack<BasicBlock *> curIteration;
std::stack<BasicBlock *> curIterationExit;
std::stack<BasicBlock *> curIterationJudge;
Value *ret;
void BZBuilder::visit(ASTProgram &node) {
    TyInt32 = Type::get_int32_type(getModule());
    for(auto delc: node.getDeclareList()){
        delc->accept(*this);
    }
}
void BZBuilder::visit(ASTConstant &node)
{
    tmp_val = CONST(node.getValue());
}
void BZBuilder::visit(ASTUnaryOp &node)
{
    Value *val;
    node.getExpression()->accept(*this);
    val = tmp_val;
    if (need_load && val->get_type()->is_pointer_type()) {
        val = builder->create_load(val->get_type()->get_pointer_element_type(), val);
    }
    if (val->get_type()->is_int1_type()) {
        // 必定是从 Cmp 来的
        if (auto sub_cmp = dynamic_cast<CmpInst *>(val)) {
            switch (node.getUnaryOpType()) {
                case ASTUnaryOp::AST_OP_POSITIVE:
                    tmp_val = builder->create_zext(val, TyInt32);
                    break;
                case ASTUnaryOp::AST_OP_NEGATIVE:
                    val = builder->create_zext(val, TyInt32);
                    tmp_val = builder->create_isub(CONST(0), val);
                    break;
                case ASTUnaryOp::AST_OP_INVERSE:
                    sub_cmp->inverseCmpOp();
                    break;
            }
        } else {
            assert(0 && "Unknown runtime");
        }
    } else {
        switch (node.getUnaryOpType()) {
            case ASTUnaryOp::AST_OP_POSITIVE:
                // val = builder->create_iadd(CONST(0), val);
                // Do nothing
                break;
            case ASTUnaryOp::AST_OP_NEGATIVE:
                val = builder->create_isub(CONST(0), val);
                break;
            case ASTUnaryOp::AST_OP_INVERSE:
                val = builder->create_icmp_eq(val, CONST(0));
                builder_tmp_br = nullptr;
                break;
        }
        tmp_val = val;
    }
}

void BZBuilder::visit(ASTMulOp &node)
{
    if(node.isUnaryExp()) {
        node.getOperand1()->accept(*this);
        if (need_load && tmp_val->get_type()->is_pointer_type()) {
            tmp_val = builder->create_load(tmp_val->get_type()->get_pointer_element_type(), tmp_val);
        }
    }
    else
    {
        node.getOperand1()->accept(*this);
        auto l_val = tmp_val;
        node.getOperand2()->accept(*this);
        auto r_val = tmp_val;

        if (l_val->get_type()->is_pointer_type()) {
            l_val = builder->create_load(l_val->get_type()->get_pointer_element_type(), l_val);
        }

        if (l_val->get_type()->is_int1_type()) {
            l_val = builder->create_zext(l_val, TyInt32);
        }

        if (r_val->get_type()->is_pointer_type()) {
            r_val = builder->create_load(r_val->get_type()->get_pointer_element_type(), r_val);
        }

        if (r_val->get_type()->is_int1_type()) {
            r_val = builder->create_zext(r_val, TyInt32);
        }
        switch (node.getOpType()) {
            case ASTMulOp::AST_OP_MUL:
                tmp_val = builder->create_imul(l_val, r_val);
            break;
            case ASTMulOp::AST_OP_DIV:
                tmp_val = builder->create_isdiv(l_val, r_val);
            break;
            case ASTMulOp::AST_OP_MOD:
                tmp_val = builder->create_irem(l_val, r_val);
            break;
        }
    }
}
void BZBuilder::visit(ASTAddOp &node)
{
    if(node.isUnaryExp()) {
        node.getOperand1()->accept(*this);
        if (need_load && tmp_val->get_type()->is_pointer_type()) {
            tmp_val = builder->create_load(tmp_val->get_type()->get_pointer_element_type(), tmp_val);
        }
    }
    else
    {
        node.getOperand1()->accept(*this);
        auto l_val = tmp_val;
        node.getOperand2()->accept(*this);
        auto r_val = tmp_val;

        if (l_val->get_type()->is_pointer_type()) {
            l_val = builder->create_load(l_val->get_type()->get_pointer_element_type(), l_val);
        }
        
        if (l_val->get_type()->is_int1_type()) {
            l_val = builder->create_zext(l_val, TyInt32);
        }

        if (r_val->get_type()->is_pointer_type()) {
            r_val = builder->create_load(r_val->get_type()->get_pointer_element_type(), r_val);
        }

        if (r_val->get_type()->is_int1_type()) {
            r_val = builder->create_zext(r_val, TyInt32);
        }
        switch (node.getOpType()) {
            case ASTAddOp::AST_OP_ADD:
                tmp_val = builder->create_iadd(l_val, r_val);
            break;
            case ASTAddOp::AST_OP_MINUS:
                tmp_val = builder->create_isub(l_val, r_val);
            break;
        }
    }
}
void BZBuilder::visit(ASTRelOp &node)
{
    if (node.isUnaryExp()) {
        node.getOperand1()->accept(*this);
        node.setTrueList(node.getOperand1()->getTrueList());
        node.setFalseList(node.getOperand1()->getFalseList());
    }
    else {
        BranchInst *lhs = nullptr, *rhs = nullptr;
        node.getOperand1()->accept(*this);
        auto l_val = tmp_val;
        if (l_val->get_type()->is_pointer_type()) {
            l_val = builder->create_load(l_val->get_type()->get_pointer_element_type(), l_val);
        }

        if (l_val->get_type()->is_int1_type()) {
            l_val = builder->create_zext(l_val, TyInt32);
            lhs = builder_tmp_br;
        }
        node.getOperand2()->accept(*this);
        auto r_val = tmp_val;
        if (r_val->get_type()->is_pointer_type()) {
            r_val = builder->create_load(r_val->get_type()->get_pointer_element_type(), r_val);
        }

        if (r_val->get_type()->is_int1_type()) {
            r_val = builder->create_zext(r_val, TyInt32);
            rhs = builder_tmp_br;
        }


        if (lhs == nullptr && rhs != nullptr) {
            rhs->get_parent()->delete_instr(rhs);
        } else if (lhs != nullptr && rhs == nullptr) {
            lhs->get_parent()->delete_instr(lhs);
        }

        switch (node.getOpType()) {
            case ASTRelOp::AST_OP_LTE:
                tmp_val = builder->create_icmp_le(l_val, r_val);
                break;
            case ASTRelOp::AST_OP_LT:
                tmp_val = builder->create_icmp_lt(l_val, r_val);
                break;
            case ASTRelOp::AST_OP_GT:
                tmp_val = builder->create_icmp_gt(l_val, r_val);
                break;
            case ASTRelOp::AST_OP_GTE:
                tmp_val = builder->create_icmp_ge(l_val, r_val);
                break;
        }
        // 适配短路运算
        BasicBlock *t_bb = BasicBlock::create(getModule(), getNewLabel(), currentfunc, true);
        BasicBlock *f_bb = BasicBlock::create(getModule(), getNewLabel(), currentfunc, true);
        builder_tmp_br = builder->create_cond_br(tmp_val, t_bb, f_bb);
        node.pushTrue(t_bb);
        node.pushFalse(f_bb);
    }

}
void BZBuilder::visit(ASTEqOp &node)
{
    if (node.isUnaryExp()){
        node.getOperand1()->accept(*this);
        node.setTrueList(node.getOperand1()->getTrueList());
        node.setFalseList(node.getOperand1()->getFalseList());
    }
    else {
        BranchInst *lhs = nullptr, *rhs = nullptr;
        node.getOperand1()->accept(*this);
        auto l_val = tmp_val;
        if (l_val->get_type()->is_int1_type()) {
            l_val = builder->create_zext(l_val, TyInt32);
            lhs = builder_tmp_br;
        }
        node.getOperand2()->accept(*this);
        auto r_val = tmp_val;
        if (r_val->get_type()->is_int1_type()) {
            r_val = builder->create_zext(r_val, TyInt32);
            rhs = builder_tmp_br;
        }

        if (lhs == nullptr && rhs != nullptr) {
            rhs->get_parent()->delete_instr(rhs);
        } else if (lhs != nullptr && rhs == nullptr) {
            lhs->get_parent()->delete_instr(lhs);
        }

        switch (node.getOpType()) {
            case ASTEqOp::AST_OP_EQ:
                tmp_val = builder->create_icmp_eq(l_val, r_val);
                break;
            case ASTEqOp::AST_OP_NEQ:
                tmp_val = builder->create_icmp_ne(l_val, r_val);
                break;
        }
        // 适配短路运算
        BasicBlock *t_bb = BasicBlock::create(getModule(), getNewLabel(), currentfunc, true);
        BasicBlock *f_bb = BasicBlock::create(getModule(), getNewLabel(), currentfunc, true);
        builder->create_cond_br(tmp_val, t_bb, f_bb);
        node.pushTrue(t_bb);
        node.pushFalse(f_bb);
    }
}

void BZBuilder::visit(ASTAndOp &node)
{
    if (node.isUnaryExp()) {
        node.getOperand1()->accept(*this);
        if (node.getOperand1()->getTrueList().empty() && node.getOperand1()->getFalseList().empty()) {
            CmpInst *cod;
            if (tmp_val->get_type()->is_int1_type()) {
                // cod = builder->create_icmp_ne(CONST(false), tmp_val);
                cod = dynamic_cast<CmpInst *>(tmp_val);
                if (cod) {
                    // cod->inverseCmpOp();
                } else {
                    assert(0 && "Error simplify icmp");
                }
            } else {
                cod = builder->create_icmp_ne(CONST(0), tmp_val);
            }
            BasicBlock *t_bb = BasicBlock::create(getModule(), getNewLabel(), currentfunc, true);
            BasicBlock *f_bb = BasicBlock::create(getModule(), getNewLabel(), currentfunc, true);
            builder->create_cond_br(cod, t_bb, f_bb);
            node.pushTrue(t_bb);
            node.pushFalse(f_bb);
        } else {
            node.setTrueList(node.getOperand1()->getTrueList());
            node.setFalseList(node.getOperand1()->getFalseList());
        }
    }
    else {
        node.getOperand1()->accept(*this);
        auto l_val = tmp_val;
        /// 标号回填 B -> B1 and <b>M<\b> B2
        auto new_b = BasicBlock::create(getModule(), getNewLabel(), currentfunc);  // M.quad
        builder->set_insert_point(new_b);
        /// 标号回填阶段1结束
        node.getOperand2()->accept(*this);
        if (node.getOperand2()->getTrueList().empty() && node.getOperand2()->getFalseList().empty()) {
            auto cod = builder->create_icmp_ne(CONST(0), tmp_val);
            BasicBlock *t_bb = BasicBlock::create(getModule(), getNewLabel(), currentfunc, true);
            BasicBlock *f_bb = BasicBlock::create(getModule(), getNewLabel(), currentfunc, true);
            builder->create_cond_br(cod, t_bb, f_bb);
            node.getOperand2()->pushTrue(t_bb);
            node.getOperand2()->pushFalse(f_bb);
        } else {
            node.setTrueList(node.getOperand1()->getTrueList());
            node.setFalseList(node.getOperand1()->getFalseList());
        }

        /// 标号回填 B -> B1 and M <b>B2<\b>
        // Back patch B1.true_list with M.quad
        for (auto bb: node.getOperand1()->getTrueList()) {
            bb->replace_all_use_with(new_b);
        }
        // Merge Lists
        node.setTrueList(node.getOperand2()->getTrueList());
        node.setFalseList(node.getOperand1()->getFalseList());
        node.unionFalseList(node.getOperand2()->getFalseList());
        /// 标号回填阶段2结束
    }
}

void BZBuilder::visit(ASTOrOp &node)
{
    if (node.isUnaryExp())
    {
        node.getOperand1()->accept(*this);
        node.setTrueList(node.getOperand1()->getTrueList());
        node.setFalseList(node.getOperand1()->getFalseList());
    }
    else {
        node.getOperand1()->accept(*this);
        auto l_val = tmp_val;
        /// 标号回填 B -> B1 or <b>M<\b> B2
        auto new_b = BasicBlock::create(getModule(), getNewLabel(), currentfunc);  // M.quad
        builder->set_insert_point(new_b);
        /// 标号回填阶段1结束
        node.getOperand2()->accept(*this);
        auto r_val = tmp_val;
        /// 标号回填 B -> B1 or M <b>B2<\b>
        // Back patch B1.true_list with M.quad
        for (auto bb: node.getOperand1()->getFalseList()) {
            bb->replace_all_use_with(new_b);
        }
        // Merge Lists
        node.setTrueList(node.getOperand1()->getTrueList());
        node.unionTrueList(node.getOperand2()->getTrueList());
        node.setFalseList(node.getOperand2()->getFalseList());
        /// 标号回填阶段2结束
    }
}
void BZBuilder::visit(ASTLVal &node)
{
    std::string var_name = node.getVarName();
    std::vector<ASTAddOp *> pointer_exp= node.getPointerExpression();
    auto var = scope.find_var(var_name);
    if (var->get_type()->is_integer_type()) {
        tmp_val = var;
        return;
    }
    auto is_int = var->get_type()->get_pointer_element_type()->is_integer_type();
    auto is_ptr = var->get_type()->get_pointer_element_type()->is_pointer_type();
    if (pointer_exp.empty()) {
        if (is_int)
            tmp_val = scope.find_var(var_name);
        else if (is_ptr)
            tmp_val = builder->create_load(var);
        else
            tmp_val = builder->create_gep(var, {CONST(0)});
    }
    else
    {
        Value *tmp_ptr;
        if (is_ptr)
        {
            std::vector<Value *> array_params;
            scope.find_params(node.getVarName(), array_params);
            tmp_ptr = builder->create_load(var);
            for (int i = 0; i < pointer_exp.size(); i++)
            {
                pointer_exp[i]->accept(*this);
                auto val = tmp_val;
                for (int j = i + 1; j < array_params.size(); j++)
                {
                    val = builder->create_imul(val, array_params[j]);
                }
                tmp_ptr = builder->create_gep(tmp_ptr, {val});
            }
        }
        else
        {
            tmp_ptr = var;
            std::vector<Value *> idxs({CONST(0)});
            bool tmp_nl = need_load;
            need_load = true;
            for (auto exp : pointer_exp)
            {
                exp->accept(*this);
                idxs.push_back(tmp_val);
            }
            need_load = tmp_nl;
            tmp_ptr = builder->create_gep(tmp_ptr, idxs);
        }
        tmp_val = tmp_ptr;
    }
}
void BZBuilder::visit(ASTFuncCall &node)
{
    auto func_name = scope.find_func(node.getFunctionName());
    if (func_name == nullptr)
        exit(120);
    std::vector<Value *> args;
    std::vector<ASTAddOp *> params=node.getParamList();

    for (int i = 0; i < params.size(); i++) {
        auto arg = params[i];
        auto arg_type =
                dynamic_cast<Function *>(func_name)->get_function_type()->get_param_type(i);

        if (!arg_type->is_integer_type()){
            need_load = false;
            arg->accept(*this);
            std::vector<Value *> idxs;
            Type *ty = tmp_val->get_type();
            while (ty->is_pointer_type() || ty->is_array_type()) {
                idxs.push_back(CONST(0));
                if (ty->is_pointer_type()) {
                    ty = ty->get_pointer_element_type();
                } else {
                    ty = ty->get_array_element_type();
                }
            }
            tmp_val = builder->create_gep(tmp_val, idxs);
            need_load = true;
        } else {
            arg->accept(*this);
        }
        args.push_back(tmp_val);
    }

    tmp_val = builder->create_call(dynamic_cast<Function *>(func_name), args);
}

int BZBuilder::compute_ast_constant(ASTInstruction *inst) {
    switch (inst->getType()) {
        case AST_CONSTANT:
            return dynamic_cast<ASTConstant *>(inst)->getValue();
        case AST_ADD_EXP: {
            auto *op = dynamic_cast<ASTAddOp *>(inst);
            if (op->isUnaryExp()) {
                return compute_ast_constant(op->getOperand1());
            } else {
                int lhs = compute_ast_constant(op->getOperand1());
                int rhs = compute_ast_constant(op->getOperand2());
                if (op->getOpType() == ASTAddOp::AST_OP_ADD) {
                    return lhs + rhs;
                } else {
                    return lhs - rhs;
                }
            }
        }
        case AST_MUL_EXP: {
            auto *op = dynamic_cast<ASTMulOp *>(inst);
            if (op->isUnaryExp()) {
                return compute_ast_constant(op->getOperand1());
            } else {
                int lhs = compute_ast_constant(op->getOperand1());
                int rhs = compute_ast_constant(op->getOperand2());
                switch (op->getOpType()) {
                    case ASTMulOp::AST_OP_DIV:
                        return lhs / rhs;
                    case ASTMulOp::AST_OP_MUL:
                        return lhs * rhs;
                    case ASTMulOp::AST_OP_MOD:
                        return lhs % rhs;
                }
            }
        }
        case AST_OR_EXP: {
            auto *op = dynamic_cast<ASTOrOp *>(inst);
            if (op->isUnaryExp()) {
                return compute_ast_constant(op->getOperand1());
            } else {
                int lhs = compute_ast_constant(op->getOperand1());
                int rhs = compute_ast_constant(op->getOperand2());
                return lhs || rhs;
            }
        }
        case AST_AND_EXP: {
            auto *op = dynamic_cast<ASTAndOp *>(inst);
            if (op->isUnaryExp()) {
                return compute_ast_constant(op->getOperand1());
            } else {
                int lhs = compute_ast_constant(op->getOperand1());
                int rhs = compute_ast_constant(op->getOperand2());
                return lhs && rhs;
            }
        }
        case AST_EQ_EXP: {
            auto *op = dynamic_cast<ASTEqOp *>(inst);
            if (op->isUnaryExp()) {
                return compute_ast_constant(op->getOperand1());
            } else {
                int lhs = compute_ast_constant(op->getOperand1());
                int rhs = compute_ast_constant(op->getOperand2());
                switch (op->getOpType()) {
                    case ASTEqOp::AST_OP_EQ:
                        return lhs == rhs;
                    case ASTEqOp::AST_OP_NEQ:
                        return lhs != rhs;
                }
            }
        }
        case AST_REL_EXP: {
            auto *op = dynamic_cast<ASTRelOp *>(inst);
            if (op->isUnaryExp()) {
                return compute_ast_constant(op->getOperand1());
            } else {
                int lhs = compute_ast_constant(op->getOperand1());
                int rhs = compute_ast_constant(op->getOperand2());
                switch (op->getOpType()) {
                    case ASTRelOp::AST_OP_GT:
                        return lhs > rhs;
                    case ASTRelOp::AST_OP_GTE:
                        return lhs >= rhs;
                    case ASTRelOp::AST_OP_LT:
                        return lhs < rhs;
                    case ASTRelOp::AST_OP_LTE:
                        return lhs <= rhs;
                }
            }
        }
        case AST_UNARY_EXP: {
            auto *op = dynamic_cast<ASTUnaryOp *>(inst);
            int lhs = compute_ast_constant(op->getExpression());
            switch (op->getUnaryOpType()) {
                case ASTUnaryOp::AST_OP_NEGATIVE:
                    return -lhs;
                case ASTUnaryOp::AST_OP_POSITIVE:
                    return lhs;
                case ASTUnaryOp::AST_OP_INVERSE:
                    return !lhs;
            }
        }
        case AST_LVAL: {
            auto *op = dynamic_cast<ASTLVal *>(inst);
            std::string var_name = op->getVarName();
            if (op->hasAddress()) {
                std::vector<int> pointer;
                for (ASTAddOp *aop: op->getPointerExpression()) {
                    pointer.push_back(compute_ast_constant(aop));
                }
                return scope.getValue(var_name, pointer);
            }
            return scope.getValue(var_name);
        }
        default:
            assert(0 && "Not a compile-time calculable expression.");
    }
}

/**
 * 递归数组初始化
 * @param l
 * @param offset
 * @param depth
 * @param init_values
 * @return 当前块填充的数量
 */
std::tuple<int, int> BZBuilder::ConstInitialValueWalker(ASTVarDecl::ASTArrayList *l, const std::vector<int> &dim, int depth,
                                   std::vector<int> &init_values) {
    int align = dim[dim.size() - 1];
    int inited = 0;
    int max_depth = depth;
    for (auto it: l->list) {
        if (it->isArray) {
            int tb_fill = inited % align;
            for(int i = 0; i < tb_fill; ++i) {
                init_values.push_back(0);
                ++inited;
            }
            int _dp, _filled;
            std::tie(_dp, _filled) = ConstInitialValueWalker(it, dim, depth + 1, init_values);
            inited += _filled;
            max_depth = std::max(max_depth, _dp);
        } else {
            ++inited;
            init_values.push_back(compute_ast_constant(it->value));
        }
    }
    int total_fill = 1;
    for(int i = 0; i <= max_depth - depth; ++i) {
        total_fill *= dim[dim.size() - 1 - i];
    }
    for(int i = inited; i < total_fill; ++i) {
        init_values.push_back(0);
        ++inited;
    }
    if(depth == 0) {
        int tbfill = 1;
        for(int i : dim) {
            tbfill *= i;
        }
        for(int i = inited; i < tbfill; ++i) {
            init_values.push_back(0);
        }
    }
    return {max_depth, inited};
}


std::tuple<int, int> BZBuilder::InitialValueWalker(ASTVarDecl::ASTArrayList *l, const std::vector<int> &dim, int depth,
                                   std::vector<Value *> &init_values, Module *m) {
    int align = dim[dim.size() - 1];
    int inited = 0;
    int max_depth = depth;
    for (auto it: l->list) {
        if (it->isArray) {
            int tb_fill = inited % align;
            for(int i = 0; i < tb_fill; ++i) {
                init_values.push_back(CONST(0));
                ++inited;
            }
            int _dp, _filled;
            std::tie(_dp, _filled) = InitialValueWalker(it, dim, depth + 1, init_values, m);
            inited += _filled;
            max_depth = std::max(max_depth, _dp);
        } else {
            ++inited;
            it->value->accept(*this);
            init_values.push_back(tmp_val);
        }
    }
    int total_fill = 1;
    for(int i = 0; i <= max_depth - depth; ++i) {
        total_fill *= dim[dim.size() - 1 - i];
    }
    for(int i = inited; i < total_fill; ++i) {
        init_values.push_back(CONST(0));
        ++inited;
    }
    if(depth == 0) {
        int tbfill = 1;
        for(int i : dim) {
            tbfill *= i;
        }
        for(int i = inited; i < tbfill; ++i) {
            init_values.push_back(CONST(0));
        }
    }
    return {max_depth, inited};
}

void BZBuilder::InitialValueBuilder(const std::vector<int> &dim, const std::vector<Value *> &val, Instruction *gep, int &offset, int depth, int totalSize) {
    for (int i = 0; i < dim[depth]; ++i) {
        auto g_i = builder->create_gep(gep, {CONST(0), ConstantInt::get(i, getModule())});
        if (depth != dim.size() - 1) {
            InitialValueBuilder(dim, val, g_i, offset, depth + 1, totalSize);
        } else {
            if (auto ci = dynamic_cast<ConstantInt *>(val[offset])) {
                if (ci->get_value() != 0 || totalSize < MEMSET_SIZE) {
                    builder->create_store(val[offset], g_i);
                }
            } else {
                builder->create_store(val[offset], g_i);
            }
            offset+=1;
        }
    }
}

ArrayType* getArrayTypeByDimension(const std::vector<int> &dim) {
    assert(!dim.empty() && "Dimension should not be empty");
    Type *ty = TyInt32;
    for(int i = (int)dim.size() - 1; i >= 0; --i) {
        ty = ArrayType::get(ty, dim[i]);
    }
    return dynamic_cast<ArrayType *>(ty);
}

std::vector<Constant *> BZBuilder::int2constant(const std::vector<int> &ori) {
    std::vector<Constant *> cons;
    for (int it: ori) {
        cons.push_back(ConstantInt::get(it, getModule()));
    }
    return cons;
}

std::vector<Value *> BZBuilder::int2value(const std::vector<int> &ori) {
    std::vector<Value *> cons;
    for (int it: ori) {
        cons.push_back(ConstantInt::get(it, getModule()));
    }
    return cons;
}

void BZBuilder::visit(ASTVarDecl &node) {
    for (ASTVarDecl::ASTVarDeclInst *it: node.getVarDeclList()) {
        std::vector<int> dimension;  // 只要是数组就有
        ArrayType* arr_ty;
        if (it->array) {
            for (auto d: it->_array_list) {
                dimension.push_back(compute_ast_constant(d));
            }
            arr_ty = getArrayTypeByDimension(dimension);
        }
        if (node.isConst()) {
            // 常量处理
            if (scope.in_global()) {
                // 全局量
                if (it->array) {
                    std::vector<int> init;
                    ConstInitialValueWalker(it->initial_value[0], dimension, 0, init);
                    auto gv = GlobalVariable::create(it->var_name, getModule(), arr_ty, true, ConstantArray::get(arr_ty, ConstantArray::IntegerList2Constant(dimension, init, getModule())));
                    gv->setFlattenInit(init);
                    scope.pushVar(it->var_name, gv, true, dimension, init);
                } else {
                    int scala_init = compute_ast_constant(it->initial_value[0]->value);
                    auto gv = GlobalVariable::create(it->var_name, getModule(), TyInt32, true, CONST(scala_init));
                    scope.pushVar(it->var_name, gv, true, {}, {scala_init});
                }
            } else {
                // 局部量
                if (it->array) {
                    std::vector<int> init;
                    int off = 0;
                    ConstInitialValueWalker(it->initial_value[0], dimension, 0, init);
                    int size = 1;
                    for (auto i: dimension) {
                        size *= i;
                    }
                    auto lv = builder->create_alloca(arr_ty);
                    if (size > MEMSET_SIZE) {
                        auto ms_func = scope.find_func("memset");
                        std::vector<Value *> idxs;
                        Type *ty = lv->get_type();
                        while (ty->is_pointer_type() || ty->is_array_type()) {
                            idxs.push_back(CONST(0));
                            if (ty->is_pointer_type()) {
                                ty = ty->get_pointer_element_type();
                            } else {
                                ty = ty->get_array_element_type();
                            }
                        }
                        auto lv2 = builder->create_gep(lv, idxs);
                        // builder->create_gep(lv, {CONST(0), CONST(0)});
                        builder->create_call(ms_func, {lv2, CONST(0), CONST(size * 4)});
                    }
                    InitialValueBuilder(dimension, int2value(init), lv, off, 0, size);
                    scope.pushVar(it->var_name, lv, true, dimension, init);
                } else {
                    int scala_init = compute_ast_constant(it->initial_value[0]->value);
                    auto ptr = builder->create_alloca(TyInt32);
                    builder->create_store(CONST(scala_init), ptr);
                    scope.pushVar(it->var_name, ptr, true, {}, {scala_init});
                }
            }
        } else {
            // 变量处理
            if (scope.in_global()) {
                // 全局量
                if (it->array) {
                    if (it->has_initial) {
                        std::vector<int> init;
                        ConstInitialValueWalker(it->initial_value[0], dimension, 0, init);
                        auto gv = GlobalVariable::create(it->var_name, getModule(), arr_ty, false, ConstantArray::get(arr_ty, ConstantArray::IntegerList2Constant(dimension, init, getModule())));
                        gv->setFlattenInit(init);
                        scope.pushVar(it->var_name, gv, false, dimension, init);
                    } else {
                        auto gv = GlobalVariable::create(it->var_name, getModule(), arr_ty, false, ConstantZero::get(arr_ty, getModule()));
                        scope.pushVar(it->var_name, gv, false, dimension);
                    }
                } else {
                    if (it->has_initial) {
                        int scala_init = compute_ast_constant(it->initial_value[0]->value);
                        auto gv = GlobalVariable::create(it->var_name, getModule(), TyInt32, false, CONST(scala_init));
                        scope.pushVar(it->var_name, gv, false);
                    } else {
                        auto gv = GlobalVariable::create(it->var_name, getModule(), TyInt32, false, CONST(0));
                        scope.pushVar(it->var_name, gv, false);
                    }
                }
            } else {
                // 局部量
                if (it->array) {
                    auto lv = builder->create_alloca(arr_ty);
                    if(it->has_initial) {
                        std::vector<Value *> init;
                        int off = 0;
                        InitialValueWalker(it->initial_value[0], dimension, 0, init, getModule());
                        int size = 1;
                        for (auto i: dimension) {
                            size *= i;
                        }
                        if (size > MEMSET_SIZE) {
                            auto ms_func = scope.find_func("memset");
                            std::vector<Value *> idxs;
                            Type *ty = lv->get_type();
                            while (ty->is_pointer_type() || ty->is_array_type()) {
                                idxs.push_back(CONST(0));
                                if (ty->is_pointer_type()) {
                                    ty = ty->get_pointer_element_type();
                                } else {
                                    ty = ty->get_array_element_type();
                                }
                            }
                            auto lv2 = builder->create_gep(lv, idxs);
                            // builder->create_gep(lv, {CONST(0), CONST(0)});
                            builder->create_call(ms_func, {lv2, CONST(0), CONST(size * 4)});
                        }
                        InitialValueBuilder(dimension, init, lv, off, 0, size);
                    }
                    scope.pushVar(it->var_name, lv, false, dimension);
                } else {
                    auto ptr = builder->create_alloca(TyInt32);
                    if(it->has_initial) {
                        it->initial_value[0]->value->accept(*this);
                        builder->create_store(tmp_val, ptr);
                    }
                    scope.pushVar(it->var_name, ptr, false);
                }
            }
        }
    }

}
void BZBuilder::visit(ASTFuncDecl &node){
    auto ret_type = node.getFunctionType();
    Type* fun_ret_type;
    if(ret_type == node.AST_RET_INT){
        fun_ret_type = Type::get_int32_type(getModule());
    }
    else{
        fun_ret_type = Type::get_void_type(getModule());
    }
    auto params = node.getParams();
    std::vector<Type *> args;
    std::vector<Value *> fun_args;
    for(auto param : params){
        if(param->isArray()){
            args.push_back(Type::get_int32_ptr_type(getModule()));
        }
        else{
            args.push_back(Type::get_int32_type(getModule()));
        }
    }
    auto fun_type = FunctionType::get(fun_ret_type, args);
    auto fun =  Function::create(fun_type, node.getFunctionName(), getModule());
    auto bb = BasicBlock::create(getModule(), "entry", fun);
    builder->set_insert_point(bb);
    scope.pushFunction(node.getFunctionName(), fun);
    scope.enter();
    cur_fun_param.clear();
    currentfunc = fun;
    cur_fun_param_num = 0;
    auto fun_param = fun->get_args();
    for(auto & it : fun_param) {
        cur_fun_param.push_back(it);
    }
    for(auto param: params){
        param->accept(*this);
        cur_fun_param_num ++;
    }
    auto block = node.getStmtBlock();
    block->accept(*this);
    scope.exit();
}

void BZBuilder::visit(ASTParam &node){
    if(node.isArray()){
        auto array_alloca = builder->create_alloca(Type::get_int32_ptr_type(getModule()));
        auto param = cur_fun_param[cur_fun_param_num];
        builder->create_store(param, array_alloca);
        std::vector<Value *> array_params;
        array_params.push_back(ConstantInt::get(0, getModule()));
        for (auto array_param : node.getArrayList()) {
            array_param->accept(*this);
            array_params.push_back(tmp_val);
        }
        scope.pushVar(node.getParamName(), array_alloca);
        scope.push_params(node.getParamName(), array_alloca, array_params);
    }
    else{
        auto alloca = builder->create_alloca(Type::get_int32_type(getModule()));
        auto params = node.getArrayList();
        builder->create_store(cur_fun_param[cur_fun_param_num], alloca);
        scope.pushVar(node.getParamName(), alloca);
    }
}

void BZBuilder::visit(ASTAssignStmt &node) {
    node.getLeftValue()->accept(*this);
    auto assign_addr=tmp_val;
    node.getExpression()->accept(*this);
    auto assign_value=tmp_val;
    if (assign_addr->get_type()->is_pointer_type()) {
        builder->create_store(assign_value, assign_addr);
    }
}
void BZBuilder::visit(ASTExpressionStmt &node) {
    if (node.isValidExpression())
        node.getExpression()->accept(*this);
}
void BZBuilder::visit(ASTIfStmt &node) {
    auto tmp=builder->get_insert_block();
    if (node.hasElseStatement()){
        auto trueBB=BasicBlock::create(module,getNewLabel(),currentfunc);
        auto falseBB=BasicBlock::create(module,getNewLabel(),currentfunc);
        auto exitBB=BasicBlock::create(module,getNewLabel(),currentfunc);
        builder->set_insert_point(tmp);
        node.getCondition()->accept(*this);
        builder->set_insert_point(trueBB);
        node.getTrueStatement()->accept(*this);

        /// 标号回填
        // 两个list都为空，说明是ASTAdd指令传上来的
        if (node.getCondition()->getTrueList().empty() && node.getCondition()->getFalseList().empty()) {
            builder->set_insert_point(tmp);
            auto cod = builder->create_icmp_eq(CONST(0), tmp_val);
            builder->create_cond_br(cod, trueBB, falseBB);
        }
        // back patch B.true_list with M1.quad
        for (auto bb: node.getCondition()->getTrueList()) {
            bb->replace_all_use_with(trueBB);
        }
        // back patch B.false_list with M2.quad
        for (auto bb: node.getCondition()->getFalseList()) {
            bb->replace_all_use_with(falseBB);
        }
        /// 标号回填结束

        bool isReturned=true;
        if (builder->get_insert_block()->get_terminator()==nullptr){
            builder->create_br(exitBB);
            isReturned=false;
        }
        builder->set_insert_point(falseBB);
        node.getFalseStatement()->accept(*this);
        if (builder->get_insert_block()->get_terminator()==nullptr){
            builder->create_br(exitBB);
            isReturned=false;
        }
        builder->set_insert_point(exitBB);
    }
    else{
        auto trueBB=BasicBlock::create(module,getNewLabel(),currentfunc);  // M.quad
        auto exitBB=BasicBlock::create(module,getNewLabel(),currentfunc);  // NextList回填目标
        builder->set_insert_point(tmp);
        node.getCondition()->accept(*this);
        // builder->create_cond_br(ret,trueBB,exitBB);
        /// 标号回填
        // back patch B.true_list with M.quad
        for (auto bb: node.getCondition()->getTrueList()) {
            bb->replace_all_use_with(trueBB);
        }
        // back patch B.false_list (node.next_list) with exit.quad
        for (auto bb: node.getCondition()->getFalseList()) {
            bb->replace_all_use_with(exitBB);
        }
        /// 标号回填结束
        builder->set_insert_point(trueBB);
        node.getTrueStatement()->accept(*this);
        bool isReturned=true;
        if (builder->get_insert_block()->get_terminator()==nullptr){
            builder->create_br(exitBB);
            isReturned=false;
        }
        builder->set_insert_point(exitBB);
    }
}
void BZBuilder::visit(ASTWhileStmt &node) {
    auto tmp=builder->get_insert_block();
    auto judgebb=BasicBlock::create(module,getNewLabel(),currentfunc);
    auto iteratebb=BasicBlock::create(module,getNewLabel(),currentfunc);
    auto exitbb=BasicBlock::create(module,getNewLabel(),currentfunc);
    builder->set_insert_point(tmp);
    builder->create_br(judgebb);
    builder->set_insert_point(judgebb);
    node.getCondition()->accept(*this);
    // builder->create_cond_br(tmp_val,iteratebb,exitbb);

    builder->set_insert_point(iteratebb);
    curIteration.push(iteratebb);
    curIterationExit.push(exitbb);
    curIterationJudge.push(judgebb);
    node.getWhileBodyStatement()->accept(*this);
    builder->create_br(judgebb);
    builder->set_insert_point(exitbb);
    curIteration.pop();
    curIterationExit.pop();
    curIterationJudge.pop();
    /// 标号回填
    // 两个list都为空，说明是ASTAdd指令传上来的
    if (node.getCondition()->getTrueList().empty() && node.getCondition()->getFalseList().empty()) {
        builder->set_insert_point(tmp);
        auto cod = builder->create_icmp_eq(CONST(0), tmp_val);
        builder->create_cond_br(cod, iteratebb, exitbb);
    }
    // back patch B.true_list with M.quad
    for (auto bb: node.getCondition()->getTrueList()) {
        bb->replace_all_use_with(iteratebb);
    }
    // back patch B.false_list (node.next_list) with exit.quad
    for (auto bb: node.getCondition()->getFalseList()) {
        bb->replace_all_use_with(exitbb);
    }
    /// 标号回填结束
}
void BZBuilder::visit(ASTBreakStmt &node) {
    builder->create_br(curIterationExit.top());
}
void BZBuilder::visit(ASTContinueStmt &node) {
    builder->create_br(curIterationJudge.top());
}

void BZBuilder::visit(ASTReturnStmt &node) {
    if (node.hasReturnValue()) {
        node.getRetExpression()->accept(*this);
        builder->create_ret(tmp_val);
    } else {
        builder->create_void_ret();
    }
}
void BZBuilder::visit(ASTBlock &node) {
    bool need_exit_scope = !pre_enter_scope;
    if (pre_enter_scope) {
        pre_enter_scope = false;
    } else {
        scope.enter();
    }
    for (auto exp: node.getStatements()) {
        exp->accept(*this);
    }
    if (need_exit_scope) {
        scope.exit();
    }
}
