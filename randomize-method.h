#ifndef RANDOMIZE_H
#define RANDOMIZE_H

dataframe get_data_set();
vector<double> switch_feature(int feat_num, dataframe data, vector<double> query);
vector<int> ordered_feats(ftplen vec);
ftplen build_feat_pathlen(vector<double> query, dataframe data);

#endif
