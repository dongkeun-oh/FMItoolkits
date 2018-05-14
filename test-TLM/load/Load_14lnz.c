/* Linearization */
#include "Load_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

const char *Load_linear_model_frame()
{
  return "model linear_Load\n  parameter Integer n = 2; // states\n  parameter Integer k = 0; // top-level inputs\n  parameter Integer l = 0; // top-level outputs\n"
  "  parameter Real x0[2] = {%s};\n"
  "  parameter Real u0[0] = {%s};\n"
  "  parameter Real A[2,2] = [%s];\n"
  "  parameter Real B[2,0] = zeros(2,0);%s\n"
  "  parameter Real C[0,2] = zeros(0,2);%s\n"
  "  parameter Real D[0,0] = zeros(0,0);%s\n"
  "  Real x[2](start=x0);\n"
  "  input Real u[0];\n"
  "  output Real y[0];\n"
  "\n  Real 'x_damper1.s_rel' = x[1];\nReal 'x_damper1.v_rel' = x[2];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\nend linear_Load;\n";
}
const char *Load_linear_model_datarecovery_frame()
{
  return "model linear_Load\n  parameter Integer n = 2; // states\n  parameter Integer k = 0; // top-level inputs\n  parameter Integer l = 0; // top-level outputs\n  parameter Integer nz = 15; // data recovery variables\n"
  "  parameter Real x0[2] = {%s};\n"
  "  parameter Real u0[0] = {%s};\n"
  "  parameter Real z0[15] = {%s};\n"
  "  parameter Real A[2,2] = [%s];\n"
  "  parameter Real B[2,0] = zeros(2,0);%s\n"
  "  parameter Real C[0,2] = zeros(0,2);%s\n"
  "  parameter Real D[0,0] = zeros(0,0);%s\n"
  "  parameter Real Cz[15,2] = [%s];\n"
  "  parameter Real Dz[15,0] = zeros(15,0);%s\n"
  "  Real x[2](start=x0);\n"
  "  input Real u[0];\n"
  "  output Real y[0];\n"
  "  output Real z[15];\n"
  "\nReal 'x_damper1.s_rel' = x[1];\nReal 'x_damper1.v_rel' = x[2];\nReal 'z_der(der(damper1.flange_a.s))' = z[1];\nReal 'z_der(damper1.flange_a.s)' = z[2];\nReal 'z_der(mass2.s)' = z[3];\nReal 'z_der(mass2.v)' = z[4];\nReal 'z_der(tLMForce1D1.flange_b.s)' = z[5];\nReal 'z_damper1.f' = z[6];\nReal 'z_damper1.flange_a.s' = z[7];\nReal 'z_damper1.lossPower' = z[8];\nReal 'z_mass2.a' = z[9];\nReal 'z_mass2.s' = z[10];\nReal 'z_mass2.v' = z[11];\nReal 'z_tLMForce1D1.f' = z[12];\nReal 'z_tLMForce1D1.flange_b.s' = z[13];\nReal 'z_tLMForce1D1.tlmDelay' = z[14];\nReal 'z_tLMForce1D1.v' = z[15];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\n  z = Cz * x + Dz * u;\nend linear_Load;\n";
}
#if defined(__cplusplus)
}
#endif

