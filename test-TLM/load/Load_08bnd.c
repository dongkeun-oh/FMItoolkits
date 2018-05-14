/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "Load_model.h"
#if defined(__cplusplus)
extern "C" {
#endif


/*
 equation index: 38
 type: SIMPLE_ASSIGN
 damper1._s_rel = damper1.s_nominal
 */
void Load_eqFunction_38(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,38};
  data->localData[0]->realVars[0] /* damper1._s_rel STATE(1,damper1.v_rel) */ = data->simulationInfo->realParameter[1];
  TRACE_POP
}
int Load_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating min-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* max ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating max-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* nominal **************************************************** */
  Load_eqFunction_38(data, threadData);
  
  infoStreamPrint(LOG_INIT, 1, "updating nominal-values");
  data->modelData->realVarsData[0].attribute /* damper1._s_rel */.nominal = data->localData[0]->realVars[0] /* damper1._s_rel STATE(1,damper1.v_rel) */;
    infoStreamPrint(LOG_INIT, 0, "%s(nominal=%g)", data->modelData->realVarsData[0].info /* damper1._s_rel */.name, (modelica_real) data->modelData->realVarsData[0].attribute /* damper1._s_rel */.nominal);
  data->localData[0]->realVars[0] /* damper1._s_rel STATE(1,damper1.v_rel) */ = data->modelData->realVarsData[0].attribute /* damper1._s_rel */.start;
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* start ****************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating primary start-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  TRACE_POP
  return 0;
}


/*
 equation index: 39
 type: SIMPLE_ASSIGN
 tLMForce1D1._tlmPlugin = TLM.TLM_Functions.TLMPlugin.constructor()
 */
void Load_eqFunction_39(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,39};
  data->simulationInfo->extObjs[0] = omc_TLM_TLM__Functions_TLMPlugin_constructor(threadData);
  TRACE_POP
}

/*
 equation index: 40
 type: SIMPLE_ASSIGN
 damper1._useHeatPort = false
 */
void Load_eqFunction_40(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,40};
  data->simulationInfo->booleanParameter[0] = 0;
  TRACE_POP
}

/*
 equation index: 41
 type: SIMPLE_ASSIGN
 damper1._stateSelect = StateSelect.prefer
 */
void Load_eqFunction_41(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,41};
  data->simulationInfo->integerParameter[0] = 4;
  TRACE_POP
}

/*
 equation index: 42
 type: ALGORITHM
 
   assert(damper1.d >= 0.0, "Variable violating min constraint: 0.0 <= damper1.d, has value: " + String(damper1.d, "g"));
 */
void Load_eqFunction_42(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,42};
  modelica_boolean tmp3;
  static const MMC_DEFSTRINGLIT(tmp4,64,"Variable violating min constraint: 0.0 <= damper1.d, has value: ");
  modelica_string tmp5;
  static int tmp6 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp6)
  {
    tmp3 = GreaterEq(data->simulationInfo->realParameter[0],0.0);
    if(!tmp3)
    {
      tmp5 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[0], (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp4),tmp5);
      {
        FILE_INFO info = {"/opt/openmodelica/lib/omlibrary/Modelica 3.2.2/Mechanics/Translational.mo",1938,7,1939,27,1};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\ndamper1.d >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp6 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 43
 type: ALGORITHM
 
   assert(damper1.s_nominal >= 0.0, "Variable violating min constraint: 0.0 <= damper1.s_nominal, has value: " + String(damper1.s_nominal, "g"));
 */
void Load_eqFunction_43(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,43};
  modelica_boolean tmp7;
  static const MMC_DEFSTRINGLIT(tmp8,72,"Variable violating min constraint: 0.0 <= damper1.s_nominal, has value: ");
  modelica_string tmp9;
  static int tmp10 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp10)
  {
    tmp7 = GreaterEq(data->simulationInfo->realParameter[1],0.0);
    if(!tmp7)
    {
      tmp9 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[1], (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp8),tmp9);
      {
        FILE_INFO info = {"/opt/openmodelica/lib/omlibrary/Modelica 3.2.2/Mechanics/Translational.mo",4683,7,4685,44,1};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\ndamper1.s_nominal >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp10 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 44
 type: ALGORITHM
 
   assert(damper1.stateSelect >= StateSelect.never and damper1.stateSelect <= StateSelect.always, "Variable violating min/max constraint: StateSelect.never <= damper1.stateSelect <= StateSelect.always, has value: " + String(damper1.stateSelect, "d"));
 */
void Load_eqFunction_44(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,44};
  modelica_boolean tmp11;
  modelica_boolean tmp12;
  static const MMC_DEFSTRINGLIT(tmp13,114,"Variable violating min/max constraint: StateSelect.never <= damper1.stateSelect <= StateSelect.always, has value: ");
  modelica_string tmp14;
  static int tmp15 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp15)
  {
    tmp11 = GreaterEq((modelica_integer)data->simulationInfo->integerParameter[0],1);
    tmp12 = LessEq((modelica_integer)data->simulationInfo->integerParameter[0],5);
    if(!(tmp11 && tmp12))
    {
      tmp14 = modelica_integer_to_modelica_string_format((modelica_integer)data->simulationInfo->integerParameter[0], (modelica_string) mmc_strings_len1[100]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp13),tmp14);
      {
        FILE_INFO info = {"/opt/openmodelica/lib/omlibrary/Modelica 3.2.2/Mechanics/Translational.mo",4680,7,4682,61,1};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\ndamper1.stateSelect >= StateSelect.never and damper1.stateSelect <= StateSelect.always", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp15 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 45
 type: ALGORITHM
 
   assert(mass2.stateSelect >= StateSelect.never and mass2.stateSelect <= StateSelect.always, "Variable violating min/max constraint: StateSelect.never <= mass2.stateSelect <= StateSelect.always, has value: " + String(mass2.stateSelect, "d"));
 */
void Load_eqFunction_45(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,45};
  modelica_boolean tmp16;
  modelica_boolean tmp17;
  static const MMC_DEFSTRINGLIT(tmp18,112,"Variable violating min/max constraint: StateSelect.never <= mass2.stateSelect <= StateSelect.always, has value: ");
  modelica_string tmp19;
  static int tmp20 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp20)
  {
    tmp16 = GreaterEq((modelica_integer)data->simulationInfo->integerParameter[1],1);
    tmp17 = LessEq((modelica_integer)data->simulationInfo->integerParameter[1],5);
    if(!(tmp16 && tmp17))
    {
      tmp19 = modelica_integer_to_modelica_string_format((modelica_integer)data->simulationInfo->integerParameter[1], (modelica_string) mmc_strings_len1[100]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp18),tmp19);
      {
        FILE_INFO info = {"/opt/openmodelica/lib/omlibrary/Modelica 3.2.2/Mechanics/Translational.mo",1750,7,1751,80,1};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmass2.stateSelect >= StateSelect.never and mass2.stateSelect <= StateSelect.always", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp20 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 46
 type: ALGORITHM
 
   assert(mass2.m >= 0.0, "Variable violating min constraint: 0.0 <= mass2.m, has value: " + String(mass2.m, "g"));
 */
void Load_eqFunction_46(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,46};
  modelica_boolean tmp21;
  static const MMC_DEFSTRINGLIT(tmp22,62,"Variable violating min constraint: 0.0 <= mass2.m, has value: ");
  modelica_string tmp23;
  static int tmp24 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp24)
  {
    tmp21 = GreaterEq(data->simulationInfo->realParameter[4],0.0);
    if(!tmp21)
    {
      tmp23 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[4], (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp22),tmp23);
      {
        FILE_INFO info = {"/opt/openmodelica/lib/omlibrary/Modelica 3.2.2/Mechanics/Translational.mo",1749,7,1749,69,1};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmass2.m >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp24 = 1;
    }
  }
  TRACE_POP
}
int Load_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  Load_eqFunction_39(data, threadData);

  Load_eqFunction_40(data, threadData);

  Load_eqFunction_41(data, threadData);

  Load_eqFunction_42(data, threadData);

  Load_eqFunction_43(data, threadData);

  Load_eqFunction_44(data, threadData);

  Load_eqFunction_45(data, threadData);

  Load_eqFunction_46(data, threadData);
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

