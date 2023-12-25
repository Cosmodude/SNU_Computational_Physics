set terminal pdfcairo enhanced color
set output 'fig_1.pdf'

set title "Average f(x) and Statistical Uncertainty"
set xlabel "x"
set ylabel "Average f(x)"
set y2label "Statistical Uncertainty (σ(x))"
set grid
set key top right

# Manually set the y-axis range
set yrange [0:450]  # Adjust the upper limit as needed

# Plot the average f(x)
plot 'stat.out' using 1:2 with lines title "Average f(x)"

# Plot the statistical uncertainty (σ(x))
set yrange [0:6.5]  # Adjust the upper limit as needed
set y2tics
set format y2 "%.2f"
plot 'stat.out' using 1:3 with errorbars axes x1y2 title "Statistical Uncertainty (σ(x))"
