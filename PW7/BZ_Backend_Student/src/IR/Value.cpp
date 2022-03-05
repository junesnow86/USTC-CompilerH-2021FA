#include "IR/Value.h"
#include "IR/Type.h"
#include "IR/User.h"
#include "IR/BasicBlock.h"
#include <cassert>

Value::Value(Type *ty, const std::string &name )
  : type_(ty), name_(name)
{

}

void Value::add_use(Value *val, unsigned arg_no )
{
    use_list_.push_back(Use(val, arg_no));
}

std::string Value::get_name() const
{
    return name_;
}

void Value::replace_all_use_with(Value *new_val)
{
    for (auto use : use_list_) {
        auto val = dynamic_cast<User *>(use.val_);
        assert(val && "new_val is not a user");
        val->set_operand(use.arg_no_, new_val);
    }
    auto val = dynamic_cast<BasicBlock *>(this);
    if (val) {
        auto new_bb = dynamic_cast<BasicBlock *>(new_val);
        for (BasicBlock * pre_bb: val->get_pre_basic_blocks()) {
            pre_bb->remove_succ_basic_block(val);
            pre_bb->add_succ_basic_block(new_bb);
            new_bb->add_pre_basic_block(pre_bb);
        }
        for (BasicBlock * suc_bb: val->get_succ_basic_blocks()) {
            suc_bb->remove_pre_basic_block(val);
            suc_bb->add_pre_basic_block(new_bb);
            new_bb->add_succ_basic_block(suc_bb);
        }
    }
}

void Value::remove_use(Value *val)
{
    auto is_val = [val] (const Use &use) { return use.val_ == val; };
    use_list_.remove_if(is_val);
}