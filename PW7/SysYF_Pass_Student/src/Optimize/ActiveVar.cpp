#include "ActiveVar.h"

#include <algorithm>

void ActiveVar::execute() {
    for (auto &func : this->module->get_functions()) {
        if (func->get_basic_blocks().empty()) {
            continue;
        } else {
            func_ = func;  
            
            /*you need to finish this function*/
        }
    }
    return ;
}