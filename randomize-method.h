#ifndef RANDOMIZE_H
#define RANDOMIZE_H

dataframe get_data_set();
std::vector<double> switch_feature(int feat_num, dataframe data, std::vector<double> query);
std::vector<int> ordered_feats(ftplen vec);
ftplen build_feature_pathlen(std::vector<double> query, dataframe data, doubleframe *df);
void build_explanation_file();

#endif
