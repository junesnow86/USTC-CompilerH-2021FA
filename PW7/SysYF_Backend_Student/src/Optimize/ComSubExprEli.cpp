#include "Pass.h"
#include "ComSubExprEli.h"
#include <set>
#include <algorithm>

void ComSubExprEli::execute() {
    module->set_print_name();
     /*you need to finish this function*/
}

bool ComSubExprEli::is_valid_expr(Instruction *inst) {
    return !(inst->is_void()||inst->is_call()||inst->is_phi()||inst->is_alloca()||inst->is_load()||inst->is_cmp()||inst->is_zext());//TODO:CHECK VALID INST
}