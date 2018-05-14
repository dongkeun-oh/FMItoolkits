model Driver
  Modelica.Mechanics.Translational.Components.Mass mass1(L = 1, m = 0.5, s(start = -0.5))  annotation(
    Placement(visible = true, transformation(origin = {-16, 56}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Sine sin1(amplitude = 0.5, freqHz = 10, offset = 2.) annotation(
    Placement(visible = true, transformation(origin = {-70, 56}, extent = {{-6, -6}, {6, 6}}, rotation = 0)));
  FMITLM.FMITLM_Interface_3D.FMITLMInterface1D fmi annotation(
    Placement(visible = true, transformation(origin = {8, 56}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  parameter Real Kp = 1000.; 
  input Real f;
  input Real x_sig;
  Modelica.Mechanics.Translational.Sources.Force force1 annotation(
    Placement(visible = true, transformation(origin = {-40, 56}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(force1.flange, mass1.flange_a) annotation(
    Line(points = {{-30, 56}, {-26, 56}, {-26, 56}, {-26, 56}}, color = {0, 127, 0}));
  connect(mass1.flange_b, fmi.flange_a) annotation(
    Line(points = {{-6, 56}, {3, 56}}, color = {0, 127, 0}));
  fmi.f = f;
  force1.f = Kp*(sin1.y - x_sig);
  annotation(
    uses(Modelica(version = "3.2.2")));
end Driver;