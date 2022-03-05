#include "pass/loop_search.h"

bool add_new_loop = false;
Loop *curloop = nullptr;
void LoopSearch::run() {
    for(auto fun: m_->get_functions()){
        if(fun->get_basic_blocks().size() == 0) continue;
        cur_fun = fun;
        index = 0;
        std::set<BasicBlock *> bb_set;
        for(auto bb: fun->get_basic_blocks()){
            bb_set.insert(bb);
        }
        curloop = nullptr;
        Tarjan(fun->get_entry_block(), bb_set);
        add_new_loop = false;
        // find inner loop
        while(!work_list.empty()){
            auto loop = work_list.back();
            curloop = loop;
            work_list.pop_back();
            if(loop->get_loop().size() == 1) continue;
            std::set<BasicBlock *> loop_bb;
            for(auto bb: loop->get_loop()){
                loop_bb.insert(bb);
            }
            loop_bb.erase(loop->get_loop_entry());
            index = 0;
            DFN.clear();Low.clear();in_stack.clear();visited.clear();
            for(auto succ: loop->get_loop_entry()->get_succ_basic_blocks()){
                if(loop_bb.find(succ) != loop_bb.end()){
                    Tarjan(succ, loop_bb);
                    break;
                }
            }
        }
        for(auto loop: fun_loop[cur_fun]){
            build_pre_succ_relation(loop);
        }
    }
    build_map();
}

Loop *LoopSearch::get_inner_loop(const std::set<Loop *>& loops, BasicBlock *bb) {
    if (loops.empty()) return nullptr;
    for (auto loop: loops) {
        if (loop->contain_bb(bb)) {
            auto inner_loop = get_inner_loop(get_child_loop(loop), bb);
            if (inner_loop != nullptr) return inner_loop;
            else return loop;
        }
    }
    return nullptr;
}

void LoopSearch::build_map() {
    for (auto f: m_->get_functions()) {
        if (f->is_declaration()) continue;
        std::map<BasicBlock *, Loop *> _sub_map;
        for (auto bb: f->get_basic_blocks()) {
            _sub_map[bb] = get_inner_loop(get_loop(f), bb);
        }
        _nested_loop[f] = _sub_map;
    }
}

void LoopSearch::print_loop(){
    auto white_space = "      ";
    for(auto x: fun_loop){
        int i = 0;
        std::cout<< "in function: " << x.first->get_name() << std::endl;
        for(auto loop: x.second){
            std::cout << "Loop " << i << ":" << std::endl;
            std::cout << "entry block: " << loop->get_loop_entry()->get_name() << std::endl;
            for(auto bb: loop->get_loop()){
                std::cout<< bb->get_name() << std::endl;
                std::cout<< "pre: " << std::endl;
                for(auto pre: loop->get_loop_bb_pre(bb)){
                    std::cout<< white_space << pre->get_name() << std::endl;
                }
                std::cout<< "succ: " << std::endl;
                for(auto succ: loop->get_loop_bb_succ(bb)){
                    std::cout<< white_space << succ->get_name() << std::endl;
                }
            }
            i++;
        }
    }
}

void LoopSearch::Tarjan(BasicBlock *bb, std::set<BasicBlock *> blocks) {
    // find loop in blocks
    DFN[bb] = index;
    Low[bb] = index;
    index ++;
    loop_stack.push(bb);
    in_stack.insert(bb);
    visited.insert(bb);
    for(auto succ_bb: bb->get_succ_basic_blocks()){
        if(blocks.find(succ_bb) == blocks.end()) continue;
        if(visited.find(succ_bb) == visited.end()) {
            // not visited
            Tarjan(succ_bb, blocks);
            Low[bb] = std::min(Low[bb], Low[succ_bb]);
        }
        else if(in_stack.find(succ_bb) != in_stack.end()){
            // still in stack
            Low[bb] = std::min(Low[bb], DFN[succ_bb]);
        }
    }
    if(DFN[bb] == Low[bb]){
        BasicBlock* v = loop_stack.top();
        loop_stack.pop();
        in_stack.erase(v);
        Loop *new_loop = new Loop();
        new_loop->add_loop_block(v);
        while(bb != v){
            v = loop_stack.top();
            loop_stack.pop();
            in_stack.erase(v);
            new_loop->add_loop_block(v);
        }
        new_loop->set_entry_block(bb);
        if(new_loop->get_loop().size() > 1){
            fun_loop[cur_fun].insert(new_loop);
            work_list.push_back(new_loop);
            if(curloop != nullptr){
                child_loop[curloop].insert(new_loop);
            }
        }
        else if(new_loop->get_loop().size() == 1){
            for(auto succ_bb: bb->get_succ_basic_blocks()){
                if(succ_bb == bb){
                    fun_loop[cur_fun].insert(new_loop);
                    work_list.push_back(new_loop);
                    if(curloop != nullptr){
                        child_loop[curloop].insert(new_loop);
                    }
                    break;
                }
            }
        }
    }
}

void LoopSearch::build_pre_succ_relation(Loop *loop) {
    auto bb_set = loop->get_loop();
    for(auto bb: bb_set){
        for(auto succ_bb: bb->get_succ_basic_blocks()){
            if(bb_set.find(succ_bb) != bb_set.end()){
                loop->add_loop_bb_succ(bb, succ_bb);
            }
        }
        for(auto pre_bb: bb->get_pre_basic_blocks()){
            if(bb_set.find(pre_bb) != bb_set.end()){
                loop->add_loop_bb_pre(bb, pre_bb);
            }
        }
    }
}