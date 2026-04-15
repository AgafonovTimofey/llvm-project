#include "TAga.h"
#include "clang/Basic/Builtins.h"
#include "clang/Basic/MacroBuilder.h"

using namespace clang;
using namespace clang::targets;

void TAgaTargetInfo::getTargetDefines(const LangOptions &Opts,
                                     MacroBuilder &Builder) const {
  Builder.defineMacro("__taga__");
}

ArrayRef<Builtin::Info> TAgaTargetInfo::getTargetBuiltins() const {
  return std::nullopt;
}