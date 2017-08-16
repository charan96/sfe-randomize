#ifndef RANDOMIZE_H
#define RANDOMIZE_H

dataframe get_data_set(std::string input_file);
std::vector<double> switch_feature(int feat_num, dataframe data, std::vector<double> query);

std::map<int, float> build_feature_pathlen(std::vector<double> query, dataframe data, float base_pathlen, IsolationForest &iff);
std::map<int, float> build_avg_feat_lens(std::vector<double> query, dataframe data, doubleframe *df);

std::vector<std::vector<int> > ranked_features();
void build_explanation_file(std::map<int, float> mymap);

#endif
