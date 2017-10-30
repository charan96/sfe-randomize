#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"
#include "build-mfp.h"


int main()
{
	/* reading input file with only nominals */
	dataframe ndata = get_data_set(INFILE);
	doubleframe *df = build_doubleframe(INFILE.c_str(), 0);

	/* std::vector<std::vector<int> > ranked_feats = get_ranked_features(INFILE, ndata, df);
	std::cout << "finished ranking; writing to file" << std::endl;
	build_expl_file(ranked_feats); */

	IsolationForest iff = build_Isolation_forest(df);
	
	std::vector<double> query = {0.634225779210607,0.0259042993306371,1.19635582987287,-0.00711012151427251,0.805633716357868,-0.00739065642095547,0.221767578497091,-0.321436897072633,-0.387772578572719};

	// std::vector<int> ordered_feats = {8, 7, 9, 5, 6, 4, 2, 1, 3};
	std::vector<int> ordered_feats = {8, 5, 9, 7, 3, 4, 2, 1, 6};

	std::cout << "comp val: " << compute_mfp(query, ordered_feats, ndata, df, &iff) << std::endl;

	return 0;
}
