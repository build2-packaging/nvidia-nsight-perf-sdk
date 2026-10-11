// Load the host library at runtime through nvperf_host_impl.h, as
// NvPerfUtility expects.
//
#include <nvperf_host_impl.h>

#include <NvPerfInit.h>
#include <NvPerfCounterConfiguration.h>
#include <NvPerfMetricsEvaluator.h>

#undef NDEBUG
#include <cassert>
#include <stdio.h>

int main ()
{
  const char* paths[] = { LIBNVPERF_HOST_DIR };

  NVPW_SetLibraryLoadPaths_Params lp {};
  lp.structSize = NVPW_SetLibraryLoadPaths_Params_STRUCT_SIZE;
  lp.numPaths = sizeof (paths) / sizeof (paths[0]);
  lp.ppPaths = paths;
  assert (NVPW_SetLibraryLoadPaths (&lp) == NVPA_STATUS_SUCCESS);

  NVPW_InitializeHost_Params p {};
  p.structSize = NVPW_InitializeHost_Params_STRUCT_SIZE;
  assert (NVPW_InitializeHost (&p) == NVPA_STATUS_SUCCESS);

  NVPW_InitializeTarget_Params tp {};
  tp.structSize = NVPW_InitializeTarget_Params_STRUCT_SIZE;
  assert (NVPW_InitializeTarget (&tp) == NVPA_STATUS_SUCCESS);

  // Devices are only enumerated after a graphics API driver is loaded.
  //
  NVPW_OpenGL_LoadDriver_Params dp {};
  dp.structSize = NVPW_OpenGL_LoadDriver_Params_STRUCT_SIZE;
  NVPA_Status s (NVPW_OpenGL_LoadDriver (&dp));
  printf ("NVPW_OpenGL_LoadDriver: %d\n", s);

  if (s != NVPA_STATUS_SUCCESS)
  {
    printf ("no driver, skipping the device check\n");
    return 0;
  }

  NVPW_GetDeviceCount_Params cp {};
  cp.structSize = NVPW_GetDeviceCount_Params_STRUCT_SIZE;
  assert (NVPW_GetDeviceCount (&cp) == NVPA_STATUS_SUCCESS);
  printf ("NVPW_GetDeviceCount: %zu devices\n", cp.numDevices);

  for (size_t i (0); i != cp.numDevices; ++i)
  {
    NVPW_Device_GetNames_Params np {};
    np.structSize = NVPW_Device_GetNames_Params_STRUCT_SIZE;
    np.deviceIndex = i;
    assert (NVPW_Device_GetNames (&np) == NVPA_STATUS_SUCCESS);
    assert (np.pDeviceName != nullptr && np.pChipName != nullptr);
    printf ("  %s (%s)\n", np.pDeviceName, np.pChipName);
  }
}
