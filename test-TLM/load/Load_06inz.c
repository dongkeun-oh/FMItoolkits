/* Initialization */
#include "Load_model.h"
#include "Load_11mix.h"
#include "Load_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void Load_functionInitialEquations_0(DATA *data, threadData_t *threadData);


/*
 equation index: 1
 type: SIMPLE_ASSIGN
 mass2._s = $START.mass2.s
 */
void Load_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->localData[0]->realVars[13] /* mass2._s DUMMY_STATE */ = data->modelData->realVarsData[13].attribute /* mass2._s DUMMY_STATE */.start;
  TRACE_POP
}

/*
 equation index: 2
 type: SIMPLE_ASSIGN
 damper1._flange_a._s = mass2.s + 0.5 * mass2.L
 */
void Load_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  data->localData[0]->realVars[10] /* damper1._flange_a._s DUMMY_STATE */ = data->localData[0]->realVars[13] /* mass2._s DUMMY_STATE */ + (0.5) * (data->simulationInfo->realParameter[3]);
  TRACE_POP
}

/*
 equation index: 3
 type: SIMPLE_ASSIGN
 damper1._s_rel = fixed1.s0 - damper1.flange_a.s
 */
void Load_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  data->localData[0]->realVars[0] /* damper1._s_rel STATE(1,damper1.v_rel) */ = data->simulationInfo->realParameter[2] - data->localData[0]->realVars[10] /* damper1._flange_a._s DUMMY_STATE */;
  TRACE_POP
}

/*
 equation index: 4
 type: SIMPLE_ASSIGN
 tLMForce1D1._flange_b._s = mass2.s + -0.5 * mass2.L
 */
void Load_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  data->localData[0]->realVars[16] /* tLMForce1D1._flange_b._s DUMMY_STATE */ = data->localData[0]->realVars[13] /* mass2._s DUMMY_STATE */ + (-0.5) * (data->simulationInfo->realParameter[3]);
  TRACE_POP
}

/*
 equation index: 5
 type: SIMPLE_ASSIGN
 mass2._v = $START.mass2.v
 */
void Load_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  data->localData[0]->realVars[14] /* mass2._v DUMMY_STATE */ = data->modelData->realVarsData[14].attribute /* mass2._v DUMMY_STATE */.start;
  TRACE_POP
}

/*
 equation index: 6
 type: SIMPLE_ASSIGN
 der(damper1._flange_a._s) = mass2.v
 */
void Load_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  data->localData[0]->realVars[5] /* der(damper1._flange_a._s) DUMMY_DER */ = data->localData[0]->realVars[14] /* mass2._v DUMMY_STATE */;
  TRACE_POP
}

/*
 equation index: 7
 type: SIMPLE_ASSIGN
 damper1._v_rel = -$DER.damper1.flange_a.s
 */
void Load_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */ = (-data->localData[0]->realVars[5] /* der(damper1._flange_a._s) DUMMY_DER */);
  TRACE_POP
}

/*
 equation index: 8
 type: SIMPLE_ASSIGN
 damper1._f = damper1.d * damper1.v_rel
 */
void Load_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  data->localData[0]->realVars[9] /* damper1._f variable */ = (data->simulationInfo->realParameter[0]) * (data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */);
  TRACE_POP
}

/*
 equation index: 9
 type: SIMPLE_ASSIGN
 damper1._lossPower = damper1.f * damper1.v_rel
 */
void Load_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  data->localData[0]->realVars[11] /* damper1._lossPower variable */ = (data->localData[0]->realVars[9] /* damper1._f variable */) * (data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */);
  TRACE_POP
}

/*
 equation index: 10
 type: SIMPLE_ASSIGN
 der(damper1._s_rel) = damper1.v_rel
 */
void Load_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  data->localData[0]->realVars[2] /* der(damper1._s_rel) STATE_DER */ = data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */;
  TRACE_POP
}

/*
 equation index: 11
 type: SIMPLE_ASSIGN
 der(mass2._s) = mass2.v
 */
void Load_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  data->localData[0]->realVars[6] /* der(mass2._s) DUMMY_DER */ = data->localData[0]->realVars[14] /* mass2._v DUMMY_STATE */;
  TRACE_POP
}

/*
 equation index: 12
 type: SIMPLE_ASSIGN
 tLMForce1D1._v = mass2.v
 */
void Load_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  data->localData[0]->realVars[18] /* tLMForce1D1._v variable */ = data->localData[0]->realVars[14] /* mass2._v DUMMY_STATE */;
  TRACE_POP
}

/*
 equation index: 13
 type: SIMPLE_ASSIGN
 der(tLMForce1D1._flange_b._s) = tLMForce1D1.v
 */
void Load_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  data->localData[0]->realVars[8] /* der(tLMForce1D1._flange_b._s) DUMMY_DER */ = data->localData[0]->realVars[18] /* tLMForce1D1._v variable */;
  TRACE_POP
}

/*
 equation index: 14
 type: ALGORITHM
 
   tLMForce1D1.f := TLM.TLM_Functions.TLMGetForce1D(tLMForce1D1.tlmPlugin, tLMForce1D1.interfaceName, time, tLMForce1D1.flange_b.s, tLMForce1D1.v);
 */
void Load_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  data->localData[0]->realVars[15] /* tLMForce1D1._f variable */ = omc_TLM_TLM__Functions_TLMGetForce1D(threadData, data->simulationInfo->extObjs[0], data->simulationInfo->stringParameter[0], data->localData[0]->timeValue, data->localData[0]->realVars[16] /* tLMForce1D1._flange_b._s DUMMY_STATE */, data->localData[0]->realVars[18] /* tLMForce1D1._v variable */);
  TRACE_POP
}

/*
 equation index: 15
 type: SIMPLE_ASSIGN
 mass2._a = DIVISION(damper1.f - tLMForce1D1.f, mass2.m)
 */
void Load_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  data->localData[0]->realVars[12] /* mass2._a variable */ = DIVISION_SIM(data->localData[0]->realVars[9] /* damper1._f variable */ - data->localData[0]->realVars[15] /* tLMForce1D1._f variable */,data->simulationInfo->realParameter[4],"mass2.m",equationIndexes);
  TRACE_POP
}

/*
 equation index: 16
 type: SIMPLE_ASSIGN
 der(mass2._v) = mass2.a
 */
void Load_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  data->localData[0]->realVars[7] /* der(mass2._v) DUMMY_DER */ = data->localData[0]->realVars[12] /* mass2._a variable */;
  TRACE_POP
}

/*
 equation index: 17
 type: SIMPLE_ASSIGN
 der(der(damper1._flange_a._s)) = mass2.a
 */
void Load_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  data->localData[0]->realVars[4] /* der(der(damper1._flange_a._s)) DUMMY_DER */ = data->localData[0]->realVars[12] /* mass2._a variable */;
  TRACE_POP
}

/*
 equation index: 18
 type: SIMPLE_ASSIGN
 der(damper1._v_rel) = -$DER.$DER.damper1.flange_a.s
 */
void Load_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  data->localData[0]->realVars[3] /* der(damper1._v_rel) STATE_DER */ = (-data->localData[0]->realVars[4] /* der(der(damper1._flange_a._s)) DUMMY_DER */);
  TRACE_POP
}

/*
 equation index: 19
 type: SIMPLE_ASSIGN
 tLMForce1D1._tlmDelay = TLM.TLM_Functions.TLMGetDelay(tLMForce1D1.interfaceName)
 */
void Load_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  data->localData[0]->realVars[17] /* tLMForce1D1._tlmDelay variable */ = omc_TLM_TLM__Functions_TLMGetDelay(threadData, data->simulationInfo->stringParameter[0]);
  TRACE_POP
}

/*
 equation index: 20
 type: ALGORITHM
 
   assert(tLMForce1D1.tlmDelay > 0.0, "Bad TLM delay in" + tLMForce1D1.interfaceName + ", give up");
   TLM.TLM_Functions.TLMSetDebugMode(tLMForce1D1.debugFlg);
 */
void Load_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  modelica_boolean tmp0;
  static const MMC_DEFSTRINGLIT(tmp1,16,"Bad TLM delay in");
  static const MMC_DEFSTRINGLIT(tmp2,9,", give up");
  static int tmp3 = 0;
  modelica_metatype tmpMeta[2] __attribute__((unused)) = {0};
  {
    tmp0 = Greater(data->localData[0]->realVars[17] /* tLMForce1D1._tlmDelay variable */,0.0);
    if(!tmp0)
    {
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp1),data->simulationInfo->stringParameter[0]);
      tmpMeta[1] = stringAppend(tmpMeta[0],MMC_REFSTRINGLIT(tmp2));
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
void Load_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  Load_eqFunction_1(data, threadData);
  Load_eqFunction_2(data, threadData);
  Load_eqFunction_3(data, threadData);
  Load_eqFunction_4(data, threadData);
  Load_eqFunction_5(data, threadData);
  Load_eqFunction_6(data, threadData);
  Load_eqFunction_7(data, threadData);
  Load_eqFunction_8(data, threadData);
  Load_eqFunction_9(data, threadData);
  Load_eqFunction_10(data, threadData);
  Load_eqFunction_11(data, threadData);
  Load_eqFunction_12(data, threadData);
  Load_eqFunction_13(data, threadData);
  Load_eqFunction_14(data, threadData);
  Load_eqFunction_15(data, threadData);
  Load_eqFunction_16(data, threadData);
  Load_eqFunction_17(data, threadData);
  Load_eqFunction_18(data, threadData);
  Load_eqFunction_19(data, threadData);
  Load_eqFunction_20(data, threadData);
  TRACE_POP
}


int Load_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  Load_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int Load_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}
int Load_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

