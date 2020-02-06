from scitools.std import *	# All important modules baked into one

n = 100		# Number of points
l = 1.0
t = 100./(float(5*n*n))
# Opening the various files I have created earlier
infile = open('ForwardEuler.txt')
infile2 = open('BackwardEuler.txt')
infile3 = open('CrankNico.txt')
x = linspace(0, 1, n)	# Our x-vector
y = -2/(l*pi)*sin(l*pi*x)*exp(-l*l*pi*pi*t) + 1 - x
# Initialising arrays for different solutions 
FE = zeros(n)
BE = zeros(n)
CN = zeros(n)
# Reading the files into this program
i = 0
for line in infile:
	FE[i] = float(line)
	i += 1

i = 0
for line2 in infile2:
	BE[i] = float(line2)
	i += 1

i = 0
for line3 in infile3:
	CN[i] = float(line3)
	i +=1
# Closing the files
infile.close()
infile2.close()
infile3.close()

# Plotting my results
plot(x, FE)
title('Forward Euler')
xlabel('position')
ylabel('Distribution of brainstuff')
hardcopy('Forwarddx100100.png')
raw_input('FE')
plot(x, BE)
title('Backward Euler')
xlabel('position')
ylabel('Distribution of brainstuff')
hardcopy('Backwarddx100100.png')
raw_input('BE')
plot(x, CN)
title('Crank Nicholson')
xlabel('position')
ylabel('Distribution of brainstuff')
hardcopy('Crankdx100100.png')
raw_input('CN')
plot(x,y)
title('Closed form solution')
xlabel('position')
ylabel('Distribution of brainstuff')
hardcopy('Closedform100100.png')
raw_input('CN')
