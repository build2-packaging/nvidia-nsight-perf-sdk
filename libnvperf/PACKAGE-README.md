# libnvperf - A C++ library

> **NOTE:**  
> This package is not open source and does not contain any source code. Instead,
> in order to "build" the exported target(s) it downloads (potentially large)
> pre-built binaries provided by NVIDIA for the target platform.
>
> CI for this package is disabled due to the above.  
> Supported platforms/compilers are Windows/MSVC and Linux (x86_64).

The NVIDIA Nsight Perf SDK is a graphics profiling toolbox for DirectX,
Vulkan, and OpenGL that collects GPU performance metrics directly from an
application.

## Usage

To start using `libnvperf` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libnvperf ^2026.3.0
```

Then import the library in your `buildfile`:

```
import libs = libnvperf%lib{nvperf}
```


## Importable targets

This package provides the following importable targets:

```
lib{nvperf}
libs{nvperf_grfx_host}
exe{GpuDiag}
exe{MetricsEnumerator}
exe{Monitoring}
```

`lib{nvperf}` provides the SDK headers (`#include <nvperf_host.h>` and so
on) and the NvPerfUtility C++ headers (`#include <NvPerfInit.h>` and so
on). It is for loading the host library at runtime, which is what upstream
recommends: include `<nvperf_host_impl.h>` in one translation unit. The host
library is then found through the dynamic loader search path or the
directories passed to `NVPW_SetLibraryLoadPaths()`. Some NvPerfUtility
headers also need the headers of the graphics API they target (Direct3D,
Vulkan, OpenGL, or EGL) or of rapidyaml, Dear ImGui, or ImPlot, which this
package does not provide.

`libs{nvperf_grfx_host}` is the pre-built host library for linking against
directly, with the same headers.

`exe{GpuDiag}`, `exe{MetricsEnumerator}`, and `exe{Monitoring}` are the
pre-built SDK tools. On Linux they find `libnvperf_grfx_host.so` through
`LD_LIBRARY_PATH`, as in upstream.


## Configuration variables

This package provides the following configuration variables:

```
[dir_path] config.libnvperf.cache ?= $out_root
```

The directory used to cache downloaded binary archives between builds. If
`config.nvperf.cache` is set (a shared project-wide cache directory), it
takes precedence over the per-package default of `$out_root`.
