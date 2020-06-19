//LLVM TO ANNOTATE THE PROGRAM FOR RESOURCE ANALYSIS
// Copyright 2017 National University of Singapore
// See LICENSE.md for the license information.

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
using namespace std;
#include <string>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "llvm-c/TargetMachine.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constants.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm-c/BitWriter.h"
//#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/MemoryBuffer.h"

#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string

#define DEBUG 0

/*
 * Main.
 */
int main(int argc, char **argv) {
	llvm::LLVMContext &Context = llvm::getGlobalContext();
	llvm::SMDiagnostic Err;
	llvm::Module *M = ParseIRFile(argv[1], Err, Context);

	if (M == 0) {
		llvm::errs() << "ERROR: failed to load " << argv[0] << "\n";
		return 1;
	}
	if (DEBUG > 0)
		llvm::errs() << "Benchmark:" << argv[1] << "\n";

	 llvm::GlobalVariable *wcetValue;
	//for (auto &F : *M) {
	for (llvm::Module::global_iterator GI = M->global_begin(), GE =
			M->global_end(); GI != GE; ++GI) {
		if (GI->getName() == "wcet") {
			if (DEBUG > 0)
				GI->dump();
			wcetValue = GI;
			//llvm::errs() << *wcetValue << "\n";

		}
	}

	for (llvm::Module::iterator it = M->begin(), ie = M->end(); it != ie;
			++it) {
		if (!it->isIntrinsic() && (it->getName().str().substr(0, 5) != "klee_")
				&& (it->getName() != "memcpy") && (it->getName() != "memmove")
				&& (it->getName() != "mempcpy")
				&& (it->getName() != "memset")) {
					//      llvm::errs() << "Function: " << it->getName() << "\n";
			for (llvm::Function::iterator it1 = it->begin(), ie1 = it->end();
					it1 != ie1; ++it1) {
				llvm::IRBuilder<> IR(llvm::dyn_cast<llvm::BasicBlock>(it1));
				int totalInstruction = 0;
				for (llvm::BasicBlock::iterator ins = it1->begin(); ins != it1->end(); ++ins) {
					totalInstruction++;
				}
				//Computing total number of instrucitons in each block
				//llvm::errs() << "totalInstruction in each Blocks: " << totalInstruction << "\n";
                //Inserting wcet += totalInstruction; in each block
				llvm::IRBuilder<> builder(it1);
				builder.SetInsertPoint(it1->getFirstInsertionPt());
				llvm::LoadInst *Load = builder.CreateLoad(wcetValue);
				llvm::Value *Inc = builder.CreateAdd(IR.getInt32(totalInstruction), Load);
				llvm::StoreInst *Store = builder.CreateStore(Inc, wcetValue);

			}
		}
	}

	llvm::outs() << *M;
	return 0;
}

