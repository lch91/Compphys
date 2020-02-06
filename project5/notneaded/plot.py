#!/usr/bin/python

from scitools.std import *

infile = open("probdiff.dat", "r")
y = zeros(100000)
i = 0
for line in infile:
	line = line.split()
	y[i] = float(line[1])#*sqrt(2*1./10000.)
	i += 1

x = linspace(0, 1, len(y[:i]))
y = y/max(y)
plot(x,y[:i])
xlabel("position")
ylabel("Brainstuff")
#hardcopy("diff10000timestepvariance.png")
