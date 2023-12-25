set terminal pdfcairo enhanced
set output 'plot4.pdf'

set xlabel 'x'
set ylabel 'y'
set xrange [-0.1: 6.1]
set yrange [0: 250]
# Plotting data with uncertainty bars
plot 'graph.in' using 1:2:3 with yerrorbars pt 0 notitle
