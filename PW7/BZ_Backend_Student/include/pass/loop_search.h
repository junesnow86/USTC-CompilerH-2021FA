#ifndef BAZINGA_COMPILER_LOOPSEARCH_H
#define BAZINGA_COMPILER_LOOPSEARCH_H

#include "IR/Module.h"
#include "IR/Function.h"
#include "IR/IRbuilder.h"
#include "IR/BasicBlock.h"
#include "IR/Instruction.h"
#include "pass_manager.h"
#include "stack"

class Loop;
class LoopBlock;

class LoopSearch : public Pass{
private:
    std::map<Function *, std::set<Loop *>> fun_loop;
    std::vector<Loop *> work_list;
    std::map<BasicBlock *, int> DFN;
    std::map<BasicBlock *, int> Low;
    std::stack<BasicBlock *> loop_stack;
    std::set<BasicBlock *> in_stack;
    std::set<BasicBlock *> visited;
    std::set<std::pair<BasicBlock *, BasicBlock *>> edges;
    std::map<Loop *, std::set<Loop *>> child_loop;
    std::map<Function *, std::map<BasicBlock *, Loop *>> _nested_loop;
    int index = 0;
    Function *cur_fun;
    Loop *get_inner_loop(const std::set<Loop *>& l, BasicBlock *bb);
    void build_pre_succ_relation(Loop *loop);
    void build_map();
public:
    void print_loop();
    LoopSearch(Module *m) : Pass(m){}
    ~LoopSearch(){};
    std::set<Loop *> get_child_loop(Loop *loop) { return child_loop[loop]; }
    std::set<Loop *> get_loop(Function *fun) { return fun_loop[fun]; }

    /**
     * 获取指定循环外一层的嵌套循环
     * 若是最外层循环则返回 @code nullptr @endcode
     * @param loop
     * @return
     */
    Loop *get_outer_loop(Loop *loop) {
        Loop *processing = nullptr;
        for (const auto& parent: child_loop) {
            auto &set = parent.second;
            // 当前遍历的循环包含目标内层循环
            if (set.find(loop) != set.end()) {
                // 若预定返回值被当前遍历的循环包含则说明遍历到的循环不是nested的
                // 反之遍历到的循环被预定返回循环包含，预定返回值不是nested，进行更新
                if (set.find(processing) == set.end()) {
                    processing = parent.first;
                }
            }
        }
        return processing;
    }

    /**
     * 获取包含该基本块的最小循环
     * @param f
     * @param bb
     * @return
     */
    Loop *get_smallest_loop(Function *f, BasicBlock *bb) { return _nested_loop[f][bb]; }
    Loop *get_smallest_loop(BasicBlock *bb) { return _nested_loop[bb->get_parent()][bb]; }
    void Tarjan(BasicBlock *bb, std::set<BasicBlock *> blocks);
    void run() override;
};

class Loop{
private:
    BasicBlock *entry_block;
    std::map<BasicBlock *, std::set<BasicBlock *>> loop_pre;
    std::map<BasicBlock *, std::set<BasicBlock *>> loop_succ;
    std::set<BasicBlock *> loop_block;
public:
    std::set<BasicBlock *> get_loop() const { return loop_block; };
    void add_loop_block(BasicBlock *bb) { loop_block.insert(bb); }
    std::set<BasicBlock *> get_loop_bb_pre(BasicBlock *bb) { return loop_pre[bb]; }
    void add_loop_bb_pre(BasicBlock *bb, BasicBlock *pre) { loop_pre[bb].insert(pre); }
    void add_loop_bb_succ(BasicBlock *bb, BasicBlock *succ) { loop_succ[bb].insert(succ); }
    std::set<BasicBlock *> get_loop_bb_succ(BasicBlock *bb) { return loop_succ[bb]; }
    BasicBlock *get_loop_entry() const { return entry_block; }
    void set_entry_block(BasicBlock *entry) { this->entry_block = entry; }
    bool contain_bb(BasicBlock *bb) const { return loop_block.find(bb) != loop_block.end(); }

    /**
     * 获取循环内部向循环入口处跳转的基本块
     * 若循环内部包含多个边指向循环入口则返回nullptr
     * @return
     */
    BasicBlock *getLoopLatch() const {
        BasicBlock *header = get_loop_entry();
        BasicBlock *bb = nullptr;
        for (auto pre: header->get_pre_basic_blocks()) {
            if (contain_bb(pre)) {
                if (bb != nullptr) {
                    return nullptr;
                }
                bb = pre;
            }
        }
        return bb;
    }

    /**
     * 获取所有能退出循环的基本块
     */
    void getExitingBB(std::vector<BasicBlock *> &ret) const {
        for (auto bb: get_loop()) {
            for (auto succ: bb->get_succ_basic_blocks()) {
                if (!contain_bb(succ)) {
                    ret.push_back(bb);
                    break;
                }
            }
        }
    }

    /**
     * 获取退出循环的基本块
     * 若有大于1个基本块满足条件则返回nullptr
     * @return
     */
    BasicBlock *getExitingBB() const {
        std::vector<BasicBlock *> ret;
        getExitingBB(ret);
        if (ret.size() != 1) {
            return nullptr;
        }
        return ret[0];
    }
};


#endif