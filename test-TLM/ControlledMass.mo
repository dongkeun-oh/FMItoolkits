model ControlledMass
  Modelica.Mechanics.Translational.Components.Mass mass1(L = 1, m = 0.5, s(fixed = true, start = 1.), v(fixed = true, start = .0)) annotation(
    Placement(visible = true, transformation(origin = {-36, 32}, extent = {{-8, -8}, {8, 8}}, rotation = 0)));
  Modelica.Mechanics.Translational.Components.Mass parasitic_mass(L = 0, m = 0.05, s(fixed = true, start = 1.5), v(fixed = true, start = 0)) annotation(
    Placement(visible = true, transformation(origin = {-6, 32}, extent = {{-8, -8}, {8, 8}}, rotation = 0)));
  Modelica.Mechanics.Translational.Components.Spring TLM_spring(c = 5e6) annotation(
    Placement(visible = true, transformation(origin = {18, 32}, extent = {{-8, -8}, {8, 8}}, rotation = 0)));
  Modelica.Mechanics.Translational.Components.Mass mass2(L = 1, m = 0.5, s(fixed = true, start = 2.0), v(fixed = true, start = 0)) annotation(
    Placement(visible = true, transformation(origin = {50, 32}, extent = {{-8, -8}, {8, 8}}, rotation = 0)));
  Modelica.Mechanics.Translational.Components.Damper damper1(d = 100) annotation(
    Placement(visible = true, transformation(origin = {72, 32}, extent = {{-8, -8}, {8, 8}}, rotation = 0)));
  Modelica.Mechanics.Translational.Components.Fixed fixed1(s0 = 3) annotation(
    Placement(visible = true, transformation(origin = {89, 25}, extent = {{-7, -7}, {7, 7}}, rotation = 0)));
  Modelica.Mechanics.Translational.Sources.Force force1 annotation(
    Placement(visible = true, transformation(origin = {-58, 32}, extent = {{-6, -6}, {6, 6}}, rotation = 0)));
  Modelica.Blocks.Sources.Sine sin1(amplitude = .5, freqHz = 10, offset = 2.5) annotation(
    Placement(visible = true, transformation(origin = {-82, 32}, extent = {{-6, -6}, {6, 6}}, rotation = 0)));
  parameter Real Kp = 1000.;
equation
  force1.f = Kp * (sin1.y - mass2.s);
  connect(parasitic_mass.flange_b, TLM_spring.flange_a) annotation(
    Line(points = {{2, 32}, {10, 32}}, color = {0, 127, 0}));
  connect(mass1.flange_b, parasitic_mass.flange_a) annotation(
    Line(points = {{-28, 32}, {-14, 32}}, color = {0, 127, 0}));
  connect(TLM_spring.flange_b, mass2.flange_a) annotation(
    Line(points = {{26, 32}, {42, 32}}, color = {0, 127, 0}));
  connect(mass2.flange_b, damper1.flange_a) annotation(
    Line(points = {{58, 32}, {64, 32}}, color = {0, 127, 0}));
  connect(force1.flange, mass1.flange_a) annotation(
    Line(points = {{-50, 32}, {-44, 32}}, color = {0, 127, 0}));
  connect(damper1.flange_b, fixed1.flange) annotation(
    Line(points = {{80, 32}, {89, 32}, {89, 25}}, color = {0, 127, 0}));
  annotation(
    uses(Modelica(version = "3.2.2")),
    Documentation);
end ControlledMass;