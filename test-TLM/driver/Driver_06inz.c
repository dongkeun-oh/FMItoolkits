/* Initialization */
#include "Driver_model.h"
#include "Driver_11mix.h"
#include "Driver_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void Driver_functionInitialEquations_0(DATA *data, threadData_t *threadData);


/*
 equation index: 1
 type: SIMPLE_ASSIGN
 force1._s_support = 0.0
 */
void Driver_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->localData[0]->realVars[7] /* force1._s_support variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 2
 type: SIMPLE_ASSIGN
 mass1._v = $START.mass1.v
 */
void Driver_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  data->localData[0]->realVars[1] /* mass1._v STATE(1,mass1.a) */ = data->modelData->realVarsData[1].attribute /* mass1._v STATE(1,mass1.a) */.start;
  TRACE_POP
}

/*
 equation index: 3
 type: SIMPLE_ASSIGN
 mass1._s = $START.mass1.s
 */
void Driver_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  data->localData[0]->realVars[0] /* mass1._s STATE(1,mass1.v) */ = data->modelData->realVarsData[0].attribute /* mass1._s STATE(1,mass1.v) */.start;
  TRACE_POP
}

/*
 equation index: 4
 type: SIMPLE_ASSIGN
 force1._f = sin1.offset + (if time < sin1.startTime then 0.0 else sin1.amplitude * sin(6.283185307179586 * sin1.freqHz * (time - sin1.startTime) + sin1.phase))
 */
void Driver_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  modelica_boolean tmp0;
  tmp0 = Less(data->localData[0]->timeValue,data->simulationInfo->realParameter[6]);
  data->localData[0]->realVars[5] /* force1._f variable */ = data->simulationInfo->realParameter[4] + (tmp0?0.0:(data->simulationInfo->realParameter[2]) * (sin((6.283185307179586) * ((data->simulationInfo->realParameter[3]) * (data->localData[0]->timeValue - data->simulationInfo->realParameter[6])) + data->simulationInfo->realParameter[5])));
  TRACE_POP
}

/*
 equation index: 5
 type: SIMPLE_ASSIGN
 der(mass1._s) = mass1.v
 */
void Driver_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  data->localData[0]->realVars[2] /* der(mass1._s) STATE_DER */ = data->localData[0]->realVars[1] /* mass1._v STATE(1,mass1.a) */;
  TRACE_POP
}

/*
 equation index: 6
 type: SIMPLE_ASSIGN
 force1._s = mass1.s + -0.5 * mass1.L
 */
void Driver_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  data->localData[0]->realVars[6] /* force1._s variable */ = data->localData[0]->realVars[0] /* mass1._s STATE(1,mass1.v) */ + (-0.5) * (data->simulationInfo->realParameter[0]);
  TRACE_POP
}

/*
 equation index: 7
 type: SIMPLE_ASSIGN
 tLMForce1D1._v = mass1.v
 */
void Driver_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  data->localData[0]->realVars[12] /* tLMForce1D1._v variable */ = data->localData[0]->realVars[1] /* mass1._v STATE(1,mass1.a) */;
  TRACE_POP
}

/*
 equation index: 8
 type: SIMPLE_ASSIGN
 der(tLMForce1D1._flange_b._s) = tLMForce1D1.v
 */
void Driver_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  data->localData[0]->realVars[4] /* der(tLMForce1D1._flange_b._s) DUMMY_DER */ = data->localData[0]->realVars[12] /* tLMForce1D1._v variable */;
  TRACE_POP
}

/*
 equation index: 9
 type: SIMPLE_ASSIGN
 tLMForce1D1._flange_b._s = mass1.s + 0.5 * mass1.L
 */
void Driver_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  data->localData[0]->realVars[10] /* tLMForce1D1._flange_b._s DUMMY_STATE */ = data->localData[0]->realVars[0] /* mass1._s STATE(1,mass1.v) */ + (0.5) * (data->simulationInfo->realParameter[0]);
  TRACE_POP
}

/*
 equation index: 10
 type: ALGORITHM
 
   tLMForce1D1.f := TLM.TLM_Functions.TLMGetForce1D(tLMForce1D1.tlmPlugin, tLMForce1D1.interfaceName, time, tLMForce1D1.flange_b.s, tLMForce1D1.v);
 */
void Driver_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  data->localData[0]->realVars[9] /* tLMForce1D1._f variable */ = omc_TLM_TLM__Functions_TLMGetForce1D(threadData, data->simulationInfo->extObjs[0], data->simulationInfo->stringParameter[0], data->localData[0]->timeValue, data->localData[0]->realVars[10] /* tLMForce1D1._flange_b._s DUMMY_STATE */, data->localData[0]->realVars[12] /* tLMForce1D1._v variable */);
  TRACE_POP
}

/*
 equation index: 11
 type: SIMPLE_ASSIGN
 mass1._a = DIVISION(force1.f - tLMForce1D1.f, mass1.m)
 */
void Driver_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  data->localData[0]->realVars[8] /* mass1._a variable */ = DIVISION_SIM(data->localData[0]->realVars[5] /* force1._f variable */ - data->localData[0]->realVars[9] /* tLMForce1D1._f variable */,data->simulationInfo->realParameter[1],"mass1.m",equationIndexes);
  TRACE_POP
}

/*
 equation index: 12
 type: SIMPLE_ASSIGN
 der(mass1._v) = mass1.a
 */
void Driver_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  data->localData[0]->realVars[3] /* der(mass1._v) STATE_DER */ = data->localData[0]->realVars[8] /* mass1._a variable */;
  TRACE_POP
}

/*
 equation index: 13
 type: SIMPLE_ASSIGN
 tLMForce1D1._tlmDelay = TLM.TLM_Functions.TLMGetDelay(tLMForce1D1.interfaceName)
 */
void Driver_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  data->localData[0]->realVars[11] /* tLMForce1D1._tlmDelay variable */ = omc_TLM_TLM__Functions_TLMGetDelay(threadData, data->simulationInfo->stringParameter[0]);
  TRACE_POP
}

/*
 equation index: 14
 type: ALGORITHM
 
   assert(tLMForce1D1.tlmDelay > 0.0, "Bad TLM delay in" + tLMForce1D1.interfaceName + ", give up");
   TLM.TLM_Functions.TLMSetDebugMode(tLMForce1D1.debugFlg);
 */
void Driver_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  modelica_boolean tmp1;
  static const MMC_DEFSTRINGLIT(tmp2,16,"Bad TLM delay in");
  static const MMC_DEFSTRINGLIT(tmp3,9,", give up");
  static int tmp4 = 0;
  modelica_metatype tmpMeta[2] __attribute__((unused)) = {0};
  {
    tmp1 = Greater(data->localData[0]->realVars[11] /* tLMForce1D1._tlmDelay variable */,0.0);
    if(!tmp1)
    {
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp2),data->simulationInfo->stringParameter[0]);
      tmpMeta[1] = stringAppend(tmpMeta[0],MMC_REFSTRINGLIT(tmp3));
      {
        FILE_INFO info = {"/Users/spinhalf/Documents/Modelica/OMTLMSimulator/bin/OpenModelica/OM_TLM.mo",206,3,206,75,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\ntLMForce1D1.tlmDelay > 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_withEquationIndexes(threadData, info, equationIndexes, MMC_STRINGDATA(tmpMeta[1]));
      }
    }
  }

  omc_TLM_TLM__Functions_TLMSetDebugMode(threadData, data->simulationInfo->booleanParameter[1]);
  TRACE_POP
}
void Driver_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  Driver_eqFunction_1(data, threadData);
  Driver_eqFunction_2(data, threadData);
  Driver_eqFunction_3(data, threadData);
  Driver_eqFunction_4(data, threadData);
  Driver_eqFunction_5(data, threadData);
  Driver_eqFunction_6(data, threadData);
  Driver_eqFunction_7(data, threadData);
  Driver_eqFunction_8(data, threadData);
  Driver_eqFunction_9(data, threadData);
  Driver_eqFunction_10(data, threadData);
  Driver_eqFunction_11(data, threadData);
  Driver_eqFunction_12(data, threadData);
  Driver_eqFunction_13(data, threadData);
  Driver_eqFunction_14(data, threadData);
  TRACE_POP
}


int Driver_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  Driver_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int Driver_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}
int Driver_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

