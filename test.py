import clib
import pybind11_abseil.status as absl_status

for _ in range(10**6):
  status = absl_status.Status(absl_status.StatusCode.ABORTED, '')
  clib.add_payload(status)
