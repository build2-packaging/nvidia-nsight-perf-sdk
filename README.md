# NVIDIA® Nsight Perf SDK

> **NOTE:**  
> This package is not open source and does not contain any source code. Instead,
> in order to "build" the exported target(s) it downloads (potentially large)
> pre-built binaries provided by NVIDIA for the target platform.
>
> CI for this package is disabled due to the above.  
> Supported platforms/compilers are Windows/MSVC and Linux (x86_64).

This is a `build2` package repository for [NVIDIA® Nsight Perf SDK](https://developer.nvidia.com/nsight-perf-sdk).

The NVIDIA® Nsight Perf SDK is a graphics profiling toolbox for DirectX,
Vulkan, and OpenGL that collects GPU performance metrics directly from an
application.

This file contains setup instructions and other details that are more
appropriate for package development rather than consumption. If you want to use
`nvidia-nsight-perf-sdk` in your `build2`-based project, then instead see the accompanying
package(s) corresponding [`PACKAGE-README.md`](libnvperf/PACKAGE-README.md) file.

The development setup for `nvidia-nsight-perf-sdk` uses the standard `bdep`-based workflow.
For example:

```
git clone https://github.com/build2-packaging/nvidia-nsight-perf-sdk
cd nvidia-nsight-perf-sdk

bdep init -C @msvc cc config.cxx=cl.exe
bdep update
bdep test
```

For how the package is put together, see [`README-DEV.md`](README-DEV.md).
