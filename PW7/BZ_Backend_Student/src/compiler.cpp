#include <iostream>
#include <fstream>
#include <string>

#include "ast.h"
#include "parser.h"
#include "bzcompiler_builder.hpp"
#include "pass_manager.h"
#include "pass/mem2reg.h"
#include "pass/SCPcombineDCE.h"
#include "pass/CodeElimination.h"
#include "pass/CFG_simply.h"
#include "LIR/LIRBuilder.h"

int main(int argc, char *argv[]) {
    int i = 1;

    std::string input_filepath;
    std::string output_filepath;
    bool generate_ir = false;
    bool generate_assemble = false;

    while (i < argc) {
        std::string arg = argv[i];
        if (arg == "-emit-llvm") {
            generate_ir = true;
        } else if (arg == "-S") {
            generate_assemble = true;
        } else if (arg == "-o") {
            output_filepath = argv[++i];
        }
        else {
            if (input_filepath.empty()) {
                input_filepath = arg;
            } else {
                std::cout << "Unknown param: " << arg << std::endl;
            }
        }
        ++i;
    }
    if (input_filepath.empty()) {
        std::cout << "Error: Input filepath not specified " << std::endl;
        return 0;
    }
    if (output_filepath.empty()) {
        std::cout << "Error: Output filepath not specified " << std::endl;
        return 0;
    }
    // Parser
    SyntaxTree *st = parse(input_filepath.c_str());
    // AST
    auto *ast = new ASTProgram(st);
    // Builder
    BZBuilder builder;
    ast->accept(builder);
    Pass_manager pm(builder.getModule());
    // We always need to apply mem2reg
    pm.add_pass<CFG_simply>();
    pm.add_pass<Mem2Reg>();
    // We have to eliminate the  Constant +/-/*// Constant, as out ASM builder can't handle these type of operands
    pm.add_pass<ConstFoldingDCEliminating>();
    pm.add_pass<CodeElimination>();
    pm.add_pass<CFG_simply>();
    pm.add_pass<CodeElimination>();
    pm.run();
    // Now we can print the llvm ir code if needed
    if (generate_ir) {
        std::ofstream llvmIRStream;
        llvmIRStream.open(output_filepath + ".ll", std::ios::out);
        llvmIRStream << "; ModuleID = 'sysy2021_bzcompiler'\n";
        llvmIRStream << "source_filename = \""+ input_filepath +"\"\n\n";
        llvmIRStream << builder.getModule()->print();
        llvmIRStream.close();
    }
    // Generate assembly if needed
    if (generate_assemble) {
        LIRBuilder lir(builder.getModule());
        lir.build();
        std::ofstream ASMStream;
        ASMStream.open(output_filepath + ".s", std::ios::out);
        ASMStream << lir.print() << std::endl;
        ASMStream.close();
    }
}