model testPumpSingleCpipe
  inner ThermoPower.System system(initOpt = ThermoPower.Choices.Init.Options.fixedState) annotation(
    Placement(transformation(extent = {{80, 80}, {100, 100}})));
  ThermoPower.LHe.FMU.cpipe cpipe1(cpipe_input = "D:/Work/FMItoolkits/test-cppfmu/src/fmu10/cpipe/_cpipe_core/test1.in", debugLogging = false, logLevel = 0, numberOfSteps = 20000, stopTime = 50) annotation(
    Placement(visible = true, transformation(origin = {-1, 32}, extent = {{-11, -11}, {11, 11}}, rotation = 0)));
  ThermoPower.LHe.Pump0 pump1(CheckValve = true, Np0 = 1, V = 3.14e-4, allowFlowReversal = false, dp0 = 300, dp_max(displayUnit = "Pa") = 15000, hstart = 2767.6459, initOpt = ThermoPower.Choices.Init.Options.fixedState, n0 = 100, rho0(displayUnit = "kg/m3") = 130, w0 = 1e-3, w_max(displayUnit = "kg/s") = 0.001, wstart = 0.001) annotation(
    Placement(visible = true, transformation(origin = {-2, -27}, extent = {{13, -13}, {-13, 13}}, rotation = 0)));
  Modelica.Blocks.Sources.Exponentials exp1(offset = 0, outMax = 100, riseTime = 100, riseTimeConst = 0.1) annotation(
    Placement(visible = true, transformation(origin = {-84, -4}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  ThermoPower.LHe.Header mixer1(V = 2e-6, allowFlowReversal = true, h(start = 2767.6459), hstart = 2767.6459, p(start = 5e5), pstart = 5e5) annotation(
    Placement(visible = true, transformation(origin = {-38, 32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  ThermoPower.LHe.Header mixer2(V = 2e-6, allowFlowReversal = true, h(start = 2767.6459), hstart = 2767.6459, p(start = 5e5), pstart = 5e5) annotation(
    Placement(visible = true, transformation(origin = {36, 32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(cpipe1.oufl, mixer2.inlet) annotation(
    Line(points = {{12, 32}, {26, 32}}, color = {0, 0, 255}));
  connect(mixer1.outlet, cpipe1.infl) annotation(
    Line(points = {{-28, 32}, {-14, 32}}, color = {0, 0, 255}));
  connect(pump1.outfl, mixer1.inlet) annotation(
    Line(points = {{-10, -18}, {-60, -18}, {-60, 32}, {-48, 32}, {-48, 32}}, color = {0, 0, 255}));
  connect(mixer2.outlet, pump1.infl) annotation(
    Line(points = {{46, 32}, {54, 32}, {54, -24}, {8, -24}, {8, -24}}, color = {0, 0, 255}));
  connect(exp1.y, pump1.n) annotation(
    Line);
  annotation(
    uses(ThermoPower(version = "3.1"), Modelica(version = "3.2.2")),
    experiment(StopTime = 50, Interval = 0.0025, StartTime = 0, Tolerance = 1e-06),
    __OpenModelica_simulationFlags(lv = "LOG_STATS", s = "impeuler"),
    Diagram(graphics = {Line(origin = {-38.2821, -9.28205}, points = {{-33, 6}, {33, 6}, {33, -6}})}));
end testPumpSingleCpipe;
