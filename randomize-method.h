#ifndef RANDOMIZE_H
#define RANDOMIZE_H

dataframe get_data_set(std::string input_file);
std::vector<double> switch_feature(int feat_num, dataframe data, std::vector<double> query);

std::map<int, float> build_avg_feat_lens(std::vector<double> query, dataframe data, doubleframe *df);

std::vector<std::vector<int> > get_ranked_features(std::string qfile, dataframe nominal_df, doubleframe *df);
void build_dropout_expl_file(std::vector<std::vector<int> > ranked_feats);

#endif
