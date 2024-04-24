#include "absl/status/status.h"
#include "pybind11/pybind11.h"
#include "pybind11_abseil/status_casters.h"

namespace {

PYBIND11_MODULE(clib, m) {
  m.def(
      "add_payload",
      [](absl::Status* status) {
        status->SetPayload("url", absl::MakeCordFromExternal("hello, world!",
                                                             [](absl::string_view) {}));
      });
}

} // namespace
