#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"

int main()
{
	dataframe data = get_data_set();
	doubleframe *df = build_doubleframe(INFILE.c_str());
	print_dataframe(data);

	std::vector<double> query = {0.961074390045098,-0.0125779430326821,2.65657571737471,
				-0.0344912414815925,1.17497576719637,-0.00739065642095547,
				0.908191661935069,-0.0412993573002382,-0.543937066541179};

	std::map<int, float> mymap = build_avg_feat_lens(query, data, df);
	print_map(mymap);
	// std::vector<double> feat_lens = feat_importance_vector(query, data, df);
	// print_vector(feat_lens);

	ftplen myvec = map_to_vector_pair(mymap);
	myvec = sort_vector_pair(myvec);
	print_vector_pair(myvec);

	build_explanation_file(mymap);
	/* std::vector<int> feats = ordered_feats(myvec);
	printf("\n");

	print_vector(feats); */
	
	return 0;
}
