#ifndef BAZINGA_COMPILER_PASS_MANAGER_H
#define BAZINGA_COMPILER_PASS_MANAGER_H
#include "IR/Module.h"
#include <vector>
#include <memory>



class Pass {
public:
    Pass(Module *m):m_(m){}
    virtual void run() =0;

protected:
    Module *m_;
};

class Pass_manager{
public:
    Pass_manager(Module *m):m_(m){}

    template<typename PassType> void add_pass(bool print_ir=false){
        passes.push_back(std::pair<Pass*,bool>(new PassType(m_),print_ir));
    }
    void run(){
        for(auto pass : passes){
            pass.first->run();
            if(pass.second){
                std::cout<<m_->print();
            }
        }
    }
private:
    std::vector<std::pair<Pass*,bool> > passes;
    Module *m_;
};


#endif //BAZINGA_COMPILER_PASS_MANAGER_H
