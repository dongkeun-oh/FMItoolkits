/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "Driver_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

int Driver_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating min-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* max ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating max-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* nominal **************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating nominal-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* start ****************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating primary start-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  TRACE_POP
  return 0;
}


/*
 equation index: 25
 type: SIMPLE_ASSIGN
 tLMForce1D1._tlmPlugin = TLM.TLM_Functions.TLMPlugin.constructor()
 */
void Driver_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  data->simulationInfo->extObjs[0] = omc_TLM_TLM__Functions_TLMPlugin_constructor(threadData);
  TRACE_POP
}

/*
 equation index: 26
 type: SIMPLE_ASSIGN
 force1._useSupport = false
 */
void Driver_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  data->simulationInfo->booleanParameter[0] = 0;
  TRACE_POP
}

/*
 equation index: 27
 type: SIMPLE_ASSIGN
 force1._s_support = 0.0
 */
void Driver_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  data->localData[0]->realVars[7] /* force1._s_support variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 28
 type: ALGORITHM
 
   assert(mass1.stateSelect >= StateSelect.never and mass1.stateSelect <= StateSelect.always, "Variable violating min/max constraint: StateSelect.never <= mass1.stateSelect <= StateSelect.always, has value: " + String(mass1.stateSelect, "d"));
 */
void Driver_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  modelica_boolean tmp1;
  modelica_boolean tmp2;
  static const MMC_DEFSTRINGLIT(tmp3,112,"Variable violating min/max constraint: StateSelect.never <= mass1.stateSelect <= StateSelect.always, has value: ");
  modelica_string tmp4;
  static int tmp5 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp5)
  {
    tmp1 = GreaterEq((modelica_integer)data->simulationInfo->integerParameter[0],1);
    tmp2 = LessEq((modelica_integer)data->simulationInfo->integerParameter[0],5);
    if(!(tmp1 && tmp2))
    {
      tmp4 = modelica_integer_to_modelica_string_format((modelica_integer)data->simulationInfo->integerParameter[0], (modelica_string) mmc_strings_len1[100]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp3),tmp4);
      {
        FILE_INFO info = {"/opt/openmodelica/lib/omlibrary/Modelica 3.2.2/Mechanics/Translational.mo",1750,7,1751,80,1};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmass1.stateSelect >= StateSelect.never and mass1.stateSelect <= StateSelect.always", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp5 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 29
 type: ALGORITHM
 
   assert(mass1.m >= 0.0, "Variable violating min constraint: 0.0 <= mass1.m, has value: " + String(mass1.m, "g"));
 */
void Driver_eqFunction_29(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,29};
  modelica_boolean tmp6;
  static const MMC_DEFSTRINGLIT(tmp7,62,"Variable violating min constraint: 0.0 <= mass1.m, has value: ");
  modelica_string tmp8;
  static int tmp9 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp9)
  {
    tmp6 = GreaterEq(data->simulationInfo->realParameter[1],0.0);
    if(!tmp6)
    {
      tmp8 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[1], (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp7),tmp8);
      {
        FILE_INFO info = {"/opt/openmodelica/lib/omlibrary/Modelica 3.2.2/Mechanics/Translational.mo",1749,7,1749,69,1};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmass1.m >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp9 = 1;
    }
  }
  TRACE_POP
}
int Driver_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  Driver_eqFunction_25(data, threadData);

  Driver_eqFunction_26(data, threadData);

  Driver_eqFunction_27(data, threadData);

  Driver_eqFunction_28(data, threadData);

  Driver_eqFunction_29(data, threadData);
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

