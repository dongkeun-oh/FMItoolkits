model testPumpTwo1DFEM
  extends Modelica.Icons.Example;
  parameter Integer Nodes = 25;
  inner ThermoPower.System system(initOpt = ThermoPower.Choices.Init.Options.fixedState) annotation(
    Placement(transformation(extent = {{80, 80}, {100, 100}})));
  ThermoPower.LHe.Flow1DFEM flow1DFEM1(A = 3.14e-5, DynamicMomentum = false, FFtype = ThermoPower.Choices.Flow1D.FFtypes.Blasius, L = 10, N = Nodes, allowFlowReversal = false, dpnom(displayUnit = "bar") = 10, e = 0, hstartin = 2767.6459, hstartout = 2767.6459, initOpt = ThermoPower.Choices.Init.Options.fixedState, omega = 0.019859, pstart = 5e5, wnom = 0.0005) annotation(
    Placement(visible = true, transformation(origin = {-2, 14}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  ThermoPower.LHe.Flow1DFEM flow1DFEM2(A = 3.14e-5, DynamicMomentum = false, FFtype = ThermoPower.Choices.Flow1D.FFtypes.Blasius, L = 10, N = Nodes, allowFlowReversal = false, dpnom(displayUnit = "bar") = 10, e = 0, hstartin = 2767.6459, hstartout = 2767.6459, initOpt = ThermoPower.Choices.Init.Options.fixedState, omega = 0.019859, pstart = 5e5, wnom = 0.0005) annotation(
    Placement(visible = true, transformation(origin = {-2, -10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  ThermoPower.Thermal.HeatSource1DFEM heatSource(N = Nodes, L = 10, omega = 0.019859) annotation(
    Placement(visible = true, transformation(origin = {-2, 38}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  ThermoPower.LHe.Pump0 pump1(CheckValve = true, Np0 = 1, V = 3.14e-4, allowFlowReversal = false, dp0 = 300, dp_max(displayUnit = "Pa") = 15000, h(fixed = true), hstart = 2767.6459, initOpt = ThermoPower.Choices.Init.Options.fixedState, n0 = 100, rho0(displayUnit = "kg/m3") = 130, w0 = 1E-3, w_max(displayUnit = "kg/s") = 0.001, w_single(fixed = true), wstart = 0) annotation(
    Placement(visible = true, transformation(origin = {-2, -43}, extent = {{13, -13}, {-13, 13}}, rotation = 0)));
  Modelica.Blocks.Sources.Exponentials exp1(offset = 0, outMax = 100, riseTime = 100, riseTimeConst = 0.1) annotation(
    Placement(visible = true, transformation(origin = {-82, -24}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Constant const(k = 10) annotation(
    Placement(visible = true, transformation(origin = {-42, 52}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  ThermoPower.LHe.Mixer mixer1(V = 2e-6, hstart = 2767.6459, pstart = 5e5)  annotation(
    Placement(visible = true, transformation(origin = {-42, 2}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));
  ThermoPower.LHe.Mixer mixer2(V = 2e-6, hstart = 2767.6459, pstart = 5e5)  annotation(
    Placement(visible = true, transformation(origin = {38, 2}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(exp1.y, pump1.n) annotation(
    Line);
  connect(heatSource.power, const.y) annotation(
    Line(points = {{-2, 42}, {-2, 52}, {-30, 52}}, color = {0, 0, 127}));
  connect(heatSource.wall, flow1DFEM1.wall) annotation(
    Line(points = {{-2, 35}, {-2, 19}}, color = {255, 127, 0}));
  connect(mixer2.out, pump1.infl) annotation(
    Line(points = {{48, 2}, {56, 2}, {56, -40}, {8, -40}, {8, -40}}, color = {0, 0, 255}));
  connect(flow1DFEM2.outfl, mixer2.in2) annotation(
    Line(points = {{8, -10}, {30, -10}, {30, -4}, {30, -4}}, color = {0, 0, 255}));
  connect(flow1DFEM1.outfl, mixer2.in1) annotation(
    Line(points = {{8, 14}, {30, 14}, {30, 8}, {30, 8}}, color = {0, 0, 255}));
  connect(mixer1.out, pump1.outfl) annotation(
    Line(points = {{-52, 2}, {-60, 2}, {-60, -34}, {-10, -34}, {-10, -34}}, color = {0, 0, 255}));
  connect(mixer1.in2, flow1DFEM2.infl) annotation(
    Line(points = {{-34, -4}, {-34, -10}, {-12, -10}}, color = {0, 0, 255}));
  connect(mixer1.in1, flow1DFEM1.infl) annotation(
    Line(points = {{-34, 8}, {-34, 14}, {-12, 14}}, color = {0, 0, 255}));
  annotation(
    Diagram(coordinateSystem(preserveAspectRatio = false, initialScale = 0.1), graphics = {Line(origin = {-38, -28}, points = {{-32, 4}, {32, 4}, {32, -4}})}),
    experiment(StopTime = 100, Tolerance = 1e-06, StartTime = 0, Interval = 0.01),
    uses(ThermoPower(version = "3.1"), Modelica(version = "3.2.1")),
    __OpenModelica_simulationFlags(lv = "LOG_STATS", s = "ida"));
end testPumpTwo1DFEM;