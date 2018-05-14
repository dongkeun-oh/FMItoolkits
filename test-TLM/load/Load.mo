model Load
  Modelica.Mechanics.Translational.Components.Mass mass2(L = 1, m = 0.5, s(fixed = true, start = 2.), v(fixed = true, start = 0)) annotation(
    Placement(visible = true, transformation(origin = {46, 32}, extent = {{-8, -8}, {8, 8}}, rotation = 0)));
  Modelica.Mechanics.Translational.Components.Damper damper1(d = 100) annotation(
    Placement(visible = true, transformation(origin = {72, 32}, extent = {{-8, -8}, {8, 8}}, rotation = 0)));
  Modelica.Mechanics.Translational.Components.Fixed fixed1(s0 = 3) annotation(
    Placement(visible = true, transformation(origin = {89, 25}, extent = {{-7, -7}, {7, 7}}, rotation = 0)));
  TLM.TLM_Interface_1D.TLMForce1D tLMForce1D1 annotation(
    Placement(visible = true, transformation(origin = {20, 32}, extent = {{-10, -10}, {10, 10}}, rotation = 180)));
equation
  connect(tLMForce1D1.flange_b, mass2.flange_a) annotation(
    Line(points = {{28, 32}, {38, 32}}, color = {0, 127, 0}));
  connect(mass2.flange_b, damper1.flange_a) annotation(
    Line(points = {{54, 32}, {64, 32}}, color = {0, 127, 0}));
  connect(damper1.flange_b, fixed1.flange) annotation(
    Line(points = {{80, 32}, {89, 32}, {89, 25}}, color = {0, 127, 0}));
  annotation(
    uses(Modelica(version = "3.2.2")));
end Load;