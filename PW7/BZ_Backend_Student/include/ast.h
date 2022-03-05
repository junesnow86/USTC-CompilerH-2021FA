// 抽象语法树生成类
// 用于将BISON输出的语法树进行展平操作 (Flatten the AST)
//

#ifndef BAZINGA_COMPILER_AST_H
#define BAZINGA_COMPILER_AST_H

#include "syntax_tree.h"
#include "IR/BasicBlock.h"
#include <algorithm>
#include <utility>

/*
 * @brief 抽象语法树入口类 \n
 * 该类提供AST的入口，每个语法分析树对应一个Program
 */

class ASTvisitor;

enum AST_INST_TYPE {
    AST_CONSTANT,
    AST_MUL_EXP,
    AST_ADD_EXP,
    AST_REL_EXP,
    AST_AND_EXP,
    AST_OR_EXP,
    AST_EQ_EXP,
    AST_UNARY_EXP,
    AST_FUNC_CALL,
    AST_LVAL,
    AST_FUNCTION_DECL,
    AST_VARIABLE_DECL,
    AST_IF_STMT,
    AST_WHILE_STMT,
    AST_CONTINUE_STMT,
    AST_BREAK_STMT,
    AST_ASSIGN_STMT,
    AST_RETURN_STMT,
    AST_EXPRESSION_STMT,
    AST_BLOCK_STMT
};

class IShortCalc {
private:
    std::vector<BasicBlock *> _true_list;
    std::vector<BasicBlock *> _false_list;
public:
    std::vector<BasicBlock *> getTrueList() { return _true_list; }
    std::vector<BasicBlock *> getFalseList() { return _false_list; }
    void pushTrue(BasicBlock *bb) { _true_list.push_back(bb); }
    void pushFalse(BasicBlock *bb) { _false_list.push_back(bb); }
    void setTrueList(const std::vector<BasicBlock *> &list) { _true_list = list; }
    void setFalseList(const std::vector<BasicBlock *> &list) { _false_list = list; }
    void unionTrueList( const std::vector<BasicBlock *> &list) { _true_list.insert(_true_list.end(), list.begin(), list.end()); }
    void unionFalseList( const std::vector<BasicBlock *> &list) { _false_list.insert(_false_list.end(), list.begin(), list.end()); }
};

class ASTInstruction : public IShortCalc {
private:
    AST_INST_TYPE _inst_type;

public:
    virtual void accept(ASTvisitor &) {};
    explicit ASTInstruction(AST_INST_TYPE type) {
        _inst_type = type;
    }

    AST_INST_TYPE getType() {
        return _inst_type;
    }

    virtual void print(int depth) {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }
    }
};

class ASTConstant : public ASTInstruction {
private:
    int _value;
public:
    void accept(ASTvisitor &) final;
    explicit ASTConstant(TreeNode *t) : ASTInstruction(AST_CONSTANT) {
        assert(t != nullptr && t->node_type == AST_INT_CONST && "ASTConstant got invalid TreeNode pointer");
        if (t->node_name[0] == '0') {
            if (t->node_name.length() == 1) {
                _value = 0;
                return;
            }
            if (t->node_name[1] == 'x' || t->node_name[1] == 'X') {
                // 16进制数
                _value = 0;
                for (int i = 2; i < t->node_name.length(); ++i) {
                    int digit;
                    char num = t->node_name[i];
                    if ('0' <= num && num <= '9') {
                        digit = num - '0';
                    } else if ('a' <= num && num <= 'f') {
                        digit = num - 'a' + 10;
                    } else if ('A' <= num && num <= 'F') {
                        digit = num - 'A' + 10;
                    } else {
                        assert(0 && "Got unrecognizable digit");
                    }
                    _value = 16 * _value + digit;
                }
            } else {
                // 8进制数
                _value = 0;
                for (int i = 1; i < t->node_name.length(); ++i) {
                    int digit;
                    char num = t->node_name[i];
                    if ('0' <= num && num <= '7') {
                        digit = num - '0';
                    } else {
                        assert(0 && "Got unrecognizable digit");
                    }
                    _value = 8 * _value + digit;
                }
            }
        } else {
            // 10进制数
            _value = std::atoi(t->node_name.c_str());
        }
    }

    /**
     * 获取当前结点的常量值
     * @return 常数结点的数值
     */
    int getValue() const {
        return _value;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Constant[" << getValue() << "]" << std::endl;
    }
};

/**
 * 此处的UnaryExp特指 +/-/! UnaryExp 类型的表达式
 * 与 parser 的定义略有不同
 */
class ASTUnaryOp : public ASTInstruction {
public:
    void accept(ASTvisitor &) final;
    enum AST_UNARY_OP_TYPE {
        AST_OP_POSITIVE,    // +
        AST_OP_NEGATIVE,    // -
        AST_OP_INVERSE      // !
    };
private:
    AST_UNARY_OP_TYPE _op_type;
    ASTInstruction *_sub_exp;

public:
    explicit ASTUnaryOp(TreeNode *t);

    ASTInstruction *getExpression() {
        return _sub_exp;
    }

    AST_UNARY_OP_TYPE getUnaryOpType() {
        return _op_type;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Unary Expression[Op: ";
        switch (getUnaryOpType()) {
            case AST_OP_INVERSE:
                std::cout << '!';
                break;
            case AST_OP_POSITIVE:
                std::cout << '+';
                break;
            case AST_OP_NEGATIVE:
                std::cout << '-';
                break;
        }
        std::cout << ']' << std::endl;
        getExpression()->print(depth);
    }

    static ASTInstruction *getUnaryOp(TreeNode *t);
};

class ASTMulOp : public ASTInstruction {
public:
    enum AST_MUL_OP_TYPE {
        AST_OP_MUL,
        AST_OP_DIV,
        AST_OP_MOD
    };
private:
    bool _is_unary;
    ASTInstruction *l_op;
    ASTInstruction *r_op;
    AST_MUL_OP_TYPE _tp;

public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTMulOp(TreeNode *t) : ASTInstruction(AST_MUL_EXP) {
        assert(t != nullptr && t->node_type == AST_mulexp && "ASTMulExpression got invalid TreeNode.");
        _is_unary = t->children.size() == 1;
        if (_is_unary) {
            l_op = ASTUnaryOp::getUnaryOp(t->children[0]);
        } else {
            l_op = new ASTMulOp(t->children[0]);
            r_op = ASTUnaryOp::getUnaryOp(t->children[2]);
            switch (t->children[1]->node_type) {
                case AST_MUL:
                    _tp = AST_OP_MUL;
                    break;
                case AST_DIV:
                    _tp = AST_OP_DIV;
                    break;
                case AST_MOD:
                    _tp = AST_OP_MOD;
                    break;
                default:
                    assert(0 && "ASTMulOp got invalid Operand Type.");
            }
        }
    }

    /**
     * 判断是否是二元操作结点
     */
    bool isUnaryExp() const {
        return _is_unary;
    }


    /**
     * 获取第一个操作数
     * 语法树正确的情况下，返回的指针任保证是有效的
     */
    ASTInstruction *getOperand1() const {
        return l_op;
    }

    /**
     * 获取第二个操作数
     * 仅当 {@see ASTAddOp::isUnaryExp} 为false时有效，否则返回空指针
     */
    ASTInstruction *getOperand2() const {
        return r_op;
    }

    /**
     * 获取运算类型
     * 仅当 {@see ASTAddOp::isUnaryExp} 为false时有效，否则返回结果不可预测
     */
    AST_MUL_OP_TYPE getOpType() const {
        return _tp;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Multiply Expression[";
        if (isUnaryExp()) {
            std::cout << "Unary]" << std::endl;
            getOperand1()->print(depth + 1);
        } else {
            std::cout << "Op: ";
            switch (getOpType()) {
                case AST_OP_MUL:
                    std::cout << '*';
                    break;
                case AST_OP_MOD:
                    std::cout << '%';
                    break;
                case AST_OP_DIV:
                    std::cout << '/';
                    break;
            }
            std::cout << ']' << std::endl;
            getOperand1()->print(depth + 1);
            getOperand2()->print(depth + 1);
        }
    }

};

class ASTAddOp : public ASTInstruction {
public:
    virtual void accept(ASTvisitor &) override final;
    enum AST_ADD_OP_TYPE {
        AST_OP_ADD,
        AST_OP_MINUS
    };
private:
    TreeNode *_root;
    bool _is_unary;
    ASTInstruction *l_op;
    ASTInstruction *r_op;
    AST_ADD_OP_TYPE _tp;
public:
    explicit ASTAddOp(TreeNode *t) : ASTInstruction(AST_ADD_EXP) {
        assert(t != nullptr && t->node_type == AST_addexp && "ASTAddExpression got invalid TreeNode.");
        _root = t;
        _is_unary = _root->children.size() == 1;
        if (_is_unary) {
            l_op = new ASTMulOp(_root->children[0]);
        } else {
            l_op = new ASTAddOp(_root->children[0]);
            r_op = new ASTMulOp(_root->children[2]);
            switch (_root->children[1]->node_type) {
                case AST_ADD:
                    _tp = AST_OP_ADD;
                    break;
                case AST_SUB:
                    _tp = AST_OP_MINUS;
                    break;
                default:
                    assert(0 && "ASTAddOp got invalid Operand Type.");
            }
        }
    }

    /**
     * 判断是否是二元操作结点
     *
     * 若语法树结构为
     * |-AddExp
     *   |-MulExp
     * 则返回 true
     *
     * 若语法树结构为
     * |-AddExp
     *   |-MulExp1
     *   |-Operand
     *   |-MulExp2
     * 则返回 false
     * @return
     */
    bool isUnaryExp() const {
        return _is_unary;
    }


    /**
     * 获取第一个操作数
     * 语法树正确的情况下，返回的指针任保证是有效的
     */
    ASTInstruction *getOperand1() {
        return l_op;
    }

    /**
     * 获取第二个操作数
     * 仅当 {@see ASTAddOp::isUnaryExp} 为false时有效，否则返回空指针
     */
    ASTInstruction *getOperand2() {
        return r_op;
    }

    /**
     * 获取运算类型
     * 仅当 {@see ASTAddOp::isUnaryExp} 为false时有效，否则返回结果不可预测
     */
    AST_ADD_OP_TYPE getOpType() {
        return _tp;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Add Expression[";
        if (isUnaryExp()) {
            std::cout << "Unary]" << std::endl;
            getOperand1()->print(depth + 1);
        } else {
            std::cout << "Op: ";
            switch (getOpType()) {
                case AST_OP_MINUS:
                    std::cout << '-';
                    break;
                case AST_OP_ADD:
                    std::cout << '+';
                    break;
            }
            std::cout << ']' << std::endl;
            getOperand1()->print(depth + 1);
            getOperand2()->print(depth + 1);
        }
    }

};

class ASTRelOp : public ASTInstruction {
public:
    enum AST_REL_OP_TYPE {
        AST_OP_GT,
        AST_OP_GTE,
        AST_OP_LT,
        AST_OP_LTE
    };
private:
    bool _is_unary;
    ASTInstruction *l_op;
    ASTInstruction *r_op;
    AST_REL_OP_TYPE _tp;

public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTRelOp(TreeNode *t) : ASTInstruction(AST_REL_EXP) {
        assert(t != nullptr && t->node_type == AST_relexp && "ASTMulExpression got invalid TreeNode.");
        _is_unary = t->children.size() == 1;
        r_op = nullptr;
        if (_is_unary) {
            l_op = new ASTAddOp(t->children[0]);
        } else {
            l_op = new ASTRelOp(t->children[0]);
            r_op = new ASTAddOp(t->children[2]);
            switch (t->children[1]->node_type) {
                case AST_GT:
                    _tp = AST_OP_GT;
                    break;
                case AST_GTE:
                    _tp = AST_OP_GTE;
                    break;
                case AST_LT:
                    _tp = AST_OP_LT;
                    break;
                case AST_LTE:
                    _tp = AST_OP_LTE;
                    break;
                default:
                    assert(0 && "ASTRelOp got invalid Operand Type.");
            }
        }
    }

    /**
     * 判断是否是二元操作结点
     */
    bool isUnaryExp() const {
        return _is_unary;
    }


    /**
     * 获取第一个操作数
     * 语法树正确的情况下，返回的指针任保证是有效的
     */
    ASTInstruction *getOperand1() const {
        return l_op;
    }

    /**
     * 获取第二个操作数
     * 仅当 {@see ASTAddOp::isUnaryExp} 为false时有效，否则返回空指针
     */
    ASTInstruction *getOperand2() const {
        return r_op;
    }

    /**
     * 获取运算类型
     * 仅当 {@see ASTRelOp::isUnaryExp} 为false时有效，否则返回结果不可预测
     */
    AST_REL_OP_TYPE getOpType() const {
        return _tp;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Relation Expression[";
        if (isUnaryExp()) {
            std::cout << "Unary]" << std::endl;
            getOperand1()->print(depth + 1);
        } else {
            std::cout << "Op: ";
            switch (getOpType()) {
                case AST_OP_LTE:
                    std::cout << "<=";
                    break;
                case AST_OP_LT:
                    std::cout << '<';
                    break;
                case AST_OP_GTE:
                    std::cout << ">=";
                    break;
                case AST_OP_GT:
                    std::cout << '>';
                    break;
            }
            std::cout << ']' << std::endl;
            getOperand1()->print(depth + 1);
            getOperand2()->print(depth + 1);
        }
    }
};

class ASTEqOp : public ASTInstruction {
public:
    enum AST_EQ_OP_TYPE {
        AST_OP_EQ,
        AST_OP_NEQ,
    };
private:
    bool _is_unary;
    ASTInstruction *l_op;
    ASTInstruction *r_op;
    AST_EQ_OP_TYPE _tp;

public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTEqOp(TreeNode *t) : ASTInstruction(AST_EQ_EXP) {
        assert(t != nullptr && t->node_type == AST_eqexp && "ASTMulExpression got invalid TreeNode.");
        _is_unary = t->children.size() == 1;
        r_op = nullptr;
        if (_is_unary) {
            l_op = new ASTRelOp(t->children[0]);
        } else {
            l_op = new ASTEqOp(t->children[0]);
            r_op = new ASTRelOp(t->children[2]);
            switch (t->children[1]->node_type) {
                case AST_EQ:
                    _tp = AST_OP_EQ;
                    break;
                case AST_NEQ:
                    _tp = AST_OP_NEQ;
                    break;
                default:
                    assert(0 && "ASTEqOp got invalid Operand Type.");
            }
        }
    }

    /**
     * 判断是否是二元操作结点
     */
    bool isUnaryExp() const {
        return _is_unary;
    }


    /**
     * 获取第一个操作数
     * 语法树正确的情况下，返回的指针任保证是有效的
     */
    ASTInstruction *getOperand1() const {
        return l_op;
    }

    /**
     * 获取第二个操作数
     * 仅当 {@see ASTAddOp::isUnaryExp} 为false时有效，否则返回空指针
     */
    ASTInstruction *getOperand2() const {
        return r_op;
    }

    /**
     * 获取运算类型
     * 仅当 {@see ASTRelOp::isUnaryExp} 为false时有效，否则返回结果不可预测
     */
    AST_EQ_OP_TYPE getOpType() const {
        return _tp;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Equality Expression[";
        if (isUnaryExp()) {
            std::cout << "Unary]" << std::endl;
            getOperand1()->print(depth + 1);
        } else {
            std::cout << "Op: ";
            switch (getOpType()) {
                case AST_OP_NEQ:
                    std::cout << "!=";
                    break;
                case AST_OP_EQ:
                    std::cout << "==";
                    break;
            }
            std::cout << ']' << std::endl;
            getOperand1()->print(depth + 1);
            getOperand2()->print(depth + 1);
        }
    }
};

class ASTAndOp : public ASTInstruction {
private:
    bool _is_unary;
    ASTInstruction *l_op;
    ASTInstruction *r_op;

public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTAndOp(TreeNode *t) : ASTInstruction(AST_AND_EXP) {
        assert(t != nullptr && t->node_type == AST_landexp && "ASTAndExpression got invalid TreeNode.");
        _is_unary = t->children.size() == 1;
        r_op = nullptr;
        if (_is_unary) {
            l_op = new ASTEqOp(t->children[0]);
        } else {
            l_op = new ASTAndOp(t->children[0]);
            r_op = new ASTEqOp(t->children[2]);
        }
    }

    /**
     * 判断是否是二元操作结点
     */
    bool isUnaryExp() const {
        return _is_unary;
    }


    /**
     * 获取第一个操作数
     * 语法树正确的情况下，返回的指针任保证是有效的
     */
    ASTInstruction *getOperand1() const {
        return l_op;
    }

    /**
     * 获取第二个操作数
     * 仅当 {@see ASTAddOp::isUnaryExp} 为false时有效，否则返回空指针
     */
    ASTInstruction *getOperand2() const {
        return r_op;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "And Expression[";
        if (isUnaryExp()) {
            std::cout << "Unary]" << std::endl;
            getOperand1()->print(depth + 1);
        } else {
            std::cout << "&&]" << std::endl;
            getOperand1()->print(depth + 1);
            getOperand2()->print(depth + 1);
        }
    }
};

class ASTOrOp : public ASTInstruction {
private:
    bool _is_unary;
    ASTInstruction *l_op;
    ASTInstruction *r_op;

public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTOrOp(TreeNode *t) : ASTInstruction(AST_OR_EXP) {
        assert(t != nullptr && t->node_type == AST_lorexp && "ASTOrExpression got invalid TreeNode.");
        _is_unary = t->children.size() == 1;
        r_op = nullptr;
        if (_is_unary) {
            l_op = new ASTAndOp(t->children[0]);
        } else {
            l_op = new ASTOrOp(t->children[0]);
            r_op = new ASTAndOp(t->children[2]);
        }
    }

    /**
     * 判断是否是二元操作结点
     */
    bool isUnaryExp() const {
        return _is_unary;
    }


    /**
     * 获取第一个操作数
     * 语法树正确的情况下，返回的指针任保证是有效的
     */
    ASTInstruction *getOperand1() const {
        return l_op;
    }

    /**
     * 获取第二个操作数
     * 仅当 {@see ASTAddOp::isUnaryExp} 为false时有效，否则返回空指针
     */
    ASTInstruction *getOperand2() const {
        return r_op;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "And Expression[";
        if (isUnaryExp()) {
            std::cout << "Unary]" << std::endl;
            getOperand1()->print(depth + 1);
        } else {
            std::cout << "&&]" << std::endl;
            getOperand1()->print(depth + 1);
            getOperand2()->print(depth + 1);
        }
    }
};

class ASTLVal : public ASTInstruction {
private:
    std::string _var_name;
    std::vector<ASTAddOp *> _pointer_exp;

    void pointer_walker(TreeNode *p) {
        _pointer_exp.push_back(new ASTAddOp(p->children[1]->children[0]));
        if (p->children.size() == 4) {
            pointer_walker(p->children[3]);
        }
    }

public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTLVal(TreeNode *t) : ASTInstruction(AST_LVAL) {
        assert(t != nullptr && t->node_type == AST_lval && "ASTLval got unknown TreeNode");
        _var_name = t->children[0]->node_name;
        if (t->children.size() == 2) {
            pointer_walker(t->children[1]);
        }
    }

    std::string getVarName() {
        return _var_name;
    }

    bool hasAddress() {
        return !_pointer_exp.empty();
    }

    std::vector<ASTAddOp *> getPointerExpression() {
        return _pointer_exp;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Variable[Name: " << getVarName() << ']' << std::endl;
        if (hasAddress()) {
            ASTInstruction::print(depth);
            std::cout << " Array indexes:" << std::endl;
            for (auto index: getPointerExpression()) {
                index->print(depth + 1);
            }
        }
    }
};

class ASTFuncCall : public ASTInstruction {
private:
    std::string _func_name;
    std::vector<ASTAddOp *> _params;

    void param_walker(TreeNode *node) {
        if (node->children.size() == 3) {
            param_walker(node->children[0]);
            _params.push_back(new ASTAddOp(node->children[2]->children[0]));
        } else {
            _params.push_back(new ASTAddOp(node->children[0]->children[0]));
        }
    }

public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTFuncCall(TreeNode *t) : ASTInstruction(AST_FUNC_CALL) {
        assert(t != nullptr && t->node_type == AST_func_call && "ASTFuncCall got nullptr");
        _func_name = t->children[0]->node_name;
        if (t->children.size() == 4) {
            param_walker(t->children[2]);
        }
    }

    std::string getFunctionName() {
        return _func_name;
    }

    bool hasParams() {
        return !_params.empty();
    }

    std::vector<ASTAddOp *> getParamList() {
        return _params;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Function Call[FunctionName: " << getFunctionName() << ']' << std::endl;
        if (hasParams()) {
            ASTInstruction::print(depth);
            std::cout << " Function params:" << std::endl;
            for (auto param: getParamList()) {
                param->print(depth + 1);
            }
        }
    }
};

class ASTStatement : public ASTInstruction {
public:
    explicit ASTStatement(AST_INST_TYPE t) : ASTInstruction(t) {}

    static ASTStatement *getASTStatement(TreeNode *t);
};

class ASTDecl : public ASTStatement {
public:
    enum ASTDeclType {
        FUNC_DECL,
        VAR_DECL
    };
private:
    ASTDeclType _type;
public:
    ASTDeclType getDeclType() const {
        return _type;
    }

    explicit ASTDecl(ASTDeclType type) : ASTStatement((type == VAR_DECL) ? AST_VARIABLE_DECL : AST_FUNCTION_DECL) {
        this->_type = type;
    }
};

class ASTVarDecl : public ASTDecl {

public:
    virtual void accept(ASTvisitor &) override final;
    enum ASTVarType {
        AST_VAR_INT,
    };

    struct ASTArrayList {
        bool isArray;
        bool isEmpty;
        ASTAddOp *value{};
        std::vector<ASTArrayList *> list;

        explicit ASTArrayList(ASTAddOp *v) {
            value = v;
            isEmpty = isArray = false;
        }

        explicit ASTArrayList(const std::vector<ASTArrayList *> &l) {
            list = l;
            isArray = true;
            isEmpty = false;
        }

        ASTArrayList() {
            isArray = isEmpty = true;
        }
    };

    struct ASTVarDeclInst {
        std::string var_name;
        ASTVarType var_type;
        bool array;
        int dimension;
        std::vector<ASTAddOp *> _array_list;
        bool has_initial;
        std::vector<ASTArrayList *> initial_value;

        ASTVarDeclInst(std::string name, ASTVarType type) {
            var_name = std::move(name);
            var_type = type;
            array = false;
            dimension = 0;
            has_initial = false;
        }

        ASTVarDeclInst(std::string name, ASTVarType type, const std::vector<ASTAddOp *> &array_list) {
            var_name = std::move(name);
            var_type = type;
            array = true;
            _array_list = array_list;
            dimension = array_list.size();
            has_initial = false;
        }

        ASTVarDeclInst(std::string name, ASTVarType type, TreeNode *init) {
            var_name = std::move(name);
            var_type = type;
            array = false;
            dimension = 0;
            has_initial = true;
            initial_walker(init, initial_value);
        }

        ASTVarDeclInst(std::string name, ASTVarType type, const std::vector<ASTAddOp *> &array_list, TreeNode *init) {
            var_name = std::move(name);
            var_type = type;
            array = true;
            _array_list = array_list;
            dimension = array_list.size();
            has_initial = true;
            initial_walker(init, initial_value);
        }
    };

private:

    std::vector<ASTVarDeclInst *> _var_list;
    bool _is_const;
    ASTVarType _var_type;

    void index_walker(TreeNode *node, std::vector<ASTAddOp *> &ind_list) {
        ind_list.push_back(new ASTAddOp(node->children[1]->children[0]));
        if (node->children.size() == 4) {
            index_walker(node->children[3], ind_list);
        }
    }

    static void initial_walker(TreeNode *node, std::vector<ASTArrayList *> &init_list) {
        if (node->node_type == AST_const_init_vals || node->node_type == AST_init_vals) {
            if (node->children.size() == 1) {
                initial_walker(node->children[0], init_list);
            } else {
                initial_walker(node->children[0], init_list);
                initial_walker(node->children[2], init_list);
            }
        } else if (node->node_type == AST_init_val || node->node_type == AST_const_init_val) {
            if (node->children.size() == 1) {
                init_list.push_back(new ASTArrayList(new ASTAddOp(node->children[0]->children[0])));
            } else if (node->children.size() == 2) {
                init_list.push_back(new ASTArrayList());
            } else {
                std::vector<ASTArrayList *> nList;
                initial_walker(node->children[1], nList);
                init_list.push_back(new ASTArrayList(nList));
            }
        }
    }


    void var_decl_list_walker(TreeNode *node) {
        if (node->node_type == AST_var_defs || node->node_type == AST_const_defs) {
            var_decl_list_walker(node->children[0]);
            if (node->children.size() == 3) {
                var_decl_list_walker(node->children[2]);
            }
        } else if (node->node_type == AST_var_def || node->node_type == AST_const_def) {
            if (node->children.size() == 1) {
                // int a;
                _var_list.push_back(new ASTVarDeclInst(node->children[0]->node_name, this->_var_type));
            } else if (node->children.size() == 2) {
                // int a[1][...];
                std::vector<ASTAddOp *> ind;
                index_walker(node->children[1], ind);
                _var_list.push_back(new ASTVarDeclInst(node->children[0]->node_name, this->_var_type, ind));
            } else if (node->children.size() == 3) {
                // int a = 1;
                _var_list.push_back(
                        new ASTVarDeclInst(node->children[0]->node_name, this->_var_type, node->children[2]));
            } else {
                std::vector<ASTAddOp *> ind;
                index_walker(node->children[1], ind);
                _var_list.push_back(
                        new ASTVarDeclInst(node->children[0]->node_name, this->_var_type, ind, node->children[3]));
            }
        }
    }

    void _print_iter(int depth, ASTArrayList *value) {
        if (value->isArray) {
            if (value->isEmpty) {
                ASTInstruction::print(depth);
                std::cout << "{}" << std::endl;
            } else {
                ASTInstruction::print(depth);
                std::cout << '{' << std::endl;
                for (auto val: value->list) {
                    _print_iter(depth + 1, val);
                }
                ASTInstruction::print(depth);
                std::cout << '}' << std::endl;
            }
        } else {
            value->value->print(depth + 1);
        }
    }

public:

    explicit ASTVarDecl(TreeNode *node) : ASTDecl(VAR_DECL) {
        assert(node != nullptr && (node->node_type == AST_var_decl || node->node_type == AST_const_decl) &&
               "ASTVarDecl got invalid TreeNode pointer");
        // 此处正常应该用children[0]进行判断，因语言特性做简略处理
        _var_type = AST_VAR_INT;
        if (node->node_type == AST_var_decl) {
            var_decl_list_walker(node->children[1]);
            _is_const = false;
        } else {
            var_decl_list_walker(node->children[2]);
            _is_const = true;
        }
    }

    std::vector<ASTVarDeclInst *> getVarDeclList() {
        return _var_list;
    }

    bool isConst() const {
        return _is_const;
    }

    void print(int depth) override {
        for (auto var: getVarDeclList()) {
            ASTInstruction::print(depth);
            if (isConst()) {
                std::cout << "const ";
            }
            std::cout << "int " << var->var_name << std::endl;
            if (var->array) {
                ASTInstruction::print(depth + 1);
                std::cout << "Array Dimension:" << std::endl;
                for (auto dim: var->_array_list) {
                    dim->print(depth + 2);
                }
            }
            if (var->has_initial) {
                ASTInstruction::print(depth + 1);
                std::cout << "Variable Initial:" << std::endl;
                _print_iter(depth + 1, var->initial_value[0]);
            }
        }
    }
};

class ASTAssignStmt : public ASTStatement {
private:
    ASTLVal *_l_val;
    ASTAddOp *_r_val;
public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTAssignStmt(TreeNode *t) : ASTStatement(AST_ASSIGN_STMT) {
        assert(t != nullptr && t->node_type == AST_assign_stmt && "ASTAssignStatement got invalid TreeNode.");
        _l_val = new ASTLVal(t->children[0]);
        _r_val = new ASTAddOp(t->children[2]->children[0]);
    }

    ASTLVal *getLeftValue() {
        return _l_val;
    }

    ASTAddOp *getExpression() {
        return _r_val;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Assign Statement" << std::endl;
        ASTInstruction::print(depth);
        std::cout << " Left Value:" << std::endl;
        getLeftValue()->print(depth + 1);
        ASTInstruction::print(depth);
        std::cout << " Right Value:" << std::endl;
        getExpression()->print(depth + 1);
    }
};

class ASTExpressionStmt : public ASTStatement {
private:
    ASTAddOp *_exp;
    bool _valid;
public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTExpressionStmt(TreeNode *t) : ASTStatement(AST_EXPRESSION_STMT) {
        assert(t != nullptr && t->node_type == AST_exp_stmt && "ASTExpressionStatement got invalid TreeNode.");
        if (t->children.size() == 1) {
            _valid = false;
            _exp = nullptr;
        } else {
            _valid = true;
            _exp = new ASTAddOp(t->children[0]->children[0]);
        }
    }

    /**
     * 是否为空表达式
     * 如 ;;
     * 若此方法为false则getExpression返回的是空指针
     * @return
     */
    bool isValidExpression() const {
        return _valid;
    }

    ASTAddOp *getExpression() {
        return _exp;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Expression Statement" << std::endl;
        if (isValidExpression()) {
            getExpression()->print(depth + 1);
        }
    }
};

class ASTIfStmt : public ASTStatement {
private:
    bool _has_else_stmt;
    ASTOrOp *_condition;
    ASTStatement *_true_stmt;
    ASTStatement *_false_stmt;
public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTIfStmt(TreeNode *t) : ASTStatement(AST_IF_STMT) {
        assert(t != nullptr && t->node_type == AST_if_stmt && "ASTIfStatement got invalid TreeNode.");
        _has_else_stmt = t->children.size() == 7;
        _condition = new ASTOrOp(t->children[2]->children[0]);
        _true_stmt = ASTStatement::getASTStatement(t->children[4]);
        if (_has_else_stmt) {
            // if-then-else
            _false_stmt = ASTStatement::getASTStatement(t->children[6]);
        } else {
            _false_stmt = nullptr;
        }
    }

    bool hasElseStatement() const {
        return _has_else_stmt;
    }

    ASTOrOp *getCondition() {
        return _condition;
    }

    ASTStatement *getTrueStatement() {
        return _true_stmt;
    };

    ASTStatement *getFalseStatement() {
        return _false_stmt;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "If-Else Statement" << std::endl;
        ASTInstruction::print(depth);
        std::cout << " If Condition:" << std::endl;
        getCondition()->print(depth + 1);
        ASTInstruction::print(depth);
        std::cout << " If Body:" << std::endl;
        getTrueStatement()->print(depth + 1);
        if (hasElseStatement()) {
            ASTInstruction::print(depth);
            std::cout << " Else Body:" << std::endl;
            getFalseStatement()->print(depth + 1);
        }
    }
};

class ASTWhileStmt : public ASTStatement {
private:
    ASTOrOp *_cond;
    ASTStatement *_while_stmt;

public:
    void accept(ASTvisitor &) final;
    explicit ASTWhileStmt(TreeNode *t) : ASTStatement(AST_WHILE_STMT) {
        assert(t != nullptr && t->node_type == AST_iter_stmt && "ASTWhileStatement got invalid TreeNode.");
        _cond = new ASTOrOp(t->children[2]->children[0]);
        _while_stmt = ASTStatement::getASTStatement(t->children[4]);
    }

    ASTOrOp *getCondition() {
        return _cond;
    }

    ASTStatement *getWhileBodyStatement() {
        return _while_stmt;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "While Statement" << std::endl;
        ASTInstruction::print(depth);
        std::cout << " While Condition:" << std::endl;
        getCondition()->print(depth + 1);
        ASTInstruction::print(depth);
        std::cout << " While Body:" << std::endl;
        getWhileBodyStatement()->print(depth + 1);
    }
};

class ASTBreakStmt : public ASTStatement {
public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTBreakStmt(TreeNode *t) : ASTStatement(AST_BREAK_STMT) {
        assert(t != nullptr && t->node_type == AST_break_stmt && "ASTBreak got invalid TreeNode.");
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Break-Statement" << std::endl;
    }
};

class ASTContinueStmt : public ASTStatement {
public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTContinueStmt(TreeNode *t) : ASTStatement(AST_CONTINUE_STMT) {
        assert(t != nullptr && t->node_type == AST_continue_stmt && "ASTContinue got invalid TreeNode.");
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Continue-Statement" << std::endl;
    }
};

class ASTReturnStmt : public ASTStatement {
private:
    bool _has_ret_value;
    ASTAddOp *_ret_expression;
public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTReturnStmt(TreeNode *t) : ASTStatement(AST_RETURN_STMT) {
        assert(t != nullptr && t->node_type == AST_return_stmt && "ASTContinue got invalid TreeNode.");
        _has_ret_value = t->children.size() == 3;
        if (_has_ret_value) {
            _ret_expression = new ASTAddOp(t->children[1]->children[0]);
        } else {
            _ret_expression = nullptr;
        }
    }

    bool hasReturnValue() const {
        return _has_ret_value;
    }

    ASTAddOp *getRetExpression() {
        return _ret_expression;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Return Statement" << std::endl;
        if (hasReturnValue()) {
            ASTInstruction::print(depth);
            std::cout << " Return Expression" << std::endl;
            getRetExpression()->print(depth + 1);
        }
    }
};

class ASTParam {
public:
    virtual void accept(ASTvisitor &);
    enum ASTFuncParamType {
        AST_PARAM_INT,
    };
private:
    std::string _var_name;
    ASTFuncParamType _type;
    bool _array;
    int _dimension;
    std::vector<ASTAddOp *> _array_list;
public:
    explicit ASTParam(TreeNode *t) {
        assert(t != nullptr && t->node_type == AST_funcf_param && "ASTParam got invalid TreeNode pointer.");
        // 该实现只有int类型
        _type = AST_PARAM_INT;
        _var_name = t->children[1]->node_name;
        if (t->children.size() == 2) {
            // 普通的整型变量
            _array = false;
        } else if (t->children.size() == 3) {
            // int a[] 形式的一维指针变量
            _array = true;
            _dimension = 1;
        } else {
            // int a[][const_exp]... 形式的多维指针变量
            _array = true;
            _dimension = 1;
            TreeNode *pointer = t->children[3];
            while (pointer && pointer->node_type == AST_pointer) {
                _array_list.push_back(new ASTAddOp(pointer->children[1]->children[0]));
                pointer = pointer->children.size() > 3 ? pointer->children[3] : nullptr;
                _dimension += 1;
            }
        }
    }

    std::string getParamName() const {
        return _var_name;
    }

    bool isArray() const {
        return _array;
    }

    std::vector<ASTAddOp *> getArrayList() {
        return _array_list;
    }
};

class ASTBlock : public ASTStatement {
private:
    std::vector<ASTStatement *> _stmt_list;

    void block_item_walker(TreeNode *t) {
        if (t->children.size() == 2) {
            block_item_walker(t->children[0]);
            _stmt_list.push_back(ASTStatement::getASTStatement(t->children[1]->children[0]));
        } else {
            _stmt_list.push_back(ASTStatement::getASTStatement(t->children[0]->children[0]));
        }
    }

public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTBlock(TreeNode *t) : ASTStatement(AST_BLOCK_STMT) {
        assert(t != nullptr && t->node_type == AST_block && "ASTBlock got invalid TreeNode.");
        if (t->children.size() != 2) {
            // 处理 空的Block的情况。如 {}
            block_item_walker(t->children[1]);
        }
    }

    std::vector<ASTStatement *> getStatements() {
        return _stmt_list;
    }

    void print(int depth) override {
        ASTInstruction::print(depth);
        std::cout << "Block{" << std::endl;
        for (auto inst : getStatements()) {
            inst->print(depth + 1);
        }
        ASTInstruction::print(depth);
        std::cout << "} end block" << std::endl;
    }
};

class ASTFuncDecl : public ASTDecl {
public:
    enum FuncRetType {
        AST_RET_INT,
        AST_RET_VOID
    };

private:
    TreeNode *_root;
    FuncRetType _ret_type;
    std::string _func_name;
    std::vector<ASTParam *> _params;
    ASTBlock *_block;

    void walker(TreeNode *node) {
        if (node->node_type == AST_funcf_params) {
            walker(node->children[0]);
            if (node->children.size() == 3) {
                walker(node->children[2]);
            }
        } else {
            this->_params.push_back(new ASTParam(node));
        }
    }

    void parse() {
        /** func_def 孩子结点定义：
         *  children.size == 6 时
         *      [0]: 函数返回类型
         *      [1]: 函数名
         *      [3]: 函数参数列表
         *      [5]: 函数语句(Block)
         *  children.size == 5 时
         *      [0]: 函数返回类型
         *      [1]: 函数名
         *      [4]: 函数语句(Block)
         *  注：Sysy语言仅支持int型变量，故所有变量都是int类型的，直接写死
        **/
        this->_ret_type = (_root->children[0]->node_type == AST_VOID) ? AST_RET_VOID : AST_RET_INT;
        this->_func_name = _root->children[1]->node_name;
        if (_root->children.size() == 5) {
            this->_block = new ASTBlock(_root->children[4]);
        } else if (_root->children.size() == 6) {
            this->_block = new ASTBlock(_root->children[5]);
            walker(_root->children[3]);
        } else {
            assert(0 && "Number of children of node func_def should be 5 or 6.");
        }
    }

public:
    virtual void accept(ASTvisitor &) override final;
    explicit ASTFuncDecl(TreeNode *node) : ASTDecl(FUNC_DECL) {
        _root = node;
        assert(node->node_type == AST_func_def && "Node passed to ASTFuncDecl is not a function decl node.");
        parse();
    }

    std::string getFunctionName() const {
        return _func_name;
    }

    FuncRetType getFunctionType() const {
        return _ret_type;
    }

    ASTBlock *getStmtBlock() {
        return _block;
    }

    bool hasParam() const {
        return !_params.empty();
    }

    std::vector<ASTParam *> getParams() {
        return _params;
    }

    void print(int depth) override {
        std::cout << "Function[Name: " << getFunctionName() << " RetType: ";
        switch (getFunctionType()) {
            case AST_RET_VOID:
                std::cout << "void";
                break;
            case AST_RET_INT:
                std::cout << "int";
                break;
        }
        std::cout << "]" << std::endl;
        if (hasParam()) {
            auto params = getParams();
            for (int i = 0; i < params.size(); ++i) {
                std::cout << "Param " << i << ": " << params[i]->getParamName() << ' ';
                if (params[i]->isArray()) {
                    std::cout << "[Array]" << std::endl;
                } else {
                    std::cout << std::endl;
                }
                for (auto inst: params[i]->getArrayList()) {
                    inst->print(depth + 1);
                }
            }
        }
        std::cout << "Statement Block:" << std::endl;
        getStmtBlock()->print(depth + 1);
    }
};

class ASTProgram {
private:
    SyntaxTree *_tree;
    std::vector<ASTDecl *> declList;

    void parse() {
        TreeNode *t = _tree->root;
        declList.clear();
        t = t->children[0];  // 树根必定只有一个孩子且为comp_unit
        while (t->node_type == AST_comp_unit) {
            // 若comp_unit有2个孩子结点，则第1个必定为comp_unit，第2个为decl
            // 否则唯一的孩子结点为decl类型，而后循环将退出
            // 这样的循环遍历会导致结点顺序与程序中相反，最后执行一次inverse操作
            TreeNode *child;
            if (t->children.size() > 1) {
                child = t->children[1];
            } else {
                child = t->children[0];
            }
            if (child->node_type == AST_decl) {
                declList.push_back(new ASTVarDecl(child->children[0]));
            } else if (child->node_type == AST_func_def) {
                declList.push_back(new ASTFuncDecl(child));
            }
            t = t->children[0];
        }
        std::reverse(declList.begin(), declList.end());
    }

public:
    void runVisitor(ASTvisitor &node);
    virtual void accept(ASTvisitor &);
    /**
     * @brief 生成抽象语法树
     * @param tree Bison输出的低层语法树
     */
    explicit ASTProgram(SyntaxTree *tree) {
        this->_tree = tree;
        if(tree == nullptr || tree->root == nullptr) exit(3);
        assert(tree != nullptr && tree->root != nullptr && tree->root->node_type == AST_program &&
               "Error: Origin AST is null or has a bag structure");
        parse();
    }

    /**
     * @brief 获取程序全局声明语句 \n
     * 包括函数声明与变量声明，且两者可能交替出现，对于不同类型的声明可以采用 @see ASTDecl::getType 进行判断
     * 然后使用 static_cast 转换到对应类型
     * @return 声明列表
     */
    std::vector<ASTDecl *> getDeclareList() {
        return declList;
    }

    void print() {
        for (ASTDecl *decl: getDeclareList()) {
            decl->print(0);
        }
    }
};

class ASTvisitor{
public:
    virtual void visit(ASTProgram &) =0;
    virtual void visit(ASTConstant &) =0;
    virtual void visit(ASTUnaryOp &) =0;
    virtual void visit(ASTMulOp &) =0;
    virtual void visit(ASTAddOp &) =0;
    virtual void visit(ASTRelOp &) =0;
    virtual void visit(ASTEqOp &) =0;
    virtual void visit(ASTAndOp &) =0;
    virtual void visit(ASTOrOp &) =0;
    virtual void visit(ASTLVal &) =0;
    virtual void visit(ASTFuncCall &) =0;
    virtual void visit(ASTVarDecl &) =0;
    virtual void visit(ASTAssignStmt &) =0;
    virtual void visit(ASTExpressionStmt &) =0;
    virtual void visit(ASTIfStmt &) =0;
    virtual void visit(ASTWhileStmt &) =0;
    virtual void visit(ASTBreakStmt &) =0;
    virtual void visit(ASTContinueStmt &) =0;
    virtual void visit(ASTParam &) = 0;
    virtual void visit(ASTFuncDecl &) = 0;
    virtual void visit(ASTReturnStmt &) = 0;
    virtual void visit(ASTBlock &) = 0;
};



#endif //BAZINGA_COMPILER_AST_H
