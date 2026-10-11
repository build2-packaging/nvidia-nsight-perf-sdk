# NVIDIA Nsight Perf SDK - Packaging Details

This document describes the approach applied to packaging `libnvperf` for
`build2`. In particular, this understanding will be useful when upgrading to
a new upstream version.

## Download

[`redist.build`](redist.build) downloads the SDK archive for the target
platform from `baseUrl` followed by that platform's `relativePath` in
[`manifest.json`](libnvperf/libnvperf/manifest.json). NVIDIA redirects this
URL to a short-lived download link, no developer account login is needed.
Each archive contains the files of all architectures, so the platform's
`exclude` patterns leave out the other architecture when extracting.
[`package.json`](libnvperf/libnvperf/package.json) lists the libraries and
executables that are exported from the extracted files.

## Cache directory

Archives land in `$out_root` by default. Only a symlink to the archive is a
target, so `b clean` leaves the cache alone. Set `config.libnvperf.cache`
for this package or `config.nvperf.cache` for all, the per-package value
wins.

    b "config.libnvperf.cache=/path/to/cache"

`config.nvperf.cache` is read at configure time into the per-package value,
so changing it afterwards needs a reconfigure.

## Release New Version

1. Find the new version on the
   [Nsight Perf SDK page](https://developer.nvidia.com/nsight-perf-sdk).
2. For each platform, update `relativePath` in
   [`manifest.json`](libnvperf/libnvperf/manifest.json). The archives are
   named `<YYYY_N>/NVIDIA_Nsight_Perf_SDK_<YYYY.N>_Public_Windows.zip` and
   `<YYYY_N>/NVIDIA_Nsight_Perf_SDK_<YYYY.N>_Public_Linux.tar.gz`.
3. Update `version` in [`manifest`](libnvperf/manifest). The full version
   is in the archive's `NvPerf/version.txt`.
4. List the new archives (`bsdtar -tf <archive>`) and update
   [`package.json`](libnvperf/libnvperf/package.json) and the license files
   in [`buildfile`](libnvperf/libnvperf/buildfile) for any renamed or new
   libraries, tools, or license files.
