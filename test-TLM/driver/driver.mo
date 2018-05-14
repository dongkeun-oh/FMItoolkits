model Driver
  Modelica.Blocks.Sources.Sine sin1(amplitude = 1000, freqHz = 10) annotation(
    Placement(visible = true, transformation(origin = {-86, 32}, extent = {{-6, -6}, {6, 6}}, rotation = 0)));
  Modelica.Mechanics.Translational.Components.Mass mass1(L = 1, m = 0.5, s(start = -0.5))  annotation(
    Placement(visible = true, transformation(origin = {-38, 32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  TLM.TLM_Interface_1D.TLMForce1D tLMForce1D1 annotation(
    Placement(visible = true, transformation(origin = {-10, 32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Mechanics.Translational.Sources.Force force1 annotation(
    Placement(visible = true, transformation(origin = {-62, 32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(force1.flange, mass1.flange_a) annotation(
    Line(points = {{-52, 32}, {-48, 32}, {-48, 32}, {-48, 32}}, color = {0, 127, 0}));
  connect(sin1.y, force1.f) annotation(
    Line(points = {{-80, 32}, {-74, 32}, {-74, 32}, {-74, 32}}, color = {0, 0, 127}));
  connect(mass1.flange_b, tLMForce1D1.flange_b) annotation(
    Line(points = {{-28, 32}, {-18, 32}}, color = {0, 127, 0}));
  annotation(
    uses(Modelica(version = "3.2.2")));
end Driver;