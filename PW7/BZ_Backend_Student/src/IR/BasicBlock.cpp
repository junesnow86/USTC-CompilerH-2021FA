#include "IR/Module.h"
#include "IR/BasicBlock.h"
#include "IR/Function.h"
#include "IR/IRprinter.h"
#include <cassert>

BasicBlock::BasicBlock(Module *m, const std::string &name = "",
                      Function *parent = nullptr, bool fake=false)
    : Value(Type::get_label_type(m), name), _parent(parent), _fake(fake)
{
    _parent->add_basic_block(this);
}

Module *BasicBlock::get_module()
{
    return get_parent()->get_parent();
}

void BasicBlock::add_instruction(Instruction *instr)
{
    instr->setSuccInst(nullptr);
    if (_instrList.empty()) {
        instr->setSuccInst(nullptr);
    } else {
        Instruction *last_inst = _instrList.back();
        instr->setPrevInst(last_inst);
        last_inst->setSuccInst(instr);
    }
    _instrList.push_back(instr);
}

void BasicBlock::add_instr_begin(Instruction *instr)
{
    instr->setPrevInst(nullptr);
    if (_instrList.empty()) {
        instr->setSuccInst(nullptr);
    } else {
        Instruction *first_inst = _instrList.front();
        instr->setSuccInst(first_inst);
        first_inst->setPrevInst(instr);
    }
    _instrList.push_front(instr);
}

void BasicBlock::add_instr_after_phi(Instruction *instr) {
    instr->set_parent(this);
    auto it = _instrList.begin();
    for (; it != _instrList.end(); ++it) {
        if (!(*it)->is_phi()) {
            break;
        }
    }
    Instruction *front = nullptr, *back = nullptr;
    if (it != _instrList.begin())  {
        front = *(--it);
        ++it;
    }
    if (it != _instrList.end()) {
        back = *it;
    }
    if (front != nullptr) {
        front->setSuccInst(instr);
    }
    if (back != nullptr) {
        back->setPrevInst(instr);
    }
    instr->setPrevInst(front);
    instr->setSuccInst(back);
    _instrList.insert(it, instr);
}

void BasicBlock::delete_instr_simple(Instruction *instr) {
    _instrList.remove(instr);
    Instruction *prev = instr->getPrevInst();
    Instruction *succ = instr->getSuccInst();
    if (prev != nullptr) {
        prev->setSuccInst(succ);
    }
    if (succ != nullptr) {
        succ->setPrevInst(prev);
    }
}

void BasicBlock::delete_instr( Instruction *instr )
{
    _instrList.remove(instr);
    Instruction *prev = instr->getPrevInst();
    Instruction *succ = instr->getSuccInst();
    if (prev != nullptr) {
        prev->setSuccInst(succ);
    }
    if (succ != nullptr) {
        succ->setPrevInst(prev);
    }
    instr->remove_use_of_ops();
}

const Instruction *BasicBlock::get_terminator() const
{
    if (_instrList.empty()){
        return nullptr;
    }
    switch (_instrList.back()->get_instr_type())
    {
    case Instruction::ret:
        return _instrList.back();
        break;
    
    case Instruction::br:
        return _instrList.back();
        break;

    default:
        return nullptr;
        break;
    }
}

void BasicBlock::erase_from_parent()
{
    this->get_parent()->remove(this);
}

std::string BasicBlock::print()
{
    if (_fake) {
        return "";
    }
    std::string bb_ir;
    bb_ir += this->get_name();
    bb_ir += ":";
    // print prebb
    if(!this->get_pre_basic_blocks().empty())
    {
        bb_ir += "                                                ; preds = ";
    }
    for (auto bb : this->get_pre_basic_blocks() )
    {
        if( bb != *this->get_pre_basic_blocks().begin() )
            bb_ir += ", ";
        bb_ir += print_as_op(bb, false);
    }
    
    // print prebb
    if ( !this->get_parent() )
    {
        bb_ir += "\n";
        bb_ir += "; Error: Block without parent!";
    }
    bb_ir += "\n";
    for ( auto instr : this->get_instructions() )
    {
        bb_ir += "  ";
        bb_ir += instr->print();
        bb_ir += "\n";
    }

    // 空BasicBlock，自动加上return语句
    if (get_terminator() == nullptr) {
        bb_ir += "  ";
        if(get_parent()->get_return_type()->is_void_type()) {
            bb_ir += "ret void\n";
        } else {
            bb_ir += "ret i32 0\n";
        }
    }

    return bb_ir;
}