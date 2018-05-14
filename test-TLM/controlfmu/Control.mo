model Control
  Modelica.Blocks.Sources.Sine sin1(amplitude = 0.5, freqHz = 10, offset = 2.) annotation(
    Placement(visible = true, transformation(origin = {-52, 32}, extent = {{-6, -6}, {6, 6}}, rotation = 0)));
  output Real x_ref;
equation
  x_ref = sin1.y; 
end Control;