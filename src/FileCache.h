#pragma once

#include <llvm/ADT/StringMap.h>

namespace llvm {
	class DebugLoc;
	class LLVMContext;
	class MDNode;
	class MemoryBuffer;
} // namespace llvm

class FileCache {
public:
	~FileCache();
	llvm::StringRef getFile(llvm::StringRef Filename);
	llvm::StringRef getFile(const llvm::MDNode *);
	llvm::StringRef getLine(llvm::StringRef Filename, unsigned Line);
	llvm::StringRef getLine(const llvm::DebugLoc &, llvm::LLVMContext &);
private:
	typedef llvm::StringMap<llvm::MemoryBuffer *> BufferMap;
	BufferMap BM;
};