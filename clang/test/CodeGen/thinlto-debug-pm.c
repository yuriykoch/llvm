// Test to ensure the opt level is passed down to the ThinLTO backend.
// REQUIRES: x86-registered-target

// TODO: remove redundant `-fno-legacy-pass-manager` key from RUN-lines once we move to NewPM by default.

// RUN: %clang_cc1 -fno-legacy-pass-manager -O2 -o %t.o -flto=thin -triple x86_64-unknown-linux-gnu -emit-llvm-bc %s
// RUN: llvm-lto -thinlto -o %t %t.o

// RUN: %clang_cc1 -fno-legacy-pass-manager -triple x86_64-unknown-linux-gnu -emit-obj -O2 -o %t2.o -x ir %t.o -fthinlto-index=%t.thinlto.bc -fdebug-pass-manager 2>&1 | FileCheck %s --check-prefix=O2
// O2: Running pass: LoopVectorizePass

// RUN: %clang_cc1 -fno-legacy-pass-manager -O0 -o %t.o -flto=thin -triple x86_64-unknown-linux-gnu -emit-llvm-bc %s
// RUN: llvm-lto -thinlto -o %t %t.o

// RUN: %clang_cc1 -fno-legacy-pass-manager -triple x86_64-unknown-linux-gnu -emit-obj -O0 -o %t2.o -x ir %t.o -fthinlto-index=%t.thinlto.bc -fdebug-pass-manager 2>&1 | FileCheck %s --check-prefix=O0
// O0-NOT: Running pass: LoopVectorizePass

void foo() {
}
