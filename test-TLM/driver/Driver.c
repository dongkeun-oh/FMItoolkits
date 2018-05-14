/* Main Simulation File */
#include "Driver_model.h"

#define prefixedName_performSimulation Driver_performSimulation
#define prefixedName_updateContinuousSystem Driver_updateContinuousSystem
#include <simulation/solver/perform_simulation.c>

#define prefixedName_performQSSSimulation Driver_performQSSSimulation
#include <simulation/solver/perform_qss_simulation.c>

/* dummy VARINFO and FILEINFO */
const FILE_INFO dummyFILE_INFO = omc_dummyFileInfo;
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;
#if defined(__cplusplus)
extern "C" {
#endif

int Driver_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int Driver_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int Driver_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int Driver_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int Driver_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
 equation index: 15
 type: SIMPLE_ASSIGN
 der(tLMForce1D1._flange_b._s) = mass1.v
 */
void Driver_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  data->localData[0]->realVars[4] /* der(tLMForce1D1._flange_b._s) DUMMY_DER */ = data->localData[0]->realVars[1] /* mass1._v STATE(1,mass1.a) */;
  TRACE_POP
}
/*
 equation index: 16
 type: SIMPLE_ASSIGN
 tLMForce1D1._v = mass1.v
 */
void Driver_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  data->localData[0]->realVars[12] /* tLMForce1D1._v variable */ = data->localData[0]->realVars[1] /* mass1._v STATE(1,mass1.a) */;
  TRACE_POP
}
/*
 equation index: 17
 type: SIMPLE_ASSIGN
 tLMForce1D1._tlmDelay = TLM.TLM_Functions.TLMGetDelay(tLMForce1D1.interfaceName)
 */
void Driver_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  data->localData[0]->realVars[11] /* tLMForce1D1._tlmDelay variable */ = omc_TLM_TLM__Functions_TLMGetDelay(threadData, data->simulationInfo->stringParameter[0]);
  TRACE_POP
}
/*
 equation index: 18
 type: SIMPLE_ASSIGN
 force1._f = sin1.offset + (if time < sin1.startTime then 0.0 else sin1.amplitude * sin(6.283185307179586 * sin1.freqHz * (time - sin1.startTime) + sin1.phase))
 */
void Driver_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  modelica_boolean tmp0;
  RELATIONHYSTERESIS(tmp0, data->localData[0]->timeValue, data->simulationInfo->realParameter[6], 0, Less);
  data->localData[0]->realVars[5] /* force1._f variable */ = data->simulationInfo->realParameter[4] + (tmp0?0.0:(data->simulationInfo->realParameter[2]) * (sin((6.283185307179586) * ((data->simulationInfo->realParameter[3]) * (data->localData[0]->timeValue - data->simulationInfo->realParameter[6])) + data->simulationInfo->realParameter[5])));
  TRACE_POP
}
/*
 equation index: 19
 type: SIMPLE_ASSIGN
 der(mass1._s) = mass1.v
 */
void Driver_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  data->localData[0]->realVars[2] /* der(mass1._s) STATE_DER */ = data->localData[0]->realVars[1] /* mass1._v STATE(1,mass1.a) */;
  TRACE_POP
}
/*
 equation index: 20
 type: SIMPLE_ASSIGN
 force1._s = mass1.s + -0.5 * mass1.L
 */
void Driver_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  data->localData[0]->realVars[6] /* force1._s variable */ = data->localData[0]->realVars[0] /* mass1._s STATE(1,mass1.v) */ + (-0.5) * (data->simulationInfo->realParameter[0]);
  TRACE_POP
}
/*
 equation index: 21
 type: SIMPLE_ASSIGN
 tLMForce1D1._flange_b._s = mass1.s + 0.5 * mass1.L
 */
void Driver_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  data->localData[0]->realVars[10] /* tLMForce1D1._flange_b._s DUMMY_STATE */ = data->localData[0]->realVars[0] /* mass1._s STATE(1,mass1.v) */ + (0.5) * (data->simulationInfo->realParameter[0]);
  TRACE_POP
}
/*
 equation index: 22
 type: ALGORITHM
 
   tLMForce1D1.f := $START.tLMForce1D1.f;
   tLMForce1D1.f := TLM.TLM_Functions.TLMGetForce1D(tLMForce1D1.tlmPlugin, tLMForce1D1.interfaceName, time, tLMForce1D1.flange_b.s, mass1.v);
 */
void Driver_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  data->localData[0]->realVars[9] /* tLMForce1D1._f variable */ = data->modelData->realVarsData[9].attribute /* tLMForce1D1._f variable */.start;

  data->localData[0]->realVars[9] /* tLMForce1D1._f variable */ = omc_TLM_TLM__Functions_TLMGetForce1D(threadData, data->simulationInfo->extObjs[0], data->simulationInfo->stringParameter[0], data->localData[0]->timeValue, data->localData[0]->realVars[10] /* tLMForce1D1._flange_b._s DUMMY_STATE */, data->localData[0]->realVars[1] /* mass1._v STATE(1,mass1.a) */);
  TRACE_POP
}
/*
 equation index: 23
 type: SIMPLE_ASSIGN
 mass1._a = DIVISION(force1.f - tLMForce1D1.f, mass1.m)
 */
void Driver_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  data->localData[0]->realVars[8] /* mass1._a variable */ = DIVISION_SIM(data->localData[0]->realVars[5] /* force1._f variable */ - data->localData[0]->realVars[9] /* tLMForce1D1._f variable */,data->simulationInfo->realParameter[1],"mass1.m",equationIndexes);
  TRACE_POP
}
/*
 equation index: 24
 type: SIMPLE_ASSIGN
 der(mass1._v) = mass1.a
 */
void Driver_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  data->localData[0]->realVars[3] /* der(mass1._v) STATE_DER */ = data->localData[0]->realVars[8] /* mass1._a variable */;
  TRACE_POP
}


int Driver_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
  
  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  Driver_functionLocalKnownVars(data, threadData);
  Driver_eqFunction_15(data, threadData);

  Driver_eqFunction_16(data, threadData);

  Driver_eqFunction_17(data, threadData);

  Driver_eqFunction_18(data, threadData);

  Driver_eqFunction_19(data, threadData);

  Driver_eqFunction_20(data, threadData);

  Driver_eqFunction_21(data, threadData);

  Driver_eqFunction_22(data, threadData);

  Driver_eqFunction_23(data, threadData);

  Driver_eqFunction_24(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int Driver_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/* forwarded equations */
extern void Driver_eqFunction_18(DATA* data, threadData_t *threadData);
extern void Driver_eqFunction_19(DATA* data, threadData_t *threadData);
extern void Driver_eqFunction_21(DATA* data, threadData_t *threadData);
extern void Driver_eqFunction_22(DATA* data, threadData_t *threadData);
extern void Driver_eqFunction_23(DATA* data, threadData_t *threadData);
extern void Driver_eqFunction_24(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  Driver_eqFunction_18(data, threadData);

  Driver_eqFunction_19(data, threadData);

  Driver_eqFunction_21(data, threadData);

  Driver_eqFunction_22(data, threadData);

  Driver_eqFunction_23(data, threadData);

  Driver_eqFunction_24(data, threadData);
}

int Driver_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  data->simulationInfo->callStatistics.functionODE++;
  
  Driver_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

  
  TRACE_POP
  return 0;
}

#ifdef FMU_EXPERIMENTAL
#endif
/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "Driver_12jac.h"
#include "Driver_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks Driver_callback = {
   (int (*)(DATA *, threadData_t *, void *)) Driver_performSimulation,
   (int (*)(DATA *, threadData_t *, void *)) Driver_performQSSSimulation,
   Driver_updateContinuousSystem,
   Driver_callExternalObjectDestructors,
   NULL,
   NULL,
   NULL,
   #if !defined(OMC_NO_STATESELECTION)
   Driver_initializeStateSets,
   #else
   NULL,
   #endif
   Driver_initializeDAEmodeData,
   Driver_functionODE,
   Driver_functionAlgebraics,
   Driver_functionDAE,
   Driver_functionLocalKnownVars,
   Driver_input_function,
   Driver_input_function_init,
   Driver_input_function_updateStartValues,
   Driver_output_function,
   Driver_function_storeDelayed,
   Driver_updateBoundVariableAttributes,
   Driver_functionInitialEquations,
   0, /* useHomotopy - 0: no homotopy or local homotopy, 1: global homotopy, 2: new global homotopy approach */
   Driver_functionInitialEquations_lambda0,
   Driver_functionRemovedInitialEquations,
   Driver_updateBoundParameters,
   Driver_checkForAsserts,
   Driver_function_ZeroCrossingsEquations,
   Driver_function_ZeroCrossings,
   Driver_function_updateRelations,
   Driver_checkForDiscreteChanges,
   Driver_zeroCrossingDescription,
   Driver_relationDescription,
   Driver_function_initSample,
   Driver_INDEX_JAC_A,
   Driver_INDEX_JAC_B,
   Driver_INDEX_JAC_C,
   Driver_INDEX_JAC_D,
   Driver_initialAnalyticJacobianA,
   Driver_initialAnalyticJacobianB,
   Driver_initialAnalyticJacobianC,
   Driver_initialAnalyticJacobianD,
   Driver_functionJacA_column,
   Driver_functionJacB_column,
   Driver_functionJacC_column,
   Driver_functionJacD_column,
   Driver_linear_model_frame,
   Driver_linear_model_datarecovery_frame,
   Driver_mayer,
   Driver_lagrange,
   Driver_pickUpBoundsForInputsInOptimization,
   Driver_setInputData,
   Driver_getTimeGrid,
   Driver_symbolicInlineSystem,
   Driver_function_initSynchronous,
   Driver_function_updateSynchronous,
   Driver_function_equationsSynchronous,
   NULL,
   #ifdef FMU_EXPERIMENTAL
   Driver_functionODE_Partial,
   Driver_functionFMIJacobian,
   #endif
   Driver_inputNames
};

void Driver_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  data->callback = &Driver_callback;
  data->modelData->modelName = "Driver";
  data->modelData->modelFilePrefix = "Driver";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "/Users/spinhalf/Documents/Modelica/test/driver";
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
    #include "Driver_init.c"
    ;
  static const char contents_info[] =
    #include "Driver_info.c"
    ;
    data->modelData->initXMLData = contents_init;
    data->modelData->modelDataXml.infoXMLData = contents_info;
  }
  #else /* handle real compilers */
  data->modelData->initXMLData =
  #include "Driver_init.c"
    ;
  data->modelData->modelDataXml.infoXMLData =
  #include "Driver_info.c"
    ;
  #endif /* defined(_MSC_VER) */
  #endif /* defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME) */
  
  data->modelData->nStates = 2;
  data->modelData->nVariablesReal = 13;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 0;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 7;
  data->modelData->nParametersInteger = 1;
  data->modelData->nParametersBoolean = 2;
  data->modelData->nParametersString = 1;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 0;
  
  data->modelData->nAliasReal = 8;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 1;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 1;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 1;
  data->modelData->modelDataXml.fileName = "Driver_info.json";
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 5;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 30;
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
  
    Driver_setupDataStruc(&data, threadData);
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

