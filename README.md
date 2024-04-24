# How to run

```bash
git clone sso://user/axv/pybind11_absl_cord_odr_issue && cd pybind11_absl_cord_odr_issue && bazel run :test
# Causes: [cordz_info.h : 223] RAW: Check list_ == &global_list_ failed: ODR violation in Cord
```

# A probable explanation

It appears that the root cause of the problem is that both `//:clib` and `@pybind11_abseil//pybind11_abseil:status.so` include statically linked components of Abseil.

`absl::Status` uses `absl::Cord` to store the payload. 

`absl::Cord` has a built-in profiling mechanism that collects samples with a certain frequency. When it collects a sample, it checks for ODR violations.

When constructing a status payload in python (i.e. using the `pybind11_abseil` instance of Abseil) and deallocating it in the `clib` pybind extension, there is a small probability that we trigger a sample collection, which subsequently crashes the process. By repeating this process many times, we can reliably cause the crash.


