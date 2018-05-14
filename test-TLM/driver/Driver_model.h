/* Simulation code for Driver generated by the OpenModelica Compiler OpenModelica 1.12.0~3-g9389f90. */
#if !defined(Driver__MODEL_H)
#define Driver__MODEL_H
#include "openmodelica.h"
#include "openmodelica_func.h"
#include "simulation_data.h"
#include "simulation/simulation_info_json.h"
#include "simulation/simulation_runtime.h"
#include "util/omc_error.h"
#include "simulation/solver/model_help.h"
#include "simulation/solver/delay.h"
#include "simulation/solver/linearSystem.h"
#include "simulation/solver/nonlinearSystem.h"
#include "simulation/solver/mixedSystem.h"

#include <string.h>

#include "Driver_functions.h"

#define TLM_TLM__Functions_TLMGetDelay_index 0
#define TLM_TLM__Functions_TLMGetForce1D_index 1
#define TLM_TLM__Functions_TLMSetDebugMode_index 2
#define TLM_TLM__Functions_TLMPlugin_constructor_index 3
#define TLM_TLM__Functions_TLMPlugin_destructor_index 4

extern void Driver_callExternalObjectDestructors(DATA *_data, threadData_t *threadData);
#if !defined(OMC_NUM_NONLINEAR_SYSTEMS) || OMC_NUM_NONLINEAR_SYSTEMS>0
#endif
#if !defined(OMC_NUM_LINEAR_SYSTEMS) || OMC_NUM_LINEAR_SYSTEMS>0
#endif
#if !defined(OMC_NUM_MIXED_SYSTEMS) || OMC_NUM_MIXED_SYSTEMS>0
#endif
#if !defined(OMC_NO_STATESELECTION)
extern void Driver_initializeStateSets(int nStateSets, STATE_SET_DATA* statesetData, DATA *data);
#endif
extern int Driver_functionAlgebraics(DATA *data, threadData_t *threadData);
extern int Driver_function_storeDelayed(DATA *data, threadData_t *threadData);
extern int Driver_updateBoundVariableAttributes(DATA *data, threadData_t *threadData);
extern int Driver_functionInitialEquations(DATA *data, threadData_t *threadData);
extern int Driver_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData);
extern int Driver_functionRemovedInitialEquations(DATA *data, threadData_t *threadData);
extern int Driver_updateBoundParameters(DATA *data, threadData_t *threadData);
extern int Driver_checkForAsserts(DATA *data, threadData_t *threadData);
extern int Driver_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData);
extern int Driver_function_ZeroCrossings(DATA *data, threadData_t *threadData, double* gout);
extern int Driver_function_updateRelations(DATA *data, threadData_t *threadData, int evalZeroCross);
extern int Driver_checkForDiscreteChanges(DATA *data, threadData_t *threadData);
extern const char* Driver_zeroCrossingDescription(int i, int **out_EquationIndexes);
extern const char* Driver_relationDescription(int i);
extern void Driver_function_initSample(DATA *data, threadData_t *threadData);
extern int Driver_initialAnalyticJacobianG(void* data, threadData_t *threadData);
extern int Driver_initialAnalyticJacobianA(void* data, threadData_t *threadData);
extern int Driver_initialAnalyticJacobianB(void* data, threadData_t *threadData);
extern int Driver_initialAnalyticJacobianC(void* data, threadData_t *threadData);
extern int Driver_initialAnalyticJacobianD(void* data, threadData_t *threadData);
extern int Driver_functionJacG_column(void* data, threadData_t *threadData);
extern int Driver_functionJacA_column(void* data, threadData_t *threadData);
extern int Driver_functionJacB_column(void* data, threadData_t *threadData);
extern int Driver_functionJacC_column(void* data, threadData_t *threadData);
extern int Driver_functionJacD_column(void* data, threadData_t *threadData);
extern const char* Driver_linear_model_frame(void);
extern const char* Driver_linear_model_datarecovery_frame(void);
extern int Driver_mayer(DATA* data, modelica_real** res, short *);
extern int Driver_lagrange(DATA* data, modelica_real** res, short *, short *);
extern int Driver_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
extern int Driver_setInputData(DATA *data, const modelica_boolean file);
extern int Driver_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
extern void Driver_function_initSynchronous(DATA * data, threadData_t *threadData);
extern void Driver_function_updateSynchronous(DATA * data, threadData_t *threadData, long i);
extern int Driver_function_equationsSynchronous(DATA * data, threadData_t *threadData, long i);
extern void Driver_read_input_fmu(MODEL_DATA* modelData, SIMULATION_INFO* simulationData);
extern void Driver_function_savePreSynchronous(DATA *data, threadData_t *threadData);
extern int Driver_inputNames(DATA* data, char ** names);
extern int Driver_initializeDAEmodeData(DATA *data, DAEMODE_DATA*);
extern int Driver_functionLocalKnownVars(DATA*, threadData_t*);
extern int Driver_symbolicInlineSystem(DATA*, threadData_t*);

#include "Driver_literals.h"




#if defined(HPCOM) && !defined(_OPENMP)
  #error "HPCOM requires OpenMP or the results are wrong"
#endif
#if defined(_OPENMP)
  #include <omp.h>
#else
  /* dummy omp defines */
  #define omp_get_max_threads() 1
#endif

#endif

