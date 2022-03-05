#include "LIR/LIRBuilder.h"
#include "LIR/LIRInstruction.h"
#include "LIR/LIRLabel.h"
#include "IR/Module.h"
#include "pass/loop_search.h"
#include "pass/dominator.h"
#include "pass/CFG.h"

#include <algorithm>

bool inverseOperandIfNeeded(Value *&lhs, Value *&rhs) {
    assert(!(dynamic_cast<ConstantInt *>(lhs) && dynamic_cast<ConstantInt *>(rhs)) && "ARM doesn't support cmp between Imme. Please run ConstantFolding first.");
    // 第一个操作数不能是立即数
    if (dynamic_cast<ConstantInt *>(lhs)) {
        std::swap(lhs, rhs);
        return true;
    } else {
        return false;
    }
}

void getDimensionByType(std::vector<int> &dim, Type *ty) {
    if (!ty->is_array_type()) return;
    auto arr_ty = dynamic_cast<ArrayType *>(ty);
    dim.push_back(arr_ty->get_num_of_elements());
    getDimensionByType(dim, arr_ty->get_array_element_type());
}

void LIRBuilder::addInstruction(LIRInstruction *inst) {
    _currentBB->addInst(inst);
}

void LIRBuilder::addBasicBlock(LIRBasicBlock *bb) {
    _currentFunc->addBasicBlock(bb);
}

LIRBasicBlock *LIRBuilder::getExitBlock() {
    return _currentFunc->getExitBlock();
}

LIROperand *LIRBuilder::getRegOrConstant(Value *v) {
    if (auto c = dynamic_cast<ConstantInt *>(v)) {
        return LIRConstantOperand::create(c->get_value());
    }
    if (auto a = dynamic_cast<Argument *>(v)) {
        return getArg(a);
    }
    if (existInRegMap(dynamic_cast<Instruction *>(v))) {
        return getReg(dynamic_cast<Instruction *>(v));
    }
    else {
        std::cout << "Warning: got null ptr" << std::endl;
        return nullptr;
    }
}

void LIRBuilder::build() {
    auto *lp = new LoopSearch(_m);
    auto *dom = new dominator(_m);
    auto *cfg = new CFG(_m);
    lp->run();
    dom->run();
    // Step 0. 处理全局变量
    for (auto gv: _m->get_global_variable()) {
        setGlobalVariable(gv, LIRGlobalVariable::create(gv->get_name(), gv->get_type(), gv->get_init(), gv->getFlattenInit()));
    }
    // Step 1. 创建所有函数、基本块的映射、为所有带有返回值的指令分配虚拟寄存器
    for (auto f: _m->get_functions()) {
        auto lf = LIRFunction::create(f->get_name(), (int)f->get_num_of_args(), !f->get_return_type()->is_void_type());
        setFunctionMap(f, lf);
        if (f->is_declaration()) continue;
        addFunction(lf);
        setCurrentFunction(lf);
        auto order = computeBasicBlockOrder(f, cfg, lp, dom);
        _blockOrder[f] = order;
        // 创建入口块
        auto initBB = LIRBasicBlock::create("init");
        addBasicBlock(initBB);
        setCurrentBasicBlock(initBB);
        lf->setInitBlock(initBB);
        int num_arg = 0;
        for (auto arg: f->get_args()) {
            //TODO
            //这里前四个参数采用寄存器传递
            //后四个参数通过load传值，因为还没有处理栈帧指针，load指令默认从13号寄存器处load，偏移量为0
        }
        for (auto bb: order) {
            auto lbb = LIRBasicBlock::create(bb->get_name());
            setBlockMap(bb, lbb);
            addBasicBlock(lbb);
            for (auto i: bb->get_instructions()) {
                if (!i->is_void()) {
                    //TODO
                    //分配虚拟寄存器或从栈中进行alloc
                }
            }
        }
        // 创建Exit块
        auto exitBB = LIRBasicBlock::create("exit");
        addBasicBlock(exitBB);
        lf->setExitBlock(exitBB);
        // Init块跳向Entry块
        auto it = _currentFunc->getBasicBlocks().begin();
        it++;
        _currentFunc->getBasicBlocks().front()->addInst(LIRBranchInstruction::create(*it));
    }
    // Step 2. 构建指令
    for (auto f: _m->get_functions()) {
        if (f->is_declaration()) continue;
        setCurrentFunction(getLFunction(f));
        for (auto bb:_blockOrder.at(f)) {
            setCurrentBasicBlock(getLBB(bb));
            for (auto i: bb->get_instructions()) {
                buildInstr(i);
            }
        }
    }
    // Step 3. 消解Phi语句
    for (auto f: _m->get_functions()) {
        if (f->is_declaration()) continue;
        for (auto bb: f->get_basic_blocks()) {
            setCurrentBasicBlock(getLBB(bb));
            for (auto i: bb->get_instructions()) {
                if (auto phi = dynamic_cast<PhiInst *>(i)) {
                    //TODO
                    //要特别处理undef路径上的值
                }
            }
        }
    }
    // Step 4. 循环深度计算、循环标号、前向边计算
    int loopId = 0;
    std::map<BasicBlock *, int> loopDepth;//统计bb所处的循环深度。对于不处在循环中的bb，循环深度为0
    std::map<BasicBlock *, int> incomingForwardBranches;//统计bb发出的前向边数量
    std::map<Loop *, int> loopID;//为每个循环编号
    for (auto f: _m->get_functions()) {
        if (f->is_declaration()) continue;
        dom->createRPO(f);
        cfg->runOnFunction(f);
        //TODO
        //请善用cfg、lp和dom中的各个函数
        //统计信息将最终为LIRBasicBlock类设置循环深度，前向边数量，以及所处最小循环编号
        //同时也需要为LIRBasicBlock类设置前驱与后继基本快

        // 单独处理开头、结尾块的信息
        auto lf = getLFunction(f);
        auto initBB = lf->getBasicBlocks().front();
        auto exitBB = lf->getBasicBlocks().back();
        initBB->setLoopIndex(-1);
        initBB->setLoopDepth(0);
        initBB->setIncomingForwardBranches(0);
        exitBB->setLoopIndex(-1);
        exitBB->setLoopDepth(0);
        exitBB->setIncomingForwardBranches(exitBB->getPredecessorBB().size());
    }
    delete lp;
    delete dom;
    delete cfg;
}

void LIRBuilder::buildInstr(Instruction *inst) {
    switch (inst->get_instr_type()) {
        case Instruction::ret: {
            auto ret = dynamic_cast<ReturnInst *>(inst);
            // Check if it is a void function
            if (ret->is_void_ret()) {
                addInstruction(LIRBranchInstruction::create(getExitBlock()));
            } else {
                addInstruction(LIRMovInst::create(LIRPhysicsRegister::create(0), getRegOrConstant(ret->get_operand(0))));
                addInstruction(LIRBranchInstruction::create(getExitBlock()));
            }
            break;
        }
        case Instruction::br: {
            // Move the condition inst to here.
            auto br = dynamic_cast<BranchInst *>(inst);
            if (br->is_cond_br()) {
                auto cond = br->get_condition();
                if (auto ci = dynamic_cast<ConstantInt *>(cond)) {
                    if (ci->get_value()) {
                        addInstruction(LIRBranchInstruction::create(getLBB(br->getTrueBB())));
                    } else {
                        addInstruction(LIRBranchInstruction::create(getLBB(br->getFalseBB())));
                    }
                } else {
                    auto cmp = dynamic_cast<CmpInst *>(cond);
                    auto lhs = cmp->get_operand(0);
                    auto rhs = cmp->get_operand(1);
                    bool inverse = inverseOperandIfNeeded(lhs, rhs);
                    addInstruction(LIRCmpInst::create(getRegOrConstant(lhs), getRegOrConstant(rhs)));
                    switch (cmp->get_cmp_op()) {
                        case CmpInst::EQ:
                            addInstruction(LIRBranchInstruction::create(getLBB(br->getTrueBB()), LIRCond::LCondEQ));
                            break;
                        case CmpInst::NE:
                            addInstruction(LIRBranchInstruction::create(getLBB(br->getTrueBB()), LIRCond::LCondNE));
                            break;
                        case CmpInst::GT:
                            addInstruction(LIRBranchInstruction::create(getLBB(br->getTrueBB()), inverse ? LIRCond::LCondLE : LIRCond::LCondGT));
                            break;
                        case CmpInst::GE:
                            addInstruction(LIRBranchInstruction::create(getLBB(br->getTrueBB()), inverse ? LIRCond::LCondLT : LIRCond::LCondGE));
                            break;
                        case CmpInst::LT:
                            addInstruction(LIRBranchInstruction::create(getLBB(br->getTrueBB()), inverse ? LIRCond::LCondGE : LIRCond::LCondLT));
                            break;
                        case CmpInst::LE:
                            addInstruction(LIRBranchInstruction::create(getLBB(br->getTrueBB()), inverse ? LIRCond::LCondGT : LIRCond::LCondLE));
                            break;
                    }
                    addInstruction(LIRBranchInstruction::create(getLBB(br->getFalseBB())));
                }
            } else {
                addInstruction(LIRBranchInstruction::create(getLBB(br->getTrueBB())));
            }
            break;
        }
        case Instruction::add:
        {
            auto lhs = inst->get_operand(0);
            auto rhs = inst->get_operand(1);
            inverseOperandIfNeeded(lhs, rhs);
            addInstruction(LIRBinaryInst::createAdd(getRegOrConstant(inst), getRegOrConstant(lhs), getRegOrConstant(rhs)));
            break;
        }
        case Instruction::mul:
        {
            auto lhs = getRegOrConstant(inst->get_operand(0));
            auto rhs = getRegOrConstant(inst->get_operand(1));
            if (dynamic_cast<LIRConstantOperand *>(lhs)) {
                auto tmp = LIRVirtualRegister::create();
                addInstruction(LIRMovInst::create(tmp, lhs));
                lhs = tmp;
            }
            if (dynamic_cast<LIRConstantOperand *>(rhs)) {
                auto tmp = LIRVirtualRegister::create();
                addInstruction(LIRMovInst::create(tmp, rhs));
                rhs = tmp;
            }
            addInstruction(LIRBinaryInst::createMul(getReg(inst), lhs, rhs));
            break;
        }
        case Instruction::sub:
        {
            auto lhs = inst->get_operand(0);
            auto rhs = inst->get_operand(1);
            if (auto c = dynamic_cast<ConstantInt *>(lhs)) {
                // 1 - a => mov r1, a; sub r2, r1, a
                auto tmp = LIRVirtualRegister::create();
                addInstruction(LIRMovInst::create(tmp, LIRConstantOperand::create(c->get_value())));
                addInstruction(LIRBinaryInst::createSub(getReg(inst), tmp, getRegOrConstant(rhs)));
            } else {
                addInstruction(LIRBinaryInst::createSub(getReg(inst), getRegOrConstant(lhs), getRegOrConstant(rhs)));
            }
            break;
        }
        case Instruction::sdiv:
        {
            auto lhs = getRegOrConstant(inst->get_operand(0));
            auto rhs = getRegOrConstant(inst->get_operand(1));
            if (dynamic_cast<LIRConstantOperand *>(lhs)) {
                auto tmp = LIRVirtualRegister::create();
                addInstruction(LIRMovInst::create(tmp, lhs));
                lhs = tmp;
            }
            if (dynamic_cast<LIRConstantOperand *>(rhs)) {
                const int N=32;
                int d=dynamic_cast<LIRConstantOperand *>(rhs)->getValue();
                //calculate m,sh_post,l
                int l=std::ceil(std::log2((double)d+0.5));
                int sh_post = l;
                const int N_=31;
                uint64_t m_l=(((uint64_t) 1) << (N_+l)) /d;
                uint64_t m_h=((((uint64_t) 1) << (N_+l)) + (((uint64_t) 1)<< (l)))/d;
                while ((m_l/2 < m_h /2) && (sh_post > 1)){
                    m_l /= 2;
                    m_h /= 2;
                    sh_post -- ;
                }
                sh_post--;
                //end calculate
                int m=(int) m_h;
                while (1<<l < d) l++;
                if (d == 1){
                    addInstruction(LIRMovInst::create(getReg(inst), lhs));
                    break;
                }
                else if (abs(d) == 1<<l){
                    addInstruction(LIRBinaryInst::createAsr(LIRPhysicsRegister::create(12), lhs, LIRConstantOperand::create(l-1)));
                    addInstruction(LIRBinaryInst::createLsr(LIRPhysicsRegister::create(12), LIRPhysicsRegister::create(12), LIRConstantOperand::create(N-l)));
                    addInstruction(LIRBinaryInst::createAdd(LIRPhysicsRegister::create(12), LIRPhysicsRegister::create(12), lhs));
                    addInstruction(LIRBinaryInst::createAsr(getReg(inst), LIRPhysicsRegister::create(12), LIRConstantOperand::create(l)));
                    break;
                }
                else if (m >= 0){
                    addInstruction(LIRMovInst::create(LIRPhysicsRegister::create(12), LIRConstantOperand::create(m)));
                    addInstruction(LIRBinaryInst::createSMMul(LIRPhysicsRegister::create(12),LIRPhysicsRegister::create(12), lhs));
                    addInstruction(LIRBinaryInst::createAsr(LIRPhysicsRegister::create(12),LIRPhysicsRegister::create(12),LIRConstantOperand::create(sh_post)));
                    addInstruction(LIRMovInst::create(getReg(inst),LIRPhysicsRegister::create(12)));
                    addInstruction(LIRBinaryInst::createLsr(LIRPhysicsRegister::create(12),lhs,LIRConstantOperand::create(31)));
                    addInstruction(LIRBinaryInst::createAdd(getReg(inst),getReg(inst),LIRPhysicsRegister::create(12)));
                }
                else{
                    addInstruction(LIRMovInst::create(LIRPhysicsRegister::create(12), LIRConstantOperand::create(m)));
                    addInstruction(LIRBinaryInst::createSMMul(LIRPhysicsRegister::create(12),LIRPhysicsRegister::create(12), lhs));
                    addInstruction(LIRBinaryInst::createAdd(LIRPhysicsRegister::create(12),LIRPhysicsRegister::create(12), lhs));
                    addInstruction(LIRBinaryInst::createAsr(LIRPhysicsRegister::create(12),LIRPhysicsRegister::create(12),LIRConstantOperand::create(sh_post)));
                    addInstruction(LIRMovInst::create(getReg(inst),LIRPhysicsRegister::create(12)));
                    addInstruction(LIRBinaryInst::createLsr(LIRPhysicsRegister::create(12),LIRPhysicsRegister::create(12),LIRConstantOperand::create(32)));
                    addInstruction(LIRBinaryInst::createAdd(getReg(inst),getReg(inst),LIRPhysicsRegister::create(12)));
                }
                break;
            }
            addInstruction(LIRBinaryInst::createDiv(getReg(inst), lhs, rhs));
            break;
        }
        case Instruction::mod: {
            auto a = getRegOrConstant(inst->get_operand(0));
            auto b = getRegOrConstant(inst->get_operand(1));
            if (auto c_a = dynamic_cast<LIRConstantOperand *>(a)) {
                auto tmp = LIRVirtualRegister::create();
                addInstruction(LIRMovInst::create(tmp, c_a));
                a = tmp;
            }
            if (auto c_b = dynamic_cast<LIRConstantOperand *>(b)) {
                auto tmp = LIRVirtualRegister::create();
                addInstruction(LIRMovInst::create(tmp, c_b));
                b = tmp;
            }
            auto adb = LIRVirtualRegister::create(), apb = LIRVirtualRegister::create();
            addInstruction(LIRBinaryInst::createDiv(adb, a, b));
            addInstruction(LIRBinaryInst::createMul(apb, adb, b));
            addInstruction(LIRBinaryInst::createSub(getReg(inst), a, apb));
            break;
        }
        /**
         * Alloca 语句不生成可执行的代码而仅在栈上分配一段空间，将空间的基址存入mapping中
         */
        case Instruction::alloca: {
            // Do nothing. This inst has been proceed in previous step.
            break;
        }
        case Instruction::load: {
            auto ld = dynamic_cast<LoadInst *>(inst);
            auto from = ld->get_operand(0);
            if (auto gv = dynamic_cast<GlobalVariable *>(from)) {
                // Global int
                auto ld_label = LIRVirtualRegister::create();
                addInstruction(LIRLoadInst::create(ld_label, getGlobalVar(gv)));
                addInstruction(LIRLoadInst::create(getReg(inst), ld_label));
            }
            else {
                // GEP
                auto gep = dynamic_cast<GetElementPtrInst *>(from);
                auto offset = getRegOrConstant(gep);
                Value *top = gep;
                while (auto gep_ori = dynamic_cast<GetElementPtrInst *>(top)) {
                    top = gep_ori->get_operand(0);
                }
                // 偏移量 x 4
                if (auto off_c = dynamic_cast<LIRConstantOperand *>(offset)) {
                    offset = LIRConstantOperand::create(off_c->getValue() * 4);
                } else {
                    auto tmp = LIRVirtualRegister::create();
                    addInstruction(LIRBinaryInst::createLsl(tmp, offset, LIRConstantOperand::create(2)));
                    offset = tmp;
                }
                // 获取到原本的模式，进行判断
                // 若是全局数组则
                if (auto glb_v = dynamic_cast<GlobalVariable *>(top)) {
                    auto ld_label = LIRVirtualRegister::create();
                    // load r1, =LabelName
                    addInstruction(LIRLoadInst::create(ld_label, getGlobalVar(glb_v)));
                    // load r2, [r1, rm/Imm]
                    addInstruction(LIRLoadInst::create(getReg(inst), ld_label, offset));
                }
                    // 参数变量
                else if (auto a = dynamic_cast<Argument *>(top)) {
                    // 直接Load即可
                    addInstruction(LIRLoadInst::create(getReg(inst), getRegOrConstant(a), offset));
                }
                    // Alloca出来的数组
                else if (auto al = dynamic_cast<AllocaInst *>(top)) {
                    // 计算相对于SP的偏移量
                    auto alloca = getAlloca(al);
                    if (auto c = dynamic_cast<LIRConstantOperand *>(offset)) {
                        offset = LIRConstantOperand::create(c->getValue() + alloca->getBase());
                    } else {
                        if (alloca->getBase() != 0) {
                            auto tmp = LIRVirtualRegister::create();
                            addInstruction(LIRBinaryInst::createAdd(tmp, offset, LIRConstantOperand::create(alloca->getBase())));
                            offset = tmp;
                        }
                    }
                    addInstruction(LIRLoadInst::create(getReg(inst), LIRPhysicsRegister::create(13), offset));
                }
            }
            break;
        }
        case Instruction::store:{
            auto st = dynamic_cast<StoreInst *>(inst);
            auto from = st->get_operand(1);
            auto data = getRegOrConstant(st->get_operand(0));
            if (auto co = dynamic_cast<LIRConstantOperand *>(data)) {
                data = LIRVirtualRegister::create();
                addInstruction(LIRMovInst::create(data, co));
            }
            if (auto gv = dynamic_cast<GlobalVariable *>(from)) {
                // Global int
                auto ld_label = LIRVirtualRegister::create();
                addInstruction(LIRLoadInst::create(ld_label, getGlobalVar(gv)));
                addInstruction(LIRStoreInst::create(data, ld_label));
            }
            else {
                // GEP
                auto gep = dynamic_cast<GetElementPtrInst *>(from);
                auto offset = getRegOrConstant(gep);
                Value *top = gep;
                while (auto gep_ori = dynamic_cast<GetElementPtrInst *>(top)) {
                    top = gep_ori->get_operand(0);
                }
                // 偏移量 x 4
                if (auto off_c = dynamic_cast<LIRConstantOperand *>(offset)) {
                    offset = LIRConstantOperand::create(off_c->getValue() * 4);
                } else {
                    auto tmp = LIRVirtualRegister::create();
                    addInstruction(LIRBinaryInst::createLsl(tmp, offset, LIRConstantOperand::create(2)));
                    offset = tmp;
                }
                // 获取到原本的模式，进行判断
                // 若是全局数组则
                if (auto glb_v = dynamic_cast<GlobalVariable *>(top)) {
                    // load r1, =LabelName
                    auto ld_label = LIRVirtualRegister::create();
                    addInstruction(LIRLoadInst::create(ld_label, getGlobalVar(glb_v)));
                    // load r2, [r1, rm/Imm]
                    addInstruction(LIRStoreInst::create(data, ld_label, offset));
                }
                    // 参数变量
                else if (auto a = dynamic_cast<Argument *>(top)) {
                    // 直接Load即可
                    addInstruction(LIRStoreInst::create(data, getRegOrConstant(a), offset));
                }
                    // Alloca出来的数组
                else if (auto al = dynamic_cast<AllocaInst *>(top)) {
                    // 计算相对于SP的偏移量
                    auto alloca = getAlloca(al);
                    if (auto c = dynamic_cast<LIRConstantOperand *>(offset)) {
                        offset = LIRConstantOperand::create(c->getValue() + alloca->getBase());
                    } else {
                        if (alloca->getBase() != 0) {
                            auto tmp = LIRVirtualRegister::create();
                            addInstruction(LIRBinaryInst::createAdd(tmp, offset, LIRConstantOperand::create(alloca->getBase())));
                            offset = tmp;
                        }
                    }
                    addInstruction(LIRStoreInst::create(data, LIRPhysicsRegister::create(13), offset));
                }
            }
            break;
        }
        case Instruction::cmp: {
            // 注意 CMP 的操作数来自CMP的情况
            auto cmp = dynamic_cast<CmpInst *>(inst);
            bool needToAdd = false;
            for (auto u: inst->get_use_list()) {
                if (dynamic_cast<CmpInst *>(u.val_)) {
                    needToAdd = true;
                    break;
                }
            }
            if (needToAdd) {
                auto lhs = cmp->get_operand(0);
                auto rhs = cmp->get_operand(1);
                bool inverse = inverseOperandIfNeeded(lhs, rhs);
                addInstruction(LIRCmpInst::create(getRegOrConstant(lhs), getRegOrConstant(rhs)));
                switch (cmp->get_cmp_op()) {
                    case CmpInst::EQ:
                        addInstruction(
                                LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1), LIRCond::LCondEQ));
                        addInstruction(
                                LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0), LIRCond::LCondNE));
                        break;
                    case CmpInst::NE:
                        addInstruction(
                                LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1), LIRCond::LCondNE));
                        addInstruction(
                                LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0), LIRCond::LCondEQ));
                        break;
                    case CmpInst::GT:
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1),
                                                              inverse ? LIRCond::LCondLE : LIRCond::LCondGT));
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0),
                                                              inverse ? LIRCond::LCondGT : LIRCond::LCondLE));
                        break;
                    case CmpInst::GE:
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1),
                                                              inverse ? LIRCond::LCondLT : LIRCond::LCondGE));
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0),
                                                              inverse ? LIRCond::LCondGE : LIRCond::LCondLT));
                        break;
                    case CmpInst::LT:
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1),
                                                              inverse ? LIRCond::LCondGE : LIRCond::LCondLT));
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0),
                                                              inverse ? LIRCond::LCondLT : LIRCond::LCondGE));
                        break;
                    case CmpInst::LE:
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1),
                                                              inverse ? LIRCond::LCondGT : LIRCond::LCondLE));
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0),
                                                              inverse ? LIRCond::LCondLE : LIRCond::LCondGT));
                        break;
                }
            }
            break;
        }
        case Instruction::phi:
            break;
        case Instruction::call: {
            auto call = dynamic_cast<CallInst *>(inst);
            auto ff = dynamic_cast<Function *>(call->get_operand(0));
            auto callee = getLFunction(ff);
            //TODO
            /*
            1. 维护栈帧指针，即13号寄存器
            2. 处理参数传递
            3. 处理返回值
            */
            break;
        }
        case Instruction::getelementptr: {
            // Calculate the offset value
            // GEP %alloca %1 %2 %3...  => 计算 %1 * dim 1 + %2 * dim 2 +...，调用时使用 Load Rd, [Sp, Rm/Imm]
            // GEP %global %1 %2 %3...  => 计算 %1 * dim 1 +... 调用时使用 1. Load r1, =%global 2. Load Rd, [r1, Rm/Imm]
            // 无论是哪种情况，我们都只需要计算偏移量即可。
            // 如果计算得到的偏移量是一个常数，则直接传入的是ASConstant而不是ASBinaryInst
            auto gep = dynamic_cast<GetElementPtrInst *>(inst);
            // 若 ptr 是 i32* 则只能有一个参数offset，计算的是 ptr + offset * 4. Argument型
            if (gep->get_operand(0)->get_type()->get_pointer_element_type()->is_int32_type()) {
                // 判断是来自GEP还是来自Argument
                if (dynamic_cast<Argument *>(gep->get_operand(0))) {
                    // 直接将偏移值存入mapping中
                    setRegister(inst, getRegOrConstant(gep->get_operand(1)));
                } else {
                    // 偏移量相加，注意常量
                    auto ori = getRegOrConstant(gep->get_operand(0));
                    auto off = gep->get_operand(1);
                    // 两个操作数都是常量，直接计算
                    if (auto off_c = dynamic_cast<ConstantInt *>(off)) {
                        if (auto constant = dynamic_cast<LIRConstantOperand *>(ori)) {
                            setRegister(inst, LIRConstantOperand::create(off_c->get_value() + constant->getValue()));
                            return;
                        }
                    }
                    auto off_c = getRegOrConstant(off);
                    if (dynamic_cast<LIRConstantOperand *>(ori)) std::swap(ori, off_c);
                    addInstruction(LIRBinaryInst::createAdd(getReg(inst), ori, off_c));
                }
            }
                // 若 ptr 是 Array*
            else {
                std::vector<int> dim;
                getDimensionByType(dim, gep->get_operand(0)->get_type()->get_pointer_element_type());
                std::vector<int> accumulate_offset(dim.size());
                accumulate_offset.back() = 1;
                for (int i = (int) dim.size() - 1; i > 0; --i) {
                    accumulate_offset[i-1] = accumulate_offset[i] * dim[i];
                }
                int const_offset = 0;
                std::vector<LIROperand *> var_offset;
                // 先把当前GEP内的总偏移计算出来，注意区分常量与变量
                for (int i = 2; i < gep->get_num_operand(); ++i) {
                    auto idx = gep->get_operand(i);
                    if (auto c = dynamic_cast<ConstantInt *>(idx)) {
                        const_offset += c->get_value() * accumulate_offset[i - 2];
                    }
                    else {
                        auto mv = LIRVirtualRegister::create();
                        auto ad = LIRVirtualRegister::create();
                        addInstruction(LIRMovInst::create(mv, LIRConstantOperand::create(accumulate_offset[i - 2])));
                        addInstruction(LIRBinaryInst::createMul(ad, getRegOrConstant(idx), mv));
                        var_offset.push_back(ad);
                    }
                }
                // 判断是否是顶层GEP
                if (!dynamic_cast<GetElementPtrInst *>(gep->get_operand(0))) {
                    // 指向的是Alloca或全局变量

                    // 判断是否完全是整数
                    if (var_offset.empty()) {
                        setRegister(inst, LIRConstantOperand::create(const_offset));
                    } else {
                        auto v = var_offset[0];
                        for (int i = 1; i < var_offset.size(); ++i) {
                            auto dst = LIRVirtualRegister::create();
                            addInstruction(LIRBinaryInst::createAdd(dst, v, var_offset[i]));
                            v = dst;
                        }
                        // 如果常量不为0也要加上
                        if (const_offset != 0) {
                            addInstruction(LIRBinaryInst::createAdd(getReg(inst), v, LIRConstantOperand::create(const_offset)));
                        } else {
                            setRegister(inst, v);
                        }
                    }
                } else {
                    // 指向GEP
                    auto parent_gep_val = getRegOrConstant(gep->get_operand(0));
                    // 判断是否完全是整数
                    if (var_offset.empty()) {
                        if (auto gep_c = dynamic_cast<LIRConstantOperand *>(parent_gep_val)) {
                            setRegister(inst, LIRConstantOperand::create(const_offset + gep_c->getValue()));
                        } else {
                            addInstruction(LIRBinaryInst::createAdd(getReg(inst), parent_gep_val, LIRConstantOperand::create(const_offset)));
                        }
                    } else {
                        if (auto gep_c = dynamic_cast<LIRConstantOperand *>(parent_gep_val)) {
                            const_offset += gep_c->getValue();
                        } else {
                            // 直接加上
                            auto tmp = LIRVirtualRegister::create();
                            addInstruction(LIRBinaryInst::createAdd(tmp, var_offset[0], parent_gep_val));
                            var_offset[0] = tmp;
                        }
                        auto v = var_offset[0];
                        for (int i = 1; i < var_offset.size(); ++i) {
                            auto tmp = LIRVirtualRegister::create();
                            addInstruction(LIRBinaryInst::createAdd(tmp, v, var_offset[i]));
                            v = tmp;
                        }
                        // 如果常量不为0也要加上
                        if (const_offset != 0) {
                            addInstruction(LIRBinaryInst::createAdd(getReg(inst), v, LIRConstantOperand::create(const_offset)));
                        } else {
                            setRegister(inst, v);
                        }
                    }
                }
            }
            break;
        }
        case Instruction::zext: {
            // Do nothing, map the incoming value to inst
            // 将CMP指令移过来然后赋值
            auto cond = dynamic_cast<CmpInst *>(inst->get_operand(0));
            if (auto ci = dynamic_cast<ConstantInt *>(cond)) {
                if (ci->get_value()) {
                    addInstruction(LIRMovInst::create(getReg(inst), LIRConstantOperand::create(1)));
                } else {
                    addInstruction(LIRMovInst::create(getReg(inst), LIRConstantOperand::create(0)));
                }
            } else {
                auto cmp = dynamic_cast<CmpInst *>(cond);
                auto lhs = cmp->get_operand(0);
                auto rhs = cmp->get_operand(1);
                bool inverse = inverseOperandIfNeeded(lhs, rhs);
                addInstruction(LIRCmpInst::create(getRegOrConstant(lhs), getRegOrConstant(rhs)));
                switch (cmp->get_cmp_op()) {
                    case CmpInst::EQ:
                        addInstruction(
                                LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1), LIRCond::LCondEQ));
                        addInstruction(
                                LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0), LIRCond::LCondNE));
                        break;
                    case CmpInst::NE:
                        addInstruction(
                                LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1), LIRCond::LCondNE));
                        addInstruction(
                                LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0), LIRCond::LCondEQ));
                        break;
                    case CmpInst::GT:
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1),
                                                              inverse ? LIRCond::LCondLE : LIRCond::LCondGT));
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0),
                                                              inverse ? LIRCond::LCondGT : LIRCond::LCondLE));
                        break;
                    case CmpInst::GE:
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1),
                                                              inverse ? LIRCond::LCondLT : LIRCond::LCondGE));
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0),
                                                              inverse ? LIRCond::LCondGE : LIRCond::LCondLT));
                        break;
                    case CmpInst::LT:
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1),
                                                              inverse ? LIRCond::LCondGE : LIRCond::LCondLT));
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0),
                                                              inverse ? LIRCond::LCondLT : LIRCond::LCondGE));
                        break;
                    case CmpInst::LE:
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(1),
                                                              inverse ? LIRCond::LCondGT : LIRCond::LCondLE));
                        addInstruction(LIRMovInst::createCond(getReg(inst), LIRConstantOperand::create(0),
                                                              inverse ? LIRCond::LCondLE : LIRCond::LCondGT));
                        break;
                }
            }
            break;
        }
    }
}

void LIRBuilder::addFunction(LIRFunction *f) {
    if (f->getName() == "main") {
        _funcList.push_front(f);
    } else {
        _funcList.push_back(f);
    }
}

std::vector<BasicBlock *> LIRBuilder::computeBasicBlockOrder(Function *f, CFG *cfg, LoopSearch *lp, dominator *dom) const {
    if (f->is_declaration()) return {};
    cfg->runOnFunction(f);
    dom->createRPO(f);
    std::map<BasicBlock *, int> incoming_forward_branches;
    std::map<BasicBlock *, int> loop_depth;
    std::vector<BasicBlock *> _queue;
    for (auto bb:f->get_basic_blocks()){
        incoming_forward_branches[bb]=0;
        Loop *loop=lp->get_smallest_loop(bb);
        loop_depth[bb]=0;
        while (loop){
            loop_depth[bb]++;
            loop=lp->get_outer_loop(loop);
        }
    }
    for (auto bb:f->get_basic_blocks()){
        for (auto succ: cfg->getSuccBB(bb)){
            if (dom->isLoopEdge(bb,succ)){
                incoming_forward_branches[succ]++;
            }
        }
    }
    // BFS遍历BB，若遇到循环则优先处理循环中的块
    struct cal_bb{
        BasicBlock *bb;
        int loop_depth;
        cal_bb (BasicBlock *_bb,int _loop_depth):bb(_bb),loop_depth(_loop_depth){};
        bool operator< (const cal_bb &a) const {return this->loop_depth < a.loop_depth;}
    };
    std::priority_queue<cal_bb> pq;
    auto temp=f->get_entry_block();
    pq.push(cal_bb(temp,loop_depth[temp]));
    while (!pq.empty()){
        auto bb=pq.top();
        pq.pop();
        _queue.push_back(bb.bb);
        for (auto succ_bb: cfg->getSuccBB(bb.bb)){
            if (!dom->isLoopEdge(bb.bb,succ_bb)) continue;
            incoming_forward_branches[succ_bb]--;
            if (incoming_forward_branches[succ_bb]==0){
                pq.push(cal_bb(succ_bb,loop_depth[succ_bb]));
            }
        }
    }
    return _queue;
}