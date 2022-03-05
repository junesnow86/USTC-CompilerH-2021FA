#include "../../include/AST/SyntaxTree.h"

class GlobalVal
{
public:
    GlobalVal()
    {
    }
    ~GlobalVal() = default;
    //返回刚更新的值是否为int型
    bool top_is_int()
    {
        return flag_.back() == NEWINT;
    }
    //返回刚更新的int值
    int pop_int()
    {
        int ret = iVal_.back();
        iVal_.pop_back();
        return ret;
    }
    //返回刚更新的float值
    float pop_float()
    {
        float ret = fVal_.back();
        fVal_.pop_back();
        return ret;
    }
    //添加一个int值
    void push(int val)
    {
        flag_.push_back(NEWINT);
        iVal_.push_back(val);
    }
    //添加一个float值
    void push(float val)
    {
        flag_.push_back(NEWFLOAT);
        fVal_.push_back(val);
    }
    //根据运算符更新全局变量值
    void cal(SyntaxTree::BinOp op)
    {
        //t1，t2分别为倒数第二、第一个flag
        FLAG_T t1, t2; 
        t2 = flag_.back();
        flag_.pop_back();
        t1 = flag_.back();
        flag_.pop_back();
        if (t1 == NEWINT && t2 == NEWINT)
        {
            int v1;
            int v2;
            v2 = iVal_.back();
            iVal_.pop_back();
            v1 = iVal_.back();
            iVal_.pop_back();
            iVal_.push_back(intFunc_(v1, v2, op));
            flag_.push_back(NEWINT);
        }
        else if (t1 == NEWINT && t2 == NEWFLOAT)
        {
            int v1;
            float v2;
            v2 = fVal_.back();
            fVal_.pop_back();
            v1 = iVal_.back();
            iVal_.pop_back();
            fVal_.push_back(floatFunc_(v1, v2, op));
            flag_.push_back(NEWFLOAT);
        }
        else if (t1 == NEWFLOAT && t2 == NEWINT)
        {
            float v1;
            int v2;
            v2 = iVal_.back();
            iVal_.pop_back();
            v1 = fVal_.back();
            fVal_.pop_back();
            fVal_.push_back(floatFunc_(v1, v2, op));
            flag_.push_back(NEWFLOAT);
        }
        else
        {
            float v1;
            float v2;
            v2 = fVal_.back();
            fVal_.pop_back();
            v1 = fVal_.back();
            fVal_.pop_back();
            fVal_.push_back(floatFunc_(v1, v2, op));
            flag_.push_back(NEWFLOAT);
        }
    }
    void cal(SyntaxTree::UnaryOp op)
    {
        if (flag_.back() == NEWINT)
            iVal_[iVal_.size() - 1] = intFunc_(iVal_.back(), op);
        else
            fVal_[fVal_.size() - 1] = floatFunc_(fVal_.back(), op);
    }
    void cal(SyntaxTree::UnaryCondOp op)
    {
        if (flag_.back() == NEWINT)
            iVal_[iVal_.size() - 1] = intFunc_(iVal_.back(), op);
        else
        {
            float v = fVal_.back();
            fVal_.pop_back();
            iVal_.push_back(intFunc_(v, op));
            flag_[flag_.size() - 1] = NEWINT;
        }
    }
    void cal(SyntaxTree::BinaryCondOp op)
    {
        //t1，t2分别为倒数第二、第一个flag
        FLAG_T t1, t2;
        t2 = flag_.back();
        flag_.pop_back();
        t1 = flag_.back();
        flag_.pop_back();
        if (t1 == NEWINT && t2 == NEWINT)
        {
            int v1;
            int v2;
            v2 = iVal_.back();
            iVal_.pop_back();
            v1 = iVal_.back();
            iVal_.pop_back();
            iVal_.push_back(intFunc_(v1, v2, op));
            flag_.push_back(NEWINT);
        }
        else if (t1 == NEWINT && t2 == NEWFLOAT)
        {
            int v1;
            float v2;
            v2 = fVal_.back();
            fVal_.pop_back();
            v1 = iVal_.back();
            iVal_.pop_back();
            iVal_.push_back(intFunc_(v1, v2, op));
            flag_.push_back(NEWINT);
        }
        else if (t1 == NEWFLOAT && t2 == NEWINT)
        {
            float v1;
            int v2;
            v2 = iVal_.back();
            iVal_.pop_back();
            v1 = fVal_.back();
            fVal_.pop_back();
            iVal_.push_back(intFunc_(v1, v2, op));
            flag_.push_back(NEWINT);
        }
        else
        {
            float v1;
            float v2;
            v2 = fVal_.back();
            fVal_.pop_back();
            v1 = fVal_.back();
            fVal_.pop_back();
            iVal_.push_back(intFunc_(v1, v2, op));
            flag_.push_back(NEWINT);
        }
    }
    void addConst(std::string name, int val)
    {
        if (cInt_.find(name) == cInt_.end())
        {
            std::vector<int> Var(1, val);
            cInt_.insert(std::make_pair(name, Var));
        }
        else
        {
            //否则向常量结尾插入（即数组）
            cInt_[name].push_back(val);
        }
    }
    void addConst(std::string name, float val)
    {
        if (cFloat_.find(name) == cFloat_.end())
        {
            std::vector<float> Var(1, val);
            cFloat_.insert(std::make_pair(name, Var));
        }
        else
        {
            //否则向常量结尾插入（即数组）
            cFloat_[name].push_back(val);
        }
    }
    void pushConst(std::string name, int offset)
    {
        if (cInt_.find(name) != cInt_.end())
        {
            //说明是int类型
            iVal_.push_back(cInt_[name][offset]);
            flag_.push_back(NEWINT);
        }
        else
        {
            //说明是float类型
            fVal_.push_back(cFloat_[name][offset]);
            flag_.push_back(NEWFLOAT);
        }
    }

private:
    enum FLAG_T
    {
        NEWINT = 0,
        NEWFLOAT,
    };
    std::vector<FLAG_T> flag_;
    //常量值
    std::vector<int> iVal_;
    std::vector<float> fVal_;
    //常量变量表
    std::map<std::string, std::vector<int>> cInt_;
    std::map<std::string, std::vector<float>> cFloat_;
    //私有函数
    int intFunc_(int v1, int v2, SyntaxTree::BinOp op)
    {
        switch (op)
        {
        case SyntaxTree::BinOp::PLUS:
            return v1 + v2;
        case SyntaxTree::BinOp::MINUS:
            return v1 - v2;
        case SyntaxTree::BinOp::MULTIPLY:
            return v1 * v2;
        case SyntaxTree::BinOp::DIVIDE:
            return v1 / v2;
        case SyntaxTree::BinOp::MODULO:
            return v1 % v2;
        default:
            return -1;
        }
    }
    int intFunc_(int v, SyntaxTree::UnaryOp op)
    {
        if (op == SyntaxTree::UnaryOp::PLUS)
            return +v;
        else
            return -v;
    }
    int intFunc_(int v, SyntaxTree::UnaryCondOp op)
    {
        return v == 0;
    }
    int intFunc_(float v, SyntaxTree::UnaryCondOp op)
    {
        return v == 0;
    }
    int intFunc_(int v1, int v2, SyntaxTree::BinaryCondOp op)
    {
        switch (op)
        {
        case SyntaxTree::BinaryCondOp::LT:
            return v1 < v2;
        case SyntaxTree::BinaryCondOp::LTE:
            return v1 <= v2;
        case SyntaxTree::BinaryCondOp::GT:
            return v1 > v2;
        case SyntaxTree::BinaryCondOp::GTE:
            return v1 >= v2;
        case SyntaxTree::BinaryCondOp::EQ:
            return v1 == v2;
        case SyntaxTree::BinaryCondOp::NEQ:
            return v1 != v2;
        case SyntaxTree::BinaryCondOp::LAND:
            return v1 && v2;
        case SyntaxTree::BinaryCondOp::LOR:
            return v1 || v2;
        default:
            return -1;
        }
    }
    int intFunc_(int v1, float v2, SyntaxTree::BinaryCondOp op)
    {
        switch (op)
        {
        case SyntaxTree::BinaryCondOp::LT:
            return v1 < v2;
        case SyntaxTree::BinaryCondOp::LTE:
            return v1 <= v2;
        case SyntaxTree::BinaryCondOp::GT:
            return v1 > v2;
        case SyntaxTree::BinaryCondOp::GTE:
            return v1 >= v2;
        case SyntaxTree::BinaryCondOp::EQ:
            return v1 == v2;
        case SyntaxTree::BinaryCondOp::NEQ:
            return v1 != v2;
        case SyntaxTree::BinaryCondOp::LAND:
            return v1 && v2;
        case SyntaxTree::BinaryCondOp::LOR:
            return v1 || v2;
        default:
            return -1;
        }
    }
    int intFunc_(float v1, int v2, SyntaxTree::BinaryCondOp op)
    {
        switch (op)
        {
        case SyntaxTree::BinaryCondOp::LT:
            return v1 < v2;
        case SyntaxTree::BinaryCondOp::LTE:
            return v1 <= v2;
        case SyntaxTree::BinaryCondOp::GT:
            return v1 > v2;
        case SyntaxTree::BinaryCondOp::GTE:
            return v1 >= v2;
        case SyntaxTree::BinaryCondOp::EQ:
            return v1 == v2;
        case SyntaxTree::BinaryCondOp::NEQ:
            return v1 != v2;
        case SyntaxTree::BinaryCondOp::LAND:
            return v1 && v2;
        case SyntaxTree::BinaryCondOp::LOR:
            return v1 || v2;
        default:
            return -1;
        }
    }
    int intFunc_(float v1, float v2, SyntaxTree::BinaryCondOp op)
    {
        switch (op)
        {
        case SyntaxTree::BinaryCondOp::LT:
            return v1 < v2;
        case SyntaxTree::BinaryCondOp::LTE:
            return v1 <= v2;
        case SyntaxTree::BinaryCondOp::GT:
            return v1 > v2;
        case SyntaxTree::BinaryCondOp::GTE:
            return v1 >= v2;
        case SyntaxTree::BinaryCondOp::EQ:
            return v1 == v2;
        case SyntaxTree::BinaryCondOp::NEQ:
            return v1 != v2;
        case SyntaxTree::BinaryCondOp::LAND:
            return v1 && v2;
        case SyntaxTree::BinaryCondOp::LOR:
            return v1 || v2;
        default:
            return -1;
        }
    }
    float floatFunc_(int v1, float v2, SyntaxTree::BinOp op)
    {
        switch (op)
        {
        case SyntaxTree::BinOp::PLUS:
            return v1 + v2;
        case SyntaxTree::BinOp::MINUS:
            return v1 - v2;
        case SyntaxTree::BinOp::MULTIPLY:
            return v1 * v2;
        case SyntaxTree::BinOp::DIVIDE:
            return v1 / v2;
        default:
            return -1;
        }
    }
    float floatFunc_(float v1, int v2, SyntaxTree::BinOp op)
    {
        switch (op)
        {
        case SyntaxTree::BinOp::PLUS:
            return v1 + v2;
        case SyntaxTree::BinOp::MINUS:
            return v1 - v2;
        case SyntaxTree::BinOp::MULTIPLY:
            return v1 * v2;
        case SyntaxTree::BinOp::DIVIDE:
            return v1 / v2;
        default:
            return -1;
        }
    }
    float floatFunc_(float v1, float v2, SyntaxTree::BinOp op)
    {
        switch (op)
        {
        case SyntaxTree::BinOp::PLUS:
            return v1 + v2;
        case SyntaxTree::BinOp::MINUS:
            return v1 - v2;
        case SyntaxTree::BinOp::MULTIPLY:
            return v1 * v2;
        case SyntaxTree::BinOp::DIVIDE:
            return v1 / v2;
        default:
            return -1;
        }
    }
    float floatFunc_(float v, SyntaxTree::UnaryOp op)
    {
        if (op == SyntaxTree::UnaryOp::PLUS)
            return +v;
        else
            return -v;
    }
};