from scitools.std import *

infile = open('2_Earth.dat', 'r')
N = 400000
t = zeros(N)
spin = zeros(N)
i=0
for line in infile:
	line = line.split()
	t[i] = float(line[0])
	spin[i] = float(line[5])
	spin[i] = spin[i]/(1.0*10**(30))
	i += 1
#print spin[:i], t[:i]	
plot(t[:i], spin[:i])
xlabel('time [yr]')
ylabel('energy [10**30*kg*AU**2/yr**2]')
hardcopy('energy.png')
"""
infile2 = open('2_Mercury.dat', 'r')
infile3 = open('4_Venus.dat', 'r')
infile4 = open('4_Earth.dat', 'r')
infile5 = open('4_Mars.dat', 'r')
infile6 = open('4_Jupiter.dat', 'r')
infile7 = open('4_Saturn.dat', 'r')
infile8 = open('4_Uranus.dat', 'r')
infile9 = open('4_Neptune.dat', 'r')
infile10 = open('4_Pluto.dat', 'r')

x = zeros(N)
y = zeros(N)

x2 = zeros(N)
y2 = zeros(N)

x3 = zeros(N)
y3 = zeros(N)

x4 = zeros(N)
y4 = zeros(N)

x5 = zeros(N)
y5 = zeros(N)

x6 = zeros(N)
y6 = zeros(N)

x7 = zeros(N)
y7 = zeros(N)

x8 = zeros(N)
y8 = zeros(N)

x9 = zeros(N)
y9 = zeros(N)

x10 = zeros(N)
y10 = zeros(N)

i = 0
j = 0
k = 0
l = 0
m = 0
n = 0
o = 0
p = 0
q = 0
r = 0
for line in infile:
	line = line.split()
	x[i] = float(line[1])
	y[i] = float(line[2])
	i +=1
	
for line3 in infile3:	
	line3 = line3.split()
	x3[k] = float(line3[1])
	y3[k] = float(line3[2])
	k += 1

for line2 in infile2:
	line2 = line2.split()
	x2[j] = float(line2[1])
	y2[j] = float(line2[2])
	j += 1

for line4 in infile4:
	line4 = line4.split()
	x4[l] = float(line4[1])
	y4[l] = float(line4[2])
	l += 1

for line5 in infile5:
	line5 = line5.split()
	x5[m] = float(line5[1])
	y5[m] = float(line5[2])
	m += 1	

for line6 in infile6:
	line6 = line6.split()
	x6[n] = float(line6[1])
	y6[n] = float(line6[2])
	n += 1

for line7 in infile7:
	line7 = line7.split()
	x7[o] = float(line7[1])
	y7[o] = float(line7[2])
	o += 1
	
for line8 in infile8:
	line8 = line8.split()
	x8[p] = float(line8[1])
	y8[p] = float(line8[2])
	p += 1
	
for line9 in infile9:
	line9 = line9.split()
	x9[q] = float(line9[1])
	y9[q] = float(line9[2])
	q += 1
	
for line10 in infile10:
	line10 = line10.split()
	x10[r] = float(line10[1])
	y10[r] = float(line10[2])
	r += 1	
infile.close()
infile2.close()
infile3.close()	
infile4.close()
infile5.close()
infile6.close()
infile7.close()
infile8.close()
infile9.close()
infile10.close()
							
plot(x[:i],y[:i])
legend('Sun')
xlabel('x-position [AU]')
ylabel('y-position [AU]')
hold('on')

plot(x2[:j],y2[:j])
legend('Mercury')

hold('on')
plot(x3[:k], y3[:k])
legend('Venus')

hold('on')
plot(x4[:l], y4[:l])
legend('Earth')

hold('on')
plot(x5[:m], y5[:m])
legend('Mars')
hardcopy('innersolar.png')

hold('on')
plot(x6[:n], y6[:n])
legend('Jupiter')
hold('on')
plot(x7[:o], y7[:o])
legend('Saturn')
hold('on')
plot(x8[:p], y8[:p])
legend('Uranus')
hold('on')
plot(x9[:q], y9[:q])
legend('Neptune')
hold('on')
plot(x10[:r], y10[:r])
legend('Pluto')
hardcopy('solarsystem.png')
"""
