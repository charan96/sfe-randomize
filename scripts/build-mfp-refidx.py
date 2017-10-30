import re, csv, itertools, linecache

# data files
half_refidx = "../anomaly_refidx.csv"
filled_refidx = "refidx_100.csv"
bench_file = "../data/benchid_100_shuttle.csv"
mother_data = "../data/shuttle.preproc.csv"


with open(half_refidx, 'r') as hr, open(filled_refidx, 'w') as fr, open(bench_file, 'r') as bench, open(mother_data, 'r') as mother:
	fr.write("\"\",\"anoIdx\",\"refIdx\"\n")		# header for filled_refidx
	mom_data = mother.readlines()
	
	for idx, line in enumerate(hr):
		if idx == 0:
			continue

		line = map(int, line.rstrip("\n").split(","))
		
		b_line = linecache.getline(bench_file, line[1] + 1)
		b_line = b_line.rstrip("\n").split(',')
		del b_line[1]
		b_line = ','.join(b_line)
		b_line = b_line + "\n"

		line_match = mom_data.index(b_line)
		
		fr.write("\"{}\",{},{}\n".format(idx + 1, line[1], line_match))

	linecache.clearcache()
