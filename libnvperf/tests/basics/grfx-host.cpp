#include <nvperf_host.h>

#undef NDEBUG
#include <cassert>

int main ()
{
  NVPW_InitializeHost_Params ip {};
  ip.structSize = NVPW_InitializeHost_Params_STRUCT_SIZE;
  assert (NVPW_InitializeHost (&ip) == NVPA_STATUS_SUCCESS);

  // The supported chips do not depend on the GPU in the machine.
  //
  NVPW_GetSupportedChipNames_Params cp {};
  cp.structSize = NVPW_GetSupportedChipNames_Params_STRUCT_SIZE;
  assert (NVPW_GetSupportedChipNames (&cp) == NVPA_STATUS_SUCCESS);
  assert (cp.numChipNames != 0);
}
