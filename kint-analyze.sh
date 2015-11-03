#!/bin/bash 

# Exit script on error
#set -e

die () {
    echo >&2 "$@"
    exit 1
}

# Check KINT_ROOT is defined
[ -d "$KINT_ROOT" ] || die "Define KINT_ROOT";

# Necessary for compiling Linux Kernel
#export CFLAGS=-Qunused-arguments
#export CPPFLAGS=-Qunused-arguments
#export ARCHFLAGS=-Wno-error=unused-command-line-argument

export LLVMCC=/home/riyad/installs/llvm-3.4/Release+Asserts/bin/clang

"$KINT_ROOT/build/bin/kint-build" make
#find $(pwd) -name "*.ll" > bitcode.lst
#"$KINT_ROOT/build/bin/intglobal" @bitcode.lst
# Check for 
#"$KINT_ROOT/build/bin/pintck"
# Check for warnings branches that are always taken or never taken
#"$KINT_ROOT/build/bin/pcmpck"
