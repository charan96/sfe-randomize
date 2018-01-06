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
#include <math.h>


typedef std::vector<std::pair<std::string, std::vector<double> > > dataframe;
typedef std::vector<std::pair<int, double> > ftplen;

const int COL_START = 2;	// features starting from 3rd column in dataset (starting from 0); E.g in the infile, first 2 cols are metadata i.e, ground truth and diff score
const int NUM_REPS = 25;		// change to 25 after testing
const int MFP_REPS = 100;	// number of repitions for building MFP
const double TOLERANCE = 0.1;	// tolerance levels for MFP

const std::string INFILE = "data/benchid_100_shuttle.csv";
const std::string REF_FILE = "anomaly_refidx.csv";
const std::string OUTFILE = "bench100_all_ranked_explanations30.csv";
const std::string MFP_FILE = "explanations_MFP.csv";

#endif
