# How to run

```bash
git clone sso://user/axv/pybind11_absl_cord_odr_issue && cd pybind11_absl_cord_odr_issue && bazel run :test
# Causes: [cordz_info.h : 223] RAW: Check list_ == &global_list_ failed: ODR violation in Cord
```

# A probable explanation

It appears that the root cause of the problem is that both `//:clib` and `@pybind11_abseil//pybind11_abseil:status.so` include statically linked components of Abseil.

`absl::Status` uses `absl::Cord` to store the payload.

`absl::Cord` has a built-in profiling mechanism that collects samples with a certain frequency. When it collects a sample, it checks for ODR violations:
  * absl/strings/internal/cordz_info.h
  * `CordzInfo::MaybeTrackCord()`
  * `CordzInfo::ODRCheck()`

When constructing a status with payload in the `clib` pybind extension and deallocating it in Python (i.e. using `pybind11_abseil`'s Abseil instance), there's a small chance of triggering a cord sample collection. The collection procedure detects a mismatched of Abseil instance with the `cord`'s original Abseil, leading to a process crash. By repeating this process many times, we can reliably cause the crash.
