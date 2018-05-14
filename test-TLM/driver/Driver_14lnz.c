/* Linearization */
#include "Driver_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

const char *Driver_linear_model_frame()
{
  return "model linear_Driver\n  parameter Integer n = 2; // states\n  parameter Integer k = 0; // top-level inputs\n  parameter Integer l = 0; // top-level outputs\n"
  "  parameter Real x0[2] = {%s};\n"
  "  parameter Real u0[0] = {%s};\n"
  "  parameter Real A[2,2] = [%s];\n"
  "  parameter Real B[2,0] = zeros(2,0);%s\n"
  "  parameter Real C[0,2] = zeros(0,2);%s\n"
  "  parameter Real D[0,0] = zeros(0,0);%s\n"
  "  Real x[2](start=x0);\n"
  "  input Real u[0];\n"
  "  output Real y[0];\n"
  "\n  Real 'x_mass1.s' = x[1];\nReal 'x_mass1.v' = x[2];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\nend linear_Driver;\n";
}
const char *Driver_linear_model_datarecovery_frame()
{
  return "model linear_Driver\n  parameter Integer n = 2; // states\n  parameter Integer k = 0; // top-level inputs\n  parameter Integer l = 0; // top-level outputs\n  parameter Integer nz = 9; // data recovery variables\n"
  "  parameter Real x0[2] = {%s};\n"
  "  parameter Real u0[0] = {%s};\n"
  "  parameter Real z0[9] = {%s};\n"
  "  parameter Real A[2,2] = [%s];\n"
  "  parameter Real B[2,0] = zeros(2,0);%s\n"
  "  parameter Real C[0,2] = zeros(0,2);%s\n"
  "  parameter Real D[0,0] = zeros(0,0);%s\n"
  "  parameter Real Cz[9,2] = [%s];\n"
  "  parameter Real Dz[9,0] = zeros(9,0);%s\n"
  "  Real x[2](start=x0);\n"
  "  input Real u[0];\n"
  "  output Real y[0];\n"
  "  output Real z[9];\n"
  "\nReal 'x_mass1.s' = x[1];\nReal 'x_mass1.v' = x[2];\nReal 'z_der(tLMForce1D1.flange_b.s)' = z[1];\nReal 'z_force1.f' = z[2];\nReal 'z_force1.s' = z[3];\nReal 'z_force1.s_support' = z[4];\nReal 'z_mass1.a' = z[5];\nReal 'z_tLMForce1D1.f' = z[6];\nReal 'z_tLMForce1D1.flange_b.s' = z[7];\nReal 'z_tLMForce1D1.tlmDelay' = z[8];\nReal 'z_tLMForce1D1.v' = z[9];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\n  z = Cz * x + Dz * u;\nend linear_Driver;\n";
}
#if defined(__cplusplus)
}
#endif

