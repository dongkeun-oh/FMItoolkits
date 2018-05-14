#ifndef Load__H
#define Load__H
#include "meta/meta_modelica.h"
#include "util/modelica.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "simulation/simulation_runtime.h"
#ifdef __cplusplus
extern "C" {
#endif


DLLExport
modelica_real omc_TLM_TLM__Functions_TLMGetDelay(threadData_t *threadData, modelica_string _name);
DLLExport
modelica_metatype boxptr_TLM_TLM__Functions_TLMGetDelay(threadData_t *threadData, modelica_metatype _name);
static const MMC_DEFSTRUCTLIT(boxvar_lit_TLM_TLM__Functions_TLMGetDelay,2,0) {(void*) boxptr_TLM_TLM__Functions_TLMGetDelay,0}};
#define boxvar_TLM_TLM__Functions_TLMGetDelay MMC_REFSTRUCTLIT(boxvar_lit_TLM_TLM__Functions_TLMGetDelay)

/*
 * The function has annotation(Include=...>)
 * the external function definition should be present
 * in one of these files and have this prototype:
 * extern double get_tlm_delay(const char* (*_name*));
 */


DLLExport
modelica_real omc_TLM_TLM__Functions_TLMGetForce1D(threadData_t *threadData, modelica_complex _tlmPlugin, modelica_string _name, modelica_real _time_in, modelica_real _x, modelica_real _v);
DLLExport
modelica_metatype boxptr_TLM_TLM__Functions_TLMGetForce1D(threadData_t *threadData, modelica_metatype _tlmPlugin, modelica_metatype _name, modelica_metatype _time_in, modelica_metatype _x, modelica_metatype _v);
static const MMC_DEFSTRUCTLIT(boxvar_lit_TLM_TLM__Functions_TLMGetForce1D,2,0) {(void*) boxptr_TLM_TLM__Functions_TLMGetForce1D,0}};
#define boxvar_TLM_TLM__Functions_TLMGetForce1D MMC_REFSTRUCTLIT(boxvar_lit_TLM_TLM__Functions_TLMGetForce1D)

/*
 * The function has annotation(Include=...>)
 * the external function definition should be present
 * in one of these files and have this prototype:
 * extern void calc_tlm_force_1d(void * (*_tlmPlugin*), const char* (*_name*), double (*_time_in*), double (*_x*), double (*_v*), double* (*_f*));
 */


DLLExport
void omc_TLM_TLM__Functions_TLMSetDebugMode(threadData_t *threadData, modelica_boolean _DebugFlg);
DLLExport
void boxptr_TLM_TLM__Functions_TLMSetDebugMode(threadData_t *threadData, modelica_metatype _DebugFlg);
static const MMC_DEFSTRUCTLIT(boxvar_lit_TLM_TLM__Functions_TLMSetDebugMode,2,0) {(void*) boxptr_TLM_TLM__Functions_TLMSetDebugMode,0}};
#define boxvar_TLM_TLM__Functions_TLMSetDebugMode MMC_REFSTRUCTLIT(boxvar_lit_TLM_TLM__Functions_TLMSetDebugMode)

/*
 * The function has annotation(Include=...>)
 * the external function definition should be present
 * in one of these files and have this prototype:
 * extern void set_debug_mode(int (*_DebugFlg*));
 */


DLLExport
modelica_complex omc_TLM_TLM__Functions_TLMPlugin_constructor(threadData_t *threadData);
DLLExport
modelica_metatype boxptr_TLM_TLM__Functions_TLMPlugin_constructor(threadData_t *threadData);
static const MMC_DEFSTRUCTLIT(boxvar_lit_TLM_TLM__Functions_TLMPlugin_constructor,2,0) {(void*) boxptr_TLM_TLM__Functions_TLMPlugin_constructor,0}};
#define boxvar_TLM_TLM__Functions_TLMPlugin_constructor MMC_REFSTRUCTLIT(boxvar_lit_TLM_TLM__Functions_TLMPlugin_constructor)

/*
 * The function has annotation(Include=...>)
 * the external function definition should be present
 * in one of these files and have this prototype:
 * extern void * initialize_TLM();
 */


DLLExport
void omc_TLM_TLM__Functions_TLMPlugin_destructor(threadData_t *threadData, modelica_complex _tlmPlugin);
DLLExport
void boxptr_TLM_TLM__Functions_TLMPlugin_destructor(threadData_t *threadData, modelica_metatype _tlmPlugin);
static const MMC_DEFSTRUCTLIT(boxvar_lit_TLM_TLM__Functions_TLMPlugin_destructor,2,0) {(void*) boxptr_TLM_TLM__Functions_TLMPlugin_destructor,0}};
#define boxvar_TLM_TLM__Functions_TLMPlugin_destructor MMC_REFSTRUCTLIT(boxvar_lit_TLM_TLM__Functions_TLMPlugin_destructor)

/*
 * The function has annotation(Include=...>)
 * the external function definition should be present
 * in one of these files and have this prototype:
 * extern void deinitialize_TLM(void * (*_tlmPlugin*));
 */
#include "Load_model.h"


#ifdef __cplusplus
}
#endif
#endif

