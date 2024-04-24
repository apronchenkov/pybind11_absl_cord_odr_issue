#include "absl/status/status.h"
#include "absl/strings/cord.h"
#include "pybind11/pybind11.h"
#include "pybind11_abseil/status_casters.h"

#include <string>

namespace {

PYBIND11_MODULE(clib, m) {
  pybind11::google::ImportStatusModule();
  m.def(
      "error_with_payload",
      [] {
        auto result = absl::InvalidArgumentError("message");
        result.SetPayload("url", absl::Cord("payload!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
        return result;
      });
}

} // namespace
