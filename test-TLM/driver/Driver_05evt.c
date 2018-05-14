/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "Driver_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void Driver_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *Driver_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"time < sin1.startTime"};
  static const int occurEqs0[] = {1,18};
  static const int *occurEqs[] = {occurEqs0};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */

int Driver_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  
  TRACE_POP
  return 0;
}

int Driver_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  modelica_boolean tmp0;
  
  data->simulationInfo->callStatistics.functionZeroCrossings++;
  
  tmp0 = LessZC(data->localData[0]->timeValue, data->simulationInfo->realParameter[6], data->simulationInfo->storedRelations[0]);
  gout[0] = (tmp0) ? 1 : -1;
  
  TRACE_POP
  return 0;
}

const char *Driver_relationDescription(int i)
{
  const char *res[] = {"time < sin1.startTime"};
  return res[i];
}

int Driver_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  modelica_boolean tmp1;
  
  if(evalforZeroCross) {
    tmp1 = LessZC(data->localData[0]->timeValue, data->simulationInfo->realParameter[6], data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[0] = tmp1;
  } else {
    data->simulationInfo->relations[0] = (data->localData[0]->timeValue < data->simulationInfo->realParameter[6]);
  }
  
  TRACE_POP
  return 0;
}

int Driver_checkForDiscreteChanges(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int needToIterate = 0;

  infoStreamPrint(LOG_EVENTS_V, 1, "check for discrete changes at time=%.12g", data->localData[0]->timeValue);
  if (ACTIVE_STREAM(LOG_EVENTS_V)) messageClose(LOG_EVENTS_V);
  
  TRACE_POP
  return needToIterate;
}

#if defined(__cplusplus)
}
#endif

