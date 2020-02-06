from scitools.std import *

n = 100
h = 5.0/(n+1)
infile = open('project2exc2w001up.txt', 'r')
infile2 = open('project2exc2w05up.txt', 'r')
infile3 = open('project2exc2w10up.txt', 'r')
infile4 = open('project2exc2w50up.txt', 'r')

lines = infile.readlines()
lines2 = infile2.readlines()
lines3 = infile3.readlines()
lines4 = infile4.readlines()

infile.close()
infile2.close()
infile3.close()
infile4.close()

rho = zeros(n)
V = zeros(n)
V2 = zeros(n)
V3 = zeros(n)
V4 = zeros(n)

for i in range(n):
	rho[i] = (i+1)*h
	"""
	V[i] = lines[i]
	V2[i] = lines2[i]
	V3[i] = lines3[i]
	V4[i] = lines4[i]
	"""
	V[i] = float(lines[i])*float(lines[i])
	V2[i] = float(lines2[i])*float(lines2[i])
	V3[i] = float(lines3[i])*float(lines3[i])
	V4[i] = float(lines4[i])*float(lines4[i])
	
plot(rho, V)
legend('w = 0.01')
xlabel('distance')
ylabel('potential')
hold('on')
plot(rho, V2)
legend('w = 0.5')
hold('on')
plot(rho, V3)
legend('w = 1.0')
hold('on')
plot(rho, V4)
legend('w = 5.0')

hardcopy('potentialexc2square.png')


