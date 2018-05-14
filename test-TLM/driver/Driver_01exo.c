/* External objects file */
#include "Driver_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

void Driver_callExternalObjectDestructors(DATA *data, threadData_t *threadData)
{
  if(data->simulationInfo->extObjs)
  {
    omc_TLM_TLM__Functions_TLMPlugin_destructor(threadData,data->simulationInfo->extObjs[0]);
    free(data->simulationInfo->extObjs);
    data->simulationInfo->extObjs = 0;
  }
}
#if defined(__cplusplus)
}
#endif

