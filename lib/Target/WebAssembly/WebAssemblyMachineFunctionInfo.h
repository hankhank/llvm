// WebAssemblyMachineFunctionInfo.h-WebAssembly machine function info-*- C++ -*-
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief This file declares WebAssembly-specific per-machine-function
/// information.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_WEBASSEMBLY_WEBASSEMBLYMACHINEFUNCTIONINFO_H
#define LLVM_LIB_TARGET_WEBASSEMBLY_WEBASSEMBLYMACHINEFUNCTIONINFO_H

#include "WebAssemblyRegisterInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

namespace llvm {

/// This class is derived from MachineFunctionInfo and contains private
/// WebAssembly-specific information for each MachineFunction.
class WebAssemblyFunctionInfo final : public MachineFunctionInfo {
  MachineFunction &MF;

  std::vector<MVT> Params;
  std::vector<MVT> Results;

  /// A mapping from CodeGen vreg index to WebAssembly register number.
  std::vector<unsigned> WARegs;

public:
  explicit WebAssemblyFunctionInfo(MachineFunction &MF) : MF(MF) {}
  ~WebAssemblyFunctionInfo() override;

  void addParam(MVT VT) { Params.push_back(VT); }
  const std::vector<MVT> &getParams() const { return Params; }

  void addResult(MVT VT) { Results.push_back(VT); }
  const std::vector<MVT> &getResults() const { return Results; }

  void initWARegs() {
    assert(WARegs.empty());
    WARegs.resize(MF.getRegInfo().getNumVirtRegs(), -1u);
  }
  void setWAReg(unsigned VReg, unsigned WAReg) {
    WARegs[TargetRegisterInfo::virtReg2Index(VReg)] = WAReg;
  }
  unsigned getWAReg(unsigned VReg) const {
    return WARegs[TargetRegisterInfo::virtReg2Index(VReg)];
  }
};

} // end namespace llvm

#endif
