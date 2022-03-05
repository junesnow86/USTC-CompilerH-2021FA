#include "pass/get_ptr_simply.h"

void GEP_Simply::run() {
    for(auto fun: m_->get_functions()){
        if(fun->is_declaration()) continue;
        auto entry_bb = fun->get_entry_block();
        bool changed = true;
        while(changed){
            changed = false;
            for(auto instr: entry_bb->get_instructions()){
                if(!instr->is_gep()) continue;
                Instruction *ins_ptr = instr;
                Value *cur_value = nullptr;
                std::vector<Instruction *> wait_delete;
                bool store_used = false;
                Instruction *pre_store = nullptr;
                while(ins_ptr->getSuccInst() != nullptr){
                    ins_ptr = ins_ptr->getSuccInst();
                    if(ins_ptr->is_store() && ins_ptr->get_operand(1) == instr){
                        if(pre_store && !store_used){
                            wait_delete.push_back(pre_store);
                        }
                        pre_store = ins_ptr;
                        store_used = false;
                        cur_value = ins_ptr->get_operand(0);
                    }
                    else if(ins_ptr->is_load() && ins_ptr->get_operand(0) == instr){
                        if(cur_value){
                            store_used = true;
                            ins_ptr->replace_all_use_with(cur_value);
                            wait_delete.push_back(ins_ptr);
                            changed = true;
                        }
                    }
                }
                for(auto ins: wait_delete){
                    entry_bb->delete_instr(ins);
                }
            }
        }
    }
}

void GEP_Simply::remove_repeat_gep(BasicBlock *bb) {

}