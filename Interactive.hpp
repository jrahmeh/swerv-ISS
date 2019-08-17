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

#include <unordered_map>
#include "Core.hpp"


namespace WdRiscv
{

  /// Manage an interactive session. To use: Construct an instance
  /// with a vector of configured core then invoke the interact
  /// method which will read commands from the standard input and
  /// execute them until the quit command is seen.
  template <typename URV>
  class Interactive
  {
  public:

    /// Constructor.
    Interactive(std::vector< Core<URV>* >& coreVec);

    /// Read commands from the standard input and execute them.
    /// Instance traces go the the given traceFile (no instance
    /// tracing if traceFile is NULL). Executed commands are logged to
    /// the give commandLog file (no comand logging if commandLog is
    /// NULL). Return true if all commands are executed successfully.
    /// Return false otherwise.
    bool interact(FILE* traceFile, FILE* commandLog);

    /// Helper to interact: "until" command. Run until address.
    bool untilCommand(Core<URV>& core, const std::string& line,
		     const std::vector<std::string>& tokens,
		     FILE* traceFile);

    /// Helper to interact: "step" command. Single step.
    bool stepCommand(Core<URV>& core, const std::string& line,
		     const std::vector<std::string>& tokens, FILE* traceFile);

    /// Helper to interact: "peek" command. Examine a register/memory
    /// location.
    bool peekCommand(Core<URV>& core, const std::string& line,
		     const std::vector<std::string>& tokens);

    /// Helper to interact: "poke" command. Set a register/memory
    /// location.
    bool pokeCommand(Core<URV>& core, const std::string& line,
		     const std::vector<std::string>& tokens);

    /// Helper to interact: "disas" command. Disassemble.
    bool disassCommand(Core<URV>& core, const std::string& line,
		       const std::vector<std::string>& tokens);

    /// Helper to interact: "elf" command. Load ELF file.
    bool elfCommand(Core<URV>& core, const std::string& line,
		    const std::vector<std::string>& tokens);

    /// Helper to interact: "hex" command. Load HEX file.
    bool hexCommand(Core<URV>& core, const std::string& line,
		    const std::vector<std::string>& tokens);

    /// Helper to interact: "reset" command. Reset processor.
    bool resetCommand(Core<URV>& core, const std::string& line,
		     const std::vector<std::string>& tokens);

    /// Helper to interact: "replay_file" command. Define replay file.
    bool replayFileCommand(const std::string& line,
			   const std::vector<std::string>& tokens,
			   std::ifstream& stream);

    /// Helper to interact: "exception" command. Associate an
    /// exception with the first subsequently executed instruction.
    bool exceptionCommand(Core<URV>& core, const std::string& line,
			  const std::vector<std::string>& tokens);

    /// Helper to interact: "load_finished" command. Mark an non-blocking
    /// load instruction as completed.
    bool loadFinishedCommand(Core<URV>& core, const std::string& line,
			     const std::vector<std::string>& tokens);

    /// Helper to interact: "help" command.
    void helpCommand(const std::vector<std::string>& tokens);

    /// Helper to interact: "replay" command. Replay one or more
    /// commands from the replay file.
    bool replayCommand(unsigned& currentHartId,
		       const std::string& line,
		       const std::vector<std::string>& tokens,
		       FILE* traceFile, FILE* commandLog,
		       std::ifstream& replayStream, bool& done);

  protected:

    /// Helper to interact. Execute a user command.
    bool executeLine(unsigned& currentHartId,
		     const std::string& inLine, FILE* traceFile,
		     FILE* commandLog,
		     std::ifstream& replayStream, bool& done);

  private:

    std::vector< Core<URV>* >& cores_;

    // Initial resets do not reset memory mapped registers.
    bool resetMemoryMappedRegs_ = false;
  };

}
