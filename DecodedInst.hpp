//
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2018 Western Digital Corporation or its affiliates.
// 
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
// 
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <https://www.gnu.org/licenses/>.
//

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "FpRegs.hpp"
#include "InstId.hpp"


namespace WdRiscv
{

  class InstInfo;   // Static instance information.

  /// Model a decoded instruction: instruction address, opcode, and
  /// operand fields.
  class DecodedInst
  {
  public:
    
    /// Default contructor: Define an invalid object.
    DecodedInst()
      : addr_(0), inst_(0), size_(0), info_(nullptr),
	op0_(0), op1_(0), op2_(0), op3_(0)
    { }

    /// Constructor.
    DecodedInst(uint64_t addr, uint32_t inst, uint32_t size,
		const InstInfo* info,
		uint32_t op0, uint32_t op1, int32_t op2, int32_t op3)
      : addr_(addr), inst_(inst), size_(size), info_(info),
	op0_(op0), op1_(op1), op2_(op2), op3_(op3)
    { }

    /// Return instruction size.
    uint32_t instSize() const
    { return size_; }

    /// Return address of instruction.
    uint64_t address() const
    { return addr_; }

    /// Return instruction code.
    uint32_t inst() const
    { return inst_; }

    /// Return the 1st operand (zero if instruction has no operands).
    /// First operand is typically the destination register.
    uint32_t op0() const
    { return op0_; }

    /// Return 2nd operand (zero if instruction has no 2nd operand).
    /// Second operand is typically source register rs1.
    uint32_t op1() const
    { return op1_; }

    /// Return 3rd operand (zero if instruction has no 3rd operand).
    /// Third operand is typically source register rs2 or immediate
    /// value.
    int32_t op2() const
    { return op2_; }

    /// Return 4th operand (zero if instruction has no 4th operand).
    /// Fourth operand is typically source register rs3 for
    /// multiply-add like floating point instructions.
    int32_t op3() const
    { return op3_; }

    /// Alias for op0 for instructions having a destination register.
    uint32_t rd() const
    { return op0_; }

    /// Alias for op1 for instructions having one or more source
    /// registers.
    uint32_t rs1() const
    { return op1_; }

    /// Alias for op2 for instructions having two or more source
    /// registers.
    uint32_t rs2() const
    { return op2_; }

    /// Alias for op2 for instsructions having one source register and
    /// one immediate operand.
    int32_t imm() const
    { return op2_; }

    /// Alias for op3 for instructions having three source registers.
    uint32_t rs3() const
    { return op3_; }

    /// Return true if this object is valid.
    bool isValid()
    { return info_ != nullptr; }

    /// Make invalid.
    void invalidate()
    { info_ = nullptr; }

    /// Return associated instruction information.
    const InstInfo* instInfo() const
    { return info_; }

    // Relevant for floating point instructions.
    RoundingMode roundingMode() const
    { return rm_; }

    // Relevant for floating point instructions.
    void setRoundingMode(RoundingMode rm)
    { rm_ = rm; }

  private:

    uint64_t addr_;
    uint32_t inst_;
    uint32_t size_;
    const InstInfo* info_;
    uint32_t op0_;    // 1st operand (typically a register number)
    uint32_t op1_;    // 2nd operand (typically a register number) 
    int32_t op2_;     // 3rd operand (register number or immediate value)
    int32_t op3_;     // 4th operand (typically a register number)
    RoundingMode rm_ = RoundingMode::NearestEven;
  };

}
