model testPumpTwoCpipes
  extends Modelica.Icons.Example;
  inner ThermoPower.System system(initOpt = ThermoPower.Choices.Init.Options.fixedState) annotation(
    Placement(transformation(extent = {{80, 80}, {100, 100}})));
  ThermoPower.LHe.Pump0 pump1(CheckValve = true, Np0 = 1, V = 3.14e-4, allowFlowReversal = false, dp0 = 300, dp_max(displayUnit = "Pa") = 15000, h(fixed = true), hstart = 2767.6459, initOpt = ThermoPower.Choices.Init.Options.fixedState, n0 = 100, rho0(displayUnit = "kg/m3") = 130, w0 = 1E-3, w_max(displayUnit = "kg/s") = 0.001, w_single(fixed = true), wstart = 0) annotation(
    Placement(visible = true, transformation(origin = {-2, -43}, extent = {{13, -13}, {-13, 13}}, rotation = 0)));
  Modelica.Blocks.Sources.Exponentials exp1(offset = 0, outMax = 100, riseTime = 100, riseTimeConst = 0.1) annotation(
    Placement(visible = true, transformation(origin = {-82, -24}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  ThermoPower.LHe.Mixer mixer1(V = 2e-6, hstart = 2767.6459, pstart = 5e5)  annotation(
    Placement(visible = true, transformation(origin = {-44, 8}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));
  ThermoPower.LHe.Mixer mixer2(V = 2e-6, hstart = 2767.6459, pstart = 5e5)  annotation(
    Placement(visible = true, transformation(origin = {40, 8}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  ThermoPower.LHe.FMU.cpipe cpipe1( cpipe_input = "D:/Work/bin/test1.in",debugLogging = false, fmuContentsDir = "D:/Work/tmp/FMIToolkits/test-cppfmu/fmu10/release/cpipe", logLevel = 0, numberOfSteps = 40000, stopTime = 100.)  annotation(
    Placement(visible = true, transformation(origin = {0, 22}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  ThermoPower.LHe.FMU.cpipe cpipe2(cpipe_input = "D:/Work/bin/test2.in", debugLogging = false, fmuContentsDir = "D:/Work/tmp/FMIToolkits/test-cppfmu/fmu10/release/cpipe", logLevel = 0, numberOfSteps = 40000, stopTime = 100.)  annotation(
    Placement(visible = true, transformation(origin = {0, -8}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(cpipe2.infl, mixer1.in2) annotation(
    Line(points = {{-12, -8}, {-36, -8}, {-36, 2}}, color = {0, 0, 255}));
  connect(mixer1.in1, cpipe1.infl) annotation(
    Line(points = {{-36, 14}, {-36, 22}, {-12, 22}}, color = {0, 0, 255}));
  connect(mixer1.out, pump1.outfl) annotation(
    Line(points = {{-54, 8}, {-60, 8}, {-60, -34}, {-10, -34}}, color = {0, 0, 255}));
  connect(cpipe1.oufl, mixer2.in1) annotation(
    Line(points = {{12, 22}, {32, 22}, {32, 14}}, color = {0, 0, 255}));
  connect(cpipe2.oufl, mixer2.in2) annotation(
    Line(points = {{12, -8}, {32, -8}, {32, 2}}, color = {0, 0, 255}));
  connect(mixer2.out, pump1.infl) annotation(
    Line(points = {{50, 8}, {56, 8}, {56, -40}, {8, -40}}, color = {0, 0, 255}));
  connect(exp1.y, pump1.n) annotation(
    Line);
  annotation(
    Diagram(coordinateSystem(preserveAspectRatio = false, initialScale = 0.1), graphics = {Line(origin = {-38, -28}, points = {{-32, 4}, {32, 4}, {32, -4}})}),
    experiment(StopTime = 100, Tolerance = 1e-06, StartTime = 0, Interval = 0.0025),
    uses(ThermoPower(version = "3.1"), Modelica(version = "3.2.1")),
    __OpenModelica_simulationFlags(lv = "LOG_STATS", s = "impeuler"));
end testPumpTwoCpipes;
