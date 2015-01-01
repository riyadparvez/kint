#pragma once

#include <llvm/Config/config.h>

#if LLVM_VERSION_MAJOR == 3 && LLVM_VERSION_MINOR < 2
#include <llvm/Support/IRBuilder.h>
#elif LLVM_VERSION_MAJOR == 3 && LLVM_VERSION_MINOR >= 3
#include <llvm/IR/IRBuilder.h>
#else
#include_next <llvm/IRBuilder.h>
#endif
