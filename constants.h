#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <bits/stdc++.h>
#include <random>
#include <map>

typedef std::vector<std::pair<std::string, std::vector<double> > > dataframe;
typedef std::vector<std::pair<int, float> > ftplen;
// const int NUM_DATAPOINTS = 58000;
// const int NUM_FEATS = 9;
const int COL_START = 2;	// features starting from 3rd column in dataset (starting from 0); E.g in the infile, first 2 cols are metadata i.e, ground truth and diff score
const int NUM_REPS = 30;		// change to 30 after testing
const std::string INFILE = "data/nominal-bench.csv";
const std::string QUERYFILE = "data/anomaly-bench.csv";
const std::string OUTFILE = "output.out";

#endif
