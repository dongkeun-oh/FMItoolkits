/* Algebraic */
#include "Driver_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void Driver_eqFunction_20(DATA* data, threadData_t *threadData);
extern void Driver_eqFunction_17(DATA* data, threadData_t *threadData);
extern void Driver_eqFunction_16(DATA* data, threadData_t *threadData);
extern void Driver_eqFunction_15(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  Driver_eqFunction_20(data, threadData);

  Driver_eqFunction_17(data, threadData);

  Driver_eqFunction_16(data, threadData);

  Driver_eqFunction_15(data, threadData);
}
/* for continuous time variables */
int Driver_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  
  data->simulationInfo->callStatistics.functionAlgebraics++;
  
  functionAlg_system0(data, threadData);

  Driver_function_savePreSynchronous(data, threadData);
  
  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
