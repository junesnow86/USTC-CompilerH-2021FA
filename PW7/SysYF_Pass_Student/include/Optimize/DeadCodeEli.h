#ifndef SYSYF_DEADCODEELI_H
#define SYSYF_DEADCODEELI_H

#include "Pass.h"
#include "Module.h"

class DeadCodeEli : public Pass
{
public:
    DeadCodeEli(Module *module) : Pass(module) {}
    void execute() final;
    const std::string get_name() const override {return name;}
private:
    Function *func_;
    const std::string name = "DeadCodeElimination";
};

#endif  // SYSYF_DEADCODEELI_H
