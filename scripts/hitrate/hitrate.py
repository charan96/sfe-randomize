import os


anom = "anomaly_refidx.csv"
old = "old_refidx.csv"


with open(anom, 'r') as afile, open(old, 'r') as ofile:
	l1 = []
	l2 = []

	for idx, line in enumerate(afile):
		if idx == 0:
			continue

		line = line.rstrip("\n").split(',')
		l1.append(line[1])

	for idx, line in enumerate(ofile):
		if idx == 0:
			continue

		line = line.rstrip("\n").split(',')
		l2.append(line[1])

	print l1 
	print l2

