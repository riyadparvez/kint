#pragma once

#include <llvm/Support/Debug.h>
#include <llvm/Support/ConstantRange.h>

#if LLVM_VERSION_MAJOR == 3 && LLVM_VERSION_MINOR >= 3
#include <llvm/ADT/APInt.h>
#include <llvm/Support/DataTypes.h>
#endif

#ifndef LLVM_HAS_RVALUE_REFERENCES
#define LLVM_HAS_RVALUE_REFERENCES 1
#endif

// llvm::ConstantRange fixup.
class CRange {
public:
    static llvm::ConstantRange makeFullSet(uint32_t BitWidth) {
		return llvm::ConstantRange(BitWidth, true);
	}
	static llvm::ConstantRange makeEmptySet(uint32_t BitWidth) {
		return llvm::ConstantRange(BitWidth, false);
	}
	
    static llvm::ConstantRange makeICmpRegion(unsigned Pred, llvm::ConstantRange other) {
		return llvm::ConstantRange::makeICmpRegion(Pred, other);
	}

	static void match(llvm::ConstantRange& t, llvm::ConstantRange R) {
		if (t.getBitWidth() != R.getBitWidth()) {
			llvm::dbgs() << "warning: range " << t << " " 
				<< t.getBitWidth() << " and " << R << " "
				<< R.getBitWidth() << " unmatch\n";
			t = t.zextOrTrunc(R.getBitWidth());
		}
	}

    static bool safeUnion(llvm::ConstantRange &t, llvm::ConstantRange R) {
        llvm::ConstantRange V = R, Old = t;
		match(V, t);
		t = t.unionWith(V);
		return Old != t;
	}

	static llvm::ConstantRange sdiv(llvm::ConstantRange LHS, llvm::ConstantRange RHS) {
		if (LHS.isEmptySet() || RHS.isEmptySet())
			return makeEmptySet(LHS.getBitWidth());
		// FIXME: too conservative.
		return makeFullSet(LHS.getBitWidth());
	}
};
