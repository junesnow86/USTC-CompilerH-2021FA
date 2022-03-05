#ifndef BAZINGA_COMPILER_CFG_H
#define BAZINGA_COMPILER_CFG_H

#include <vector>
#include <map>
#include <queue>
#include "pass_manager.h"
#include "IR/BasicBlock.h"

/**
 * 分析类Pass，构建CFG
 */
class CFG : public Pass {
public:

    typedef struct Edge {
        BasicBlock *from;
        BasicBlock *to;
    } Edge;


    explicit CFG(Module *m) : Pass(m) {}
    void run() final;
    void runOnFunction(Function *f);

    /**
     * 获取函数入口基本块
     * @return
     */
    BasicBlock * getEntryBB() { return _entry; }

    /**
     * 获取流图中无法到达的基本块
     * @return
     */
    std::set<BasicBlock *> getUnreachableBB() { return _unreachable; }

    /**
     * 获取一个基本块的前继（所有经过一步可以到达该基本块的块）
     * @param bb
     * @return
     */
    std::set<BasicBlock *> getPrevBB(BasicBlock *bb) { return _precessor_map[bb]; }

    /**
     * 获取一个基本块的后继（所有由该块经过一步即可到达的块）
     * @param bb
     * @return
     */
    std::set<BasicBlock *> getSuccBB(BasicBlock *bb) { return _successor_map[bb]; }

    /**
     * 获取所有终止函数运行的基本块
     * @return
     */
    std::set<BasicBlock *> getTerminators() { return _term_set; }

    /**
     * 获取函数RPO遍历的所有反向边
     * @param f
     * @return
     */
    std::set<Edge *> getRPOBackwardEdges(Function *f);


    /**
     * 获取函数RPO遍历的顺序
     * @param f
     * @return
     */
    std::vector<BasicBlock *> getRPOTraverseQueue(Function *f);


    /**
     * 以markdown mermaid绘图方式输出
     * @return
     */
    std::string printAsMermaid();

private:
    void clearAll() {
        _func = nullptr;
        _entry = nullptr;
        _successor_map.clear();
        _precessor_map.clear();
        _term_set.clear();
    }

    Function *_func{};
    BasicBlock *_entry{};
    std::map<BasicBlock *, std::set<BasicBlock *>> _successor_map;
    std::map<BasicBlock *, std::set<BasicBlock *>> _precessor_map;
    std::set<BasicBlock *> _term_set;
    std::set<BasicBlock *> _unreachable;

};


#endif //BAZINGA_COMPILER_CFG_H
