#include <CodeGen.h>
#include <RegAlloc.h>
#include <string>

/*
    code for allocating spaces for the varibles in the function (specified by parameter)
        - parameter `fun`: pointer to the function to be handled
    
    you need to implement this function, according to the stack frame layout stated in PW7 documentation
    
    here are some tips:
        - be careful about the order of the argument passed through stack, they are pushed in the reverse order,
          which means the parameter with smaller number will be closer to the stack pointer. 
          for example, the fourth parameter will be closer to stack pointer than the fifth parameter.
        - don't forget the space for callee-saved register, the number of callee-saved register can be 
          get by `used_reg.second.size()`
        - ...
*/

int CodeGen::stack_space_allocation(Function *fun)
{
    int size = 0;

    // std::map<Value *, Interval *> CodeGen::reg_map
    auto _reg_map = &reg_map;   // hint: use this to get register for values

    //std::map<Value *, IR2asm::Regbase *> CodeGen::stack_map
    stack_map.clear();          // you need to fill in this container to finish allocation

    //std::vector<IR2asm::Regbase *> CodeGen::arg_on_stack
    arg_on_stack.clear();       // you need to maintain this information, the order is the same as parameter

    /*TODO：put your code here */
    
    return size;
}