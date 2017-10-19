#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"

int main()
{
	/* reading input file with only nominals */
	dataframe ndata = get_data_set(INFILE);
	doubleframe *df = build_doubleframe(INFILE.c_str());
	
	// std::cout<< get_num_cols_in_file(INFILE) << std::endl;
	std::vector<std::vector<int> > ranked_feats = get_ranked_features(QUERYFILE, ndata, df);
	build_dropout_expl_file(ranked_feats);

	return 0;
}
