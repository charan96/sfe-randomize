#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"

int main()
{
	dataframe data = get_data_set();
	std::string infile = "shuttle.preproc.csv";
	doubleframe *df = build_doubleframe(infile.c_str());
	// print_dataframe(data);

	std::vector<double> query = {0.961074390045098,-0.0125779430326821,2.65657571737471,
				-0.0344912414815925,1.17497576719637,-0.00739065642095547,
				0.908191661935069,-0.0412993573002382,-0.543937066541179};

	ftplen myvec = build_feature_pathlen(query, data, df);
	print_vector_pair(myvec);

	myvec = sort_vector_pair(myvec);
	print_vector_pair(myvec);

	std::vector<int> feats = ordered_feats(myvec);
	printf("\n");

	print_vector(feats);
	
	return 0;
}
