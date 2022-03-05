#ifndef BAZINGA_COMPILER_BASICBLOCK_H
#define BAZINGA_COMPILER_BASICBLOCK_H

#include "Value.h"
#include "Instruction.h"
#include "Module.h"
#include "Function.h"

#include <list>
#include <set>
#include <string>
#include <vector>

class Function;
class Instruction;
class Module;

class BasicBlock : public Value
{
private:
    explicit BasicBlock(Module *m, const std::string &name ,
                        Function *parent, bool fake);
    std::list<BasicBlock *> _preBB;
    std::list<BasicBlock *> _succBB;
    std::list<Instruction *> _instrList;
    Function *_parent;
    bool _fake;

public:
    static BasicBlock *create(Module *m, const std::string &name ,
                              Function *parent, bool fake=false) {
        auto prefix = name.empty() ? "" : "label_";
        if (name == "lb1") {
            int a = 1;
        }
        return new BasicBlock(m, prefix + name, parent, fake);
    }

    Function *get_parent() { return _parent; }

    Module *get_module();

    std::list<BasicBlock *> &get_pre_basic_blocks() { return _preBB; }
    std::list<BasicBlock *> &get_succ_basic_blocks() { return _succBB; }
    void add_pre_basic_block(BasicBlock *bb) { _preBB.push_back(bb); }
    void add_succ_basic_block(BasicBlock *bb) { _succBB.push_back(bb); }
    void set_pre_bb(const std::set<BasicBlock *> &bb_list) {
        _preBB.clear();
        _preBB.insert(_preBB.begin(), bb_list.begin(), bb_list.end());
    }
    void set_succ_bb(const std::set<BasicBlock *> &bb_list) {
        _succBB.clear();
        _succBB.insert(_succBB.begin(), bb_list.begin(), bb_list.end());
    }
    void replace_basic_block(BasicBlock *oldBB, BasicBlock *newBB) {
        for(auto it = _preBB.begin(); it != _preBB.end(); ++it) {
            if(*it == oldBB) {
                *it = newBB;
            }
        }
        for(auto it = _succBB.begin(); it != _succBB.end(); ++it) {
            if(*it == oldBB) {
                *it = newBB;
            }
        }
    }

    void remove_pre_basic_block(BasicBlock *bb) { _preBB.remove(bb); }
    void remove_succ_basic_block(BasicBlock *bb) { _succBB.remove(bb); }

    const Instruction *get_terminator() const;
    Instruction *get_terminator() {
        return const_cast<Instruction *>(
                static_cast<const BasicBlock *>(this)->get_terminator());
    }

    void add_instruction(Instruction *instr);
    void add_instr_begin(Instruction *instr);
    void add_instr_after_phi(Instruction *instr);
    void delete_instr_simple(Instruction *instr);

    void delete_instr(Instruction *instr);

    bool empty() { return _instrList.empty(); }
    bool is_fake_block() {return _fake; }
    int get_num_of_instr() { return _instrList.size(); }
    std::list<Instruction *> &get_instructions() { return _instrList; }

    void erase_from_parent();

    virtual std::string print() override;

};

#endif 
