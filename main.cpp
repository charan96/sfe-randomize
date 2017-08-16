#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"

int main()
{
	/* reading input file with only nominals */
	dataframe ndata = get_data_set(INFILE);
	doubleframe *df = build_doubleframe(INFILE.c_str());
	// print_dataframe(ndata);
	
	std::cout<< get_num_cols_in_file(INFILE) << std::endl;
	dataframe qdata = get_data_set(QUERYFILE);

	for (int i=0; i<qdata.size(); i++)
	{
		std::vector<double> qpoint = qdata.at(i).second;
		std::map<int, float> mymap = build_avg_feat_lens(qpoint, ndata, df);

		print_map(mymap);

		if (i==3)
			break;
	}

	/*
	std::vector<double> query = {0.961074390045098,-0.0125779430326821,2.65657571737471,
				-0.0344912414815925,1.17497576719637,-0.00739065642095547,
				0.908191661935069,-0.0412993573002382,-0.543937066541179};

	std::map<int, float> mymap = build_avg_feat_lens(query, ndata, df);
	print_map(mymap);
	// std::vector<double> feat_lens = feat_importance_vector(query, ndata, df);
	// print_vector(feat_lens);

	ftplen myvec = map_to_vector_pair(mymap);
	myvec = sort_vector_pair(myvec);
	print_vector_pair(myvec);

	build_explanation_file(mymap); */
	/* std::vector<int> feats = ordered_feats(myvec);
	printf("\n");

	print_vector(feats); */

	
	return 0;
}
