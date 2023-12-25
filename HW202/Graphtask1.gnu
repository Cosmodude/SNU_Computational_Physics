set terminal pngcairo
set output 'output.png'

# Set title for the plot
set title "Graph of Data Points"

# Set labels for the axes
set xlabel "X-axis"
set ylabel "Y-axis"

# Plot the data points
plot "./HW202/data.txt" with linespoints

set output