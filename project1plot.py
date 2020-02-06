# Python-program for plotting the results
from scitools.std import * # INF1100-package that include everything we need

n = 100		# The n from previously
infile = open('project.txt', 'r')	# Opens the file we wrote to
lines = infile.readlines()			# Reading in the lines
infile.close()						# Closing the file
v = zeros(n)						# Empty vector to store the values

for i in range(n):
	v[i] = lines[i]					# Putting the values into the vector
	
x = linspace(0, 1, n)				# The x-values used
u = 1-(1-exp(-10))*x-exp(-10*x)		# The exact solution

# The plot commands, plotting the numerical and exact solution together
plot(x, v)
legend('numerical')
hold('on')
plot(x, u)
legend('exact')

hardcopy('plot.png')
raw_input('enter')

