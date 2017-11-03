#ifndef MFP_H
#define MFP_H

#include "iforest/IsolationForest.hpp"

int compute_mfp_from_expl_file(std::vector<double> query, std::vector<int> ordered_feats, dataframe data, doubleframe *df, IsolationForest *iff);
void compute_mfp_while_building_expls(std::vector<double> query, std::vector<int> ordered_feats, dataframe data, doubleframe *df, IsolationForest *iff);

#endif
