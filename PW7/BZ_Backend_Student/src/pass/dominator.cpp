#include "pass/dominator.h"
#include "queue"
#include "iostream"

void print_block(Function* f){
    for(auto bb: f->get_basic_blocks()){
        if(!bb->is_fake_block()){
            std::cout << bb->get_name() << "has " << bb->get_pre_basic_blocks().size() << " pre block " << std::endl;
            for(auto succ: bb->get_pre_basic_blocks()){
                std::cout<< succ->get_name() << std::endl;
            }
        }
    }
}

void dominator::run(){
    for (auto f : m_->get_functions()) {
        if (f->get_basic_blocks().size() == 0)
            continue;
        for (auto bb : f->get_basic_blocks() ){
            if(bb->is_fake_block()) continue;
            _iDomMap.insert({bb , {}});
            _frontierMap.insert({bb , {}});
            _successorMap.insert({bb , {}});
        }
        createRPO(f);
        create_immediate_dominance(f);
        create_dominance_frontier(f);
        create_dom_tree_succ(f);
    }
}

void dominator::createRPO(Function *f){
    _reversedPostOrderQueue.clear();
    _postOrderID.clear();
    std::set<BasicBlock *> visited;
    int id = 0;
    dfs(f->get_entry_block(), visited, id);
    _reversedPostOrderQueue.reverse();
}

void dominator::dfs(BasicBlock *bb, std::set<BasicBlock *> &visited, int &id){
    visited.insert(bb);
    for (auto _bb : bb->get_succ_basic_blocks()) {
        // 跳过假块
        if(_bb->is_fake_block()) continue;
        // 若没有访问过则对其访问，否则跳过
        if (visited.find(_bb) == visited.end()) {
            dfs(_bb, visited, id);
        }
    }
    _postOrderID[bb] = id++;
    _reversedPostOrderQueue.push_back(bb);
}

void dominator::create_immediate_dominance(Function *f){
    for (auto bb : f->get_basic_blocks()){
        if(bb->is_fake_block()){
            continue;
        }
        set_immediate_dominance(bb, nullptr);
    }
    auto root = f->get_entry_block();
    set_immediate_dominance(root, root);

    bool changed = true;
    while (changed) {
        changed = false;
        for (auto bb : this->_reversedPostOrderQueue) {
            if(bb->is_fake_block()) continue;
            if (bb == root) {
                continue;
            }
            // find one pred which has idom
            BasicBlock *pred = nullptr;
            for (auto p : bb->get_pre_basic_blocks()) {
                if(p->is_fake_block()) continue;
                if (getImmediateDominance(p)) {
                    pred = p;
                    break;
                }
            }
            assert(pred);

            BasicBlock *new_idom = pred;
            for (auto p : bb->get_pre_basic_blocks()) {
                if(p->is_fake_block()) continue;
                if (p == pred)
                    continue;
                if (getImmediateDominance(p)) {
                    new_idom = intersect(p, new_idom);
                }
            }
            if (getImmediateDominance(bb) != new_idom) {
                set_immediate_dominance(bb, new_idom);
                changed = true;
            }
        }
    }
}

// find closest parent of b1 and b2
BasicBlock *dominator::intersect(BasicBlock *b1, BasicBlock *b2){
    assert(_postOrderID.find(b1) != _postOrderID.end() && _postOrderID.find(b2) != _postOrderID.end() && "Unidentified Basic Block");
    while (b1 != b2) {
        while (_postOrderID[b1] < _postOrderID[b2]) {
            assert(getImmediateDominance(b1));
            b1 = getImmediateDominance(b1);
        }
        while (_postOrderID[b2] < _postOrderID[b1]) {
            assert(getImmediateDominance(b2));
            b2 = getImmediateDominance(b2);
        }
    }
    return b1;
}

void dominator::create_dominance_frontier(Function *f){
    for (auto bb : f->get_basic_blocks()) {
        if(bb->is_fake_block()) continue;
        if (bb->get_pre_basic_blocks().size() >= 2) {
            for (auto p : bb->get_pre_basic_blocks()) {
                auto runner = p;
                while (runner != getImmediateDominance(bb)) {
                    add_dominance_frontier(runner, bb);
                    runner = getImmediateDominance(runner);
                }
            }
        }
    }
}

void dominator::create_dom_tree_succ(Function *f){
    for (auto bb : f->get_basic_blocks()) {
        if(bb->is_fake_block()) continue;
        auto idom = getImmediateDominance(bb);
        if(!idom || idom->is_fake_block()) continue;
        // e.g, entry bb
        if (idom != bb) {
            add_dom_tree_succ_block(idom, bb);
        }
    }
}

void dominator::print_dom_tree() {
    std::cout <<"======="<<std::endl;
    std::cout << _successorMap.size() << std::endl;
    for(auto x: _successorMap){
        if(x.first->is_fake_block()) continue;
        std::cout << x.first->get_name() << std::endl;
        for(auto s: x.second){
            std::cout << x.first->get_name() << " -->  " << s->get_name() << std::endl;
        }
    }
    std::cout <<"======="<<std::endl;
}