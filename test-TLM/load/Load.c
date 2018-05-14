/* Main Simulation File */
#include "Load_model.h"

#define prefixedName_performSimulation Load_performSimulation
#define prefixedName_updateContinuousSystem Load_updateContinuousSystem
#include <simulation/solver/perform_simulation.c>

#define prefixedName_performQSSSimulation Load_performQSSSimulation
#include <simulation/solver/perform_qss_simulation.c>

/* dummy VARINFO and FILEINFO */
const FILE_INFO dummyFILE_INFO = omc_dummyFileInfo;
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;
#if defined(__cplusplus)
extern "C" {
#endif

int Load_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int Load_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int Load_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int Load_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int Load_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
 equation index: 21
 type: SIMPLE_ASSIGN
 der(tLMForce1D1._flange_b._s) = -damper1.v_rel
 */
void Load_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  data->localData[0]->realVars[8] /* der(tLMForce1D1._flange_b._s) DUMMY_DER */ = (-data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */);
  TRACE_POP
}
/*
 equation index: 22
 type: SIMPLE_ASSIGN
 tLMForce1D1._v = -damper1.v_rel
 */
void Load_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  data->localData[0]->realVars[18] /* tLMForce1D1._v variable */ = (-data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */);
  TRACE_POP
}
/*
 equation index: 23
 type: SIMPLE_ASSIGN
 der(mass2._s) = -damper1.v_rel
 */
void Load_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  data->localData[0]->realVars[6] /* der(mass2._s) DUMMY_DER */ = (-data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */);
  TRACE_POP
}
/*
 equation index: 24
 type: SIMPLE_ASSIGN
 mass2._v = -damper1.v_rel
 */
void Load_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  data->localData[0]->realVars[14] /* mass2._v DUMMY_STATE */ = (-data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */);
  TRACE_POP
}
/*
 equation index: 25
 type: SIMPLE_ASSIGN
 der(damper1._flange_a._s) = -damper1.v_rel
 */
void Load_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  data->localData[0]->realVars[5] /* der(damper1._flange_a._s) DUMMY_DER */ = (-data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */);
  TRACE_POP
}
/*
 equation index: 26
 type: SIMPLE_ASSIGN
 tLMForce1D1._tlmDelay = TLM.TLM_Functions.TLMGetDelay(tLMForce1D1.interfaceName)
 */
void Load_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  data->localData[0]->realVars[17] /* tLMForce1D1._tlmDelay variable */ = omc_TLM_TLM__Functions_TLMGetDelay(threadData, data->simulationInfo->stringParameter[0]);
  TRACE_POP
}
/*
 equation index: 27
 type: SIMPLE_ASSIGN
 der(damper1._s_rel) = damper1.v_rel
 */
void Load_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  data->localData[0]->realVars[2] /* der(damper1._s_rel) STATE_DER */ = data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */;
  TRACE_POP
}
/*
 equation index: 28
 type: SIMPLE_ASSIGN
 damper1._f = damper1.d * damper1.v_rel
 */
void Load_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  data->localData[0]->realVars[9] /* damper1._f variable */ = (data->simulationInfo->realParameter[0]) * (data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */);
  TRACE_POP
}
/*
 equation index: 29
 type: SIMPLE_ASSIGN
 damper1._lossPower = damper1.f * damper1.v_rel
 */
void Load_eqFunction_29(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,29};
  data->localData[0]->realVars[11] /* damper1._lossPower variable */ = (data->localData[0]->realVars[9] /* damper1._f variable */) * (data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */);
  TRACE_POP
}
/*
 equation index: 30
 type: SIMPLE_ASSIGN
 damper1._flange_a._s = fixed1.s0 - damper1.s_rel
 */
void Load_eqFunction_30(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,30};
  data->localData[0]->realVars[10] /* damper1._flange_a._s DUMMY_STATE */ = data->simulationInfo->realParameter[2] - data->localData[0]->realVars[0] /* damper1._s_rel STATE(1,damper1.v_rel) */;
  TRACE_POP
}
/*
 equation index: 31
 type: SIMPLE_ASSIGN
 mass2._s = damper1.flange_a.s - 0.5 * mass2.L
 */
void Load_eqFunction_31(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,31};
  data->localData[0]->realVars[13] /* mass2._s DUMMY_STATE */ = data->localData[0]->realVars[10] /* damper1._flange_a._s DUMMY_STATE */ - ((0.5) * (data->simulationInfo->realParameter[3]));
  TRACE_POP
}
/*
 equation index: 32
 type: SIMPLE_ASSIGN
 tLMForce1D1._flange_b._s = mass2.s + -0.5 * mass2.L
 */
void Load_eqFunction_32(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,32};
  data->localData[0]->realVars[16] /* tLMForce1D1._flange_b._s DUMMY_STATE */ = data->localData[0]->realVars[13] /* mass2._s DUMMY_STATE */ + (-0.5) * (data->simulationInfo->realParameter[3]);
  TRACE_POP
}
/*
 equation index: 33
 type: ALGORITHM
 
   tLMForce1D1.f := $START.tLMForce1D1.f;
   tLMForce1D1.f := TLM.TLM_Functions.TLMGetForce1D(tLMForce1D1.tlmPlugin, tLMForce1D1.interfaceName, time, tLMForce1D1.flange_b.s, -damper1.v_rel);
 */
void Load_eqFunction_33(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,33};
  data->localData[0]->realVars[15] /* tLMForce1D1._f variable */ = data->modelData->realVarsData[15].attribute /* tLMForce1D1._f variable */.start;

  data->localData[0]->realVars[15] /* tLMForce1D1._f variable */ = omc_TLM_TLM__Functions_TLMGetForce1D(threadData, data->simulationInfo->extObjs[0], data->simulationInfo->stringParameter[0], data->localData[0]->timeValue, data->localData[0]->realVars[16] /* tLMForce1D1._flange_b._s DUMMY_STATE */, (-data->localData[0]->realVars[1] /* damper1._v_rel STATE(1) */));
  TRACE_POP
}
/*
 equation index: 34
 type: SIMPLE_ASSIGN
 mass2._a = DIVISION(damper1.f - tLMForce1D1.f, mass2.m)
 */
void Load_eqFunction_34(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,34};
  data->localData[0]->realVars[12] /* mass2._a variable */ = DIVISION_SIM(data->localData[0]->realVars[9] /* damper1._f variable */ - data->localData[0]->realVars[15] /* tLMForce1D1._f variable */,data->simulationInfo->realParameter[4],"mass2.m",equationIndexes);
  TRACE_POP
}
/*
 equation index: 35
 type: SIMPLE_ASSIGN
 der(damper1._v_rel) = -mass2.a
 */
void Load_eqFunction_35(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,35};
  data->localData[0]->realVars[3] /* der(damper1._v_rel) STATE_DER */ = (-data->localData[0]->realVars[12] /* mass2._a variable */);
  TRACE_POP
}
/*
 equation index: 36
 type: SIMPLE_ASSIGN
 der(der(damper1._flange_a._s)) = mass2.a
 */
void Load_eqFunction_36(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,36};
  data->localData[0]->realVars[4] /* der(der(damper1._flange_a._s)) DUMMY_DER */ = data->localData[0]->realVars[12] /* mass2._a variable */;
  TRACE_POP
}
/*
 equation index: 37
 type: SIMPLE_ASSIGN
 der(mass2._v) = mass2.a
 */
void Load_eqFunction_37(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,37};
  data->localData[0]->realVars[7] /* der(mass2._v) DUMMY_DER */ = data->localData[0]->realVars[12] /* mass2._a variable */;
  TRACE_POP
}


int Load_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
  
  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  Load_functionLocalKnownVars(data, threadData);
  Load_eqFunction_21(data, threadData);

  Load_eqFunction_22(data, threadData);

  Load_eqFunction_23(data, threadData);

  Load_eqFunction_24(data, threadData);

  Load_eqFunction_25(data, threadData);

  Load_eqFunction_26(data, threadData);

  Load_eqFunction_27(data, threadData);

  Load_eqFunction_28(data, threadData);

  Load_eqFunction_29(data, threadData);

  Load_eqFunction_30(data, threadData);

  Load_eqFunction_31(data, threadData);

  Load_eqFunction_32(data, threadData);

  Load_eqFunction_33(data, threadData);

  Load_eqFunction_34(data, threadData);

  Load_eqFunction_35(data, threadData);

  Load_eqFunction_36(data, threadData);

  Load_eqFunction_37(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int Load_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/* forwarded equations */
extern void Load_eqFunction_27(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_28(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_30(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_31(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_32(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_33(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_34(DATA* data, threadData_t *threadData);
extern void Load_eqFunction_35(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  Load_eqFunction_27(data, threadData);

  Load_eqFunction_28(data, threadData);

  Load_eqFunction_30(data, threadData);

  Load_eqFunction_31(data, threadData);

  Load_eqFunction_32(data, threadData);

  Load_eqFunction_33(data, threadData);

  Load_eqFunction_34(data, threadData);

  Load_eqFunction_35(data, threadData);
}

int Load_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  data->simulationInfo->callStatistics.functionODE++;
  
  Load_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

  
  TRACE_POP
  return 0;
}

#ifdef FMU_EXPERIMENTAL
#endif
/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "Load_12jac.h"
#include "Load_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks Load_callback = {
   (int (*)(DATA *, threadData_t *, void *)) Load_performSimulation,
   (int (*)(DATA *, threadData_t *, void *)) Load_performQSSSimulation,
   Load_updateContinuousSystem,
   Load_callExternalObjectDestructors,
   NULL,
   NULL,
   NULL,
   #if !defined(OMC_NO_STATESELECTION)
   Load_initializeStateSets,
   #else
   NULL,
   #endif
   Load_initializeDAEmodeData,
   Load_functionODE,
   Load_functionAlgebraics,
   Load_functionDAE,
   Load_functionLocalKnownVars,
   Load_input_function,
   Load_input_function_init,
   Load_input_function_updateStartValues,
   Load_output_function,
   Load_function_storeDelayed,
   Load_updateBoundVariableAttributes,
   Load_functionInitialEquations,
   0, /* useHomotopy - 0: no homotopy or local homotopy, 1: global homotopy, 2: new global homotopy approach */
   Load_functionInitialEquations_lambda0,
   Load_functionRemovedInitialEquations,
   Load_updateBoundParameters,
   Load_checkForAsserts,
   Load_function_ZeroCrossingsEquations,
   Load_function_ZeroCrossings,
   Load_function_updateRelations,
   Load_checkForDiscreteChanges,
   Load_zeroCrossingDescription,
   Load_relationDescription,
   Load_function_initSample,
   Load_INDEX_JAC_A,
   Load_INDEX_JAC_B,
   Load_INDEX_JAC_C,
   Load_INDEX_JAC_D,
   Load_initialAnalyticJacobianA,
   Load_initialAnalyticJacobianB,
   Load_initialAnalyticJacobianC,
   Load_initialAnalyticJacobianD,
   Load_functionJacA_column,
   Load_functionJacB_column,
   Load_functionJacC_column,
   Load_functionJacD_column,
   Load_linear_model_frame,
   Load_linear_model_datarecovery_frame,
   Load_mayer,
   Load_lagrange,
   Load_pickUpBoundsForInputsInOptimization,
   Load_setInputData,
   Load_getTimeGrid,
   Load_symbolicInlineSystem,
   Load_function_initSynchronous,
   Load_function_updateSynchronous,
   Load_function_equationsSynchronous,
   NULL,
   #ifdef FMU_EXPERIMENTAL
   Load_functionODE_Partial,
   Load_functionFMIJacobian,
   #endif
   Load_inputNames
};

void Load_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  data->callback = &Load_callback;
  data->modelData->modelName = "Load";
  data->modelData->modelFilePrefix = "Load";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "/Users/spinhalf/Documents/Modelica/test/load";
  data->modelData->modelGUID = "{8c4e810f-3df3-4a00-8276-176fa3c9f9e0}";
  #if defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME)
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  #else
  #if defined(_MSC_VER) /* handle joke compilers */
  {
  /* for MSVC we encode a string like char x[] = {'a', 'b', 'c', '\0'} */
  /* because the string constant limit is 65535 bytes */
  static const char contents_init[] =
    #include "Load_init.c"
    ;
  static const char contents_info[] =
    #include "Load_info.c"
    ;
    data->modelData->initXMLData = contents_init;
    data->modelData->modelDataXml.infoXMLData = contents_info;
  }
  #else /* handle real compilers */
  data->modelData->initXMLData =
  #include "Load_init.c"
    ;
  data->modelData->modelDataXml.infoXMLData =
  #include "Load_info.c"
    ;
  #endif /* defined(_MSC_VER) */
  #endif /* defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME) */
  
  data->modelData->nStates = 2;
  data->modelData->nVariablesReal = 19;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 0;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 5;
  data->modelData->nParametersInteger = 2;
  data->modelData->nParametersBoolean = 2;
  data->modelData->nParametersString = 1;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 0;
  
  data->modelData->nAliasReal = 10;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 0;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 0;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 1;
  data->modelData->modelDataXml.fileName = "Load_info.json";
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 5;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 47;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 0;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 4;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  
  data->modelData->nDelayExpressions = 0;
  
  data->modelData->nClocks = 0;
  data->modelData->nSubClocks = 0;
  
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
}

#ifdef __cplusplus
}
#endif

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}

#if defined(threadData)
#undef threadData
#endif
/* call the simulation runtime main from our main! */
int main(int argc, char**argv)
{
  int res;
  DATA data;
  MODEL_DATA modelData;
  SIMULATION_INFO simInfo;
  data.modelData = &modelData;
  data.simulationInfo = &simInfo;
  measure_time_flag = 0;
  compiledInDAEMode = 0;
  compiledWithSymSolver = 0;
  MMC_INIT(0);
  omc_alloc_interface.init();
  {
    MMC_TRY_TOP()
  
    MMC_TRY_STACK()
  
    Load_setupDataStruc(&data, threadData);
    res = _main_SimulationRuntime(argc, argv, &data, threadData);
    
    MMC_ELSE()
    rml_execution_failed();
    fprintf(stderr, "Stack overflow detected and was not caught.\nSend us a bug report at https://trac.openmodelica.org/OpenModelica/newticket\n    Include the following trace:\n");
    printStacktraceMessages();
    fflush(NULL);
    return 1;
    MMC_CATCH_STACK()
    
    MMC_CATCH_TOP(return rml_execution_failed());
  }

  fflush(NULL);
  EXIT(res);
  return res;
}

