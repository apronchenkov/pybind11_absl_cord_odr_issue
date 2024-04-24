#include "absl/status/status.h"
#include "pybind11/pybind11.h"
#include "pybind11_abseil/status_casters.h"

#include <string>

namespace {

PYBIND11_MODULE(clib, m) {
  pybind11::google::ImportStatusModule();
  m.def(
      "erase_payload",
      [](absl::Status* status, std::string url) {
        status->ErasePayload(url);
      });
}

} // namespace
