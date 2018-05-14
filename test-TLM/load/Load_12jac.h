/* Jacobians */
static const REAL_ATTRIBUTE dummyREAL_ATTRIBUTE = omc_dummyRealAttribute;
/* Jacobian Variables */
#if defined(__cplusplus)
extern "C" {
#endif
  #define Load_INDEX_JAC_A 3
  int Load_functionJacA_column(void* data, threadData_t *threadData);
  int Load_initialAnalyticJacobianA(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* A */
#define $Pdamper1_s_relSeedA data->simulationInfo->analyticJacobians[3].seedVars[0]
#define $Pdamper1_v_relSeedA data->simulationInfo->analyticJacobians[3].seedVars[1]

#if defined(__cplusplus)
extern "C" {
#endif
  #define Load_INDEX_JAC_B 2
  int Load_functionJacB_column(void* data, threadData_t *threadData);
  int Load_initialAnalyticJacobianB(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* B */

#if defined(__cplusplus)
extern "C" {
#endif
  #define Load_INDEX_JAC_C 1
  int Load_functionJacC_column(void* data, threadData_t *threadData);
  int Load_initialAnalyticJacobianC(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* C */

#if defined(__cplusplus)
extern "C" {
#endif
  #define Load_INDEX_JAC_D 0
  int Load_functionJacD_column(void* data, threadData_t *threadData);
  int Load_initialAnalyticJacobianD(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* D */


