set terminal pdfcairo enhanced
set output 'plot1.pdf'
set xlabel 'x'
set ylabel 'f(x)'
set xrange [0:10]  # Set the x-axis range
set yrange [-1.1:1.1]  # 
plot 'data.txt' with lines