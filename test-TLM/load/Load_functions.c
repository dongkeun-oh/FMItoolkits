#include "Load_functions.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "Load_includes.h"


modelica_real omc_TLM_TLM__Functions_TLMGetDelay(threadData_t *threadData, modelica_string _name)
{
  double _TLMdelay_ext;
  modelica_real _TLMdelay;
  _TLMdelay_ext = get_tlm_delay(MMC_STRINGDATA(_name));
  _TLMdelay = (modelica_real)_TLMdelay_ext;
  return _TLMdelay;
}
modelica_metatype boxptr_TLM_TLM__Functions_TLMGetDelay(threadData_t *threadData, modelica_metatype _name)
{
  modelica_real _TLMdelay;
  modelica_metatype out_TLMdelay;
  _TLMdelay = omc_TLM_TLM__Functions_TLMGetDelay(threadData, _name);
  out_TLMdelay = mmc_mk_rcon(_TLMdelay);
  return out_TLMdelay;
}

modelica_real omc_TLM_TLM__Functions_TLMGetForce1D(threadData_t *threadData, modelica_complex _tlmPlugin, modelica_string _name, modelica_real _time_in, modelica_real _x, modelica_real _v)
{
  void * _tlmPlugin_ext;
  double _time_in_ext;
  double _x_ext;
  double _v_ext;
  double _f_ext;
  modelica_real _f;
  _tlmPlugin_ext = (void *)_tlmPlugin;
  _time_in_ext = (double)_time_in;
  _x_ext = (double)_x;
  _v_ext = (double)_v;
  calc_tlm_force_1d(_tlmPlugin_ext, MMC_STRINGDATA(_name), _time_in_ext, _x_ext, _v_ext, &_f_ext);
  _f = (modelica_real)_f_ext;
  return _f;
}
modelica_metatype boxptr_TLM_TLM__Functions_TLMGetForce1D(threadData_t *threadData, modelica_metatype _tlmPlugin, modelica_metatype _name, modelica_metatype _time_in, modelica_metatype _x, modelica_metatype _v)
{
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real _f;
  modelica_metatype out_f;
  tmp1 = mmc_unbox_real(_time_in);
  tmp2 = mmc_unbox_real(_x);
  tmp3 = mmc_unbox_real(_v);
  _f = omc_TLM_TLM__Functions_TLMGetForce1D(threadData, _tlmPlugin, _name, tmp1, tmp2, tmp3);
  out_f = mmc_mk_rcon(_f);
  return out_f;
}

void omc_TLM_TLM__Functions_TLMSetDebugMode(threadData_t *threadData, modelica_boolean _DebugFlg)
{
  int _DebugFlg_ext;
  _DebugFlg_ext = (int)_DebugFlg;
  set_debug_mode(_DebugFlg_ext);
  return;
}
void boxptr_TLM_TLM__Functions_TLMSetDebugMode(threadData_t *threadData, modelica_metatype _DebugFlg)
{
  modelica_integer tmp1;
  tmp1 = mmc_unbox_integer(_DebugFlg);
  omc_TLM_TLM__Functions_TLMSetDebugMode(threadData, tmp1);
  return;
}

modelica_complex omc_TLM_TLM__Functions_TLMPlugin_constructor(threadData_t *threadData)
{
  void * _tlmPlugin_ext;
  modelica_complex _tlmPlugin;
  _tlmPlugin_ext = initialize_TLM();
  _tlmPlugin = (modelica_complex)_tlmPlugin_ext;
  return _tlmPlugin;
}
modelica_metatype boxptr_TLM_TLM__Functions_TLMPlugin_constructor(threadData_t *threadData)
{
  modelica_complex _tlmPlugin;
  _tlmPlugin = omc_TLM_TLM__Functions_TLMPlugin_constructor(threadData);
  /* skip box _tlmPlugin; ExternalObject TLM.TLM_Functions.TLMPlugin */
  return _tlmPlugin;
}

void omc_TLM_TLM__Functions_TLMPlugin_destructor(threadData_t *threadData, modelica_complex _tlmPlugin)
{
  void * _tlmPlugin_ext;
  _tlmPlugin_ext = (void *)_tlmPlugin;
  deinitialize_TLM(_tlmPlugin_ext);
  return;
}
void boxptr_TLM_TLM__Functions_TLMPlugin_destructor(threadData_t *threadData, modelica_metatype _tlmPlugin)
{
  omc_TLM_TLM__Functions_TLMPlugin_destructor(threadData, _tlmPlugin);
  return;
}

#ifdef __cplusplus
}
#endif
