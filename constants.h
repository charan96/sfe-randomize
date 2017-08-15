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

// using namespace std;

typedef std::vector<std::pair<std::string, std::vector<double> > > dataframe;
typedef std::vector<std::pair<int, float> > ftplen;
const int NUM_DATAPOINTS = 58000;
const int NUM_FEATS = 9;
const int NUM_REPS = 5;
const std::string INFILE = "data/nominal-bench.csv";
const std::string QUERYFILE = "data/anomaly-bench.csv";
const std::string OUTFILE = "output.out";

#endif
