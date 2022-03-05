#include "pass/CFG.h"

void CFG::run() {
    // Do Nothing
}

void CFG::runOnFunction(Function *f) {
    clearAll();
    this->_func = f;
    if (f->is_declaration()) {
        return;
    }
    _entry = f->get_entry_block();
    // 构建前继、后继链
    for (auto bb: f->get_basic_blocks()) {
        auto term = dynamic_cast<BranchInst *>(bb->get_terminator());
        if (term == nullptr) {
            _term_set.insert(bb);
        } else {
            auto true_bb = term->getTrueBB();
            _precessor_map[true_bb].insert(bb);
            _successor_map[bb].insert(true_bb);
            if (term->is_cond_br()) {
                auto false_bb = term->getFalseBB();
                _precessor_map[false_bb].insert(bb);
                _successor_map[bb].insert(false_bb);
            }
        }
    }
    // 遍历搜索不可达块
    std::queue<BasicBlock *> visit_queue;
    std::set<BasicBlock *> visited_set;
    visit_queue.push(_entry);
    while (!visit_queue.empty()) {
        auto bb = visit_queue.front();
        visit_queue.pop();
        visited_set.insert(bb);
        for (auto next_bb: _successor_map[bb]) {
            if (visited_set.find(next_bb) == visited_set.end()) {
                visit_queue.push(next_bb);
            }
        }
    }
    for (auto bb: f->get_basic_blocks()) {
        if (visited_set.find(bb) == visited_set.end()) {
            _unreachable.insert(bb);
        }
    }
}

std::string CFG::printAsMermaid() {
    _func->print();
    if (_func == nullptr || _func->is_declaration()) { return ""; }
    int i = 1;
    std::map<BasicBlock *, int> _name_map;
    std::string ret = "graph TD;\n";
    for (auto bb: _func->get_basic_blocks()) {
        if (bb->is_fake_block()) continue;
        _name_map.insert({bb, ++i});
        ret += "id" + std::to_string(i) + "[" + bb->get_name() + "]\n";
    }
    for (auto bb: _func->get_basic_blocks()) {
        for (auto target_bb: _successor_map[bb]){
            ret += "id" + std::to_string(_name_map[bb]) + "-->" + "id" + std::to_string(_name_map[target_bb]) +"\n";
        }
    }
    return ret;
}
