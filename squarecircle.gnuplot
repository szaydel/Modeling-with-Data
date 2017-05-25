#Just as you can use sin(x) to For a parametric plot
set parametric
set size square
set size 0.9
unset key
unset xtics
unset ytics
set xrange [-1:1]
set yrange [-1:1]
set label "{\\small $r$}" at 0.45, 0.1
set label "$A(\\circ) = \\pi r^2 = \\pi$\\\\$A(\\Box) = (2r)^2 = 4$" at -0.8, 0.49
set term latex
set out "squaredcircle.tex"
plot [0:2*pi] sin(t),cos(t) with lines,  t, 0
