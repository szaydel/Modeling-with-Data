# This produces the three graphs of the U.S. national debt for the book.
# As you can see, they produce LaTeX output directly; to display to screen
# just comment out the set term and set out lines, and uncomment the
# pauses.


set term latex 
set size 0.55, 0.55
set out 'debt.shortscale.tex' 
set key off
set ylabel "\\rotatebox{90}{National debt}"
set format x "\\rotatebox{65}{%g}"
plot 'data-debt' index 0 using 1:2 with lines
 
#pause 4

set yrange [0:*]
set out 'debt.tallscale.tex' 
set ylabel "\\rotatebox{90}{National debt}"
plot 'data-debt' index 0 using 1:2 with lines

#pause 4

set yrange [*:*]
set out 'deficit.tex' 
set ylabel "\\rotatebox{90}{Annual deficit}"
plot 'data-debt' index 0 using 1:3 with lines

#pause 4
