/* Algebraic */
#include "Load_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void Load_eqFunction_29(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_36(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_37(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_26(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_25(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_24(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_23(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_22(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_21(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  Load_eqFunction_29(data, threadData);

  Load_eqFunction_36(data, threadData);

  Load_eqFunction_37(data, threadData);

  Load_eqFunction_26(data, threadData);

  Load_eqFunction_25(data, threadData);

  Load_eqFunction_24(data, threadData);

  Load_eqFunction_23(data, threadData);

  Load_eqFunction_22(data, threadData);

  Load_eqFunction_21(data, threadData);
}
/* for continuous time variables */
int Load_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  
  data->simulationInfo->callStatistics.functionAlgebraics++;
  
  functionAlg_system0(data, threadData);

  Load_function_savePreSynchronous(data, threadData);
  
  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
