#ifndef RANDOMIZE_H
#define RANDOMIZE_H

dataframe get_data_set();
std::vector<double> switch_feature(int feat_num, dataframe data, std::vector<double> query);

std::map<int, float> build_feature_pathlen(std::vector<double> query, dataframe data, doubleframe *df);
std::map<int, float> build_avg_feat_lens(std::vector<double> query, dataframe data, doubleframe *df);

void build_explanation_file(std::map<int, float> mymap);

#endif
