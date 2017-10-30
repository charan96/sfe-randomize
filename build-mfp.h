#ifndef MFP_H
#define MFP_H

#include "iforest/IsolationForest.hpp"

int compute_mfp(std::vector<double> query, std::vector<int> ordered_feats, dataframe data, doubleframe *df, IsolationForest *iff);
void write_mfp_file();

#endif
