/* Jacobians */
static const REAL_ATTRIBUTE dummyREAL_ATTRIBUTE = omc_dummyRealAttribute;
/* Jacobian Variables */
#if defined(__cplusplus)
extern "C" {
#endif
  #define Driver_INDEX_JAC_A 3
  int Driver_functionJacA_column(void* data, threadData_t *threadData);
  int Driver_initialAnalyticJacobianA(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* A */
#define $Pmass1_sSeedA data->simulationInfo->analyticJacobians[3].seedVars[0]
#define $Pmass1_vSeedA data->simulationInfo->analyticJacobians[3].seedVars[1]

#if defined(__cplusplus)
extern "C" {
#endif
  #define Driver_INDEX_JAC_B 2
  int Driver_functionJacB_column(void* data, threadData_t *threadData);
  int Driver_initialAnalyticJacobianB(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* B */

#if defined(__cplusplus)
extern "C" {
#endif
  #define Driver_INDEX_JAC_C 1
  int Driver_functionJacC_column(void* data, threadData_t *threadData);
  int Driver_initialAnalyticJacobianC(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* C */

#if defined(__cplusplus)
extern "C" {
#endif
  #define Driver_INDEX_JAC_D 0
  int Driver_functionJacD_column(void* data, threadData_t *threadData);
  int Driver_initialAnalyticJacobianD(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* D */


