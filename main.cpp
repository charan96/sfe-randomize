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

	std::vector<std::vector<int> > ranked_feats = get_ranked_features(INFILE, ndata, df);
	std::cout << "finished ranking; writing to file" << std::endl;
	build_expl_file(ranked_feats);


	/****************************************************************/
	/****************** MFP FROM EXPLANATIONS FILE ******************/
	/****************************************************************/

	/* IsolationForest iff = build_Isolation_forest(df);

	std::vector<std::vector<double> > datapoints = get_all_datapoints(ndata);
	std::vector<std::vector<int> > expls = read_bench_expl_file(OUTFILE);
	std::vector<int> anomalies = get_anomalies_idx(ndata);

	std::vector<double> avg_mfp;

	if (datapoints.size() == expls.size())
	{
		for (int i: anomalies)
		{
			std::vector<double> query = datapoints.at(i);
			std::vector<int> explanation = expls.at(i);

			avg_mfp.push_back(compute_mfp_from_expl_file(query, explanation, ndata, df, &iff));
		}
	} 
	else
	{
		std::cout << "ERROR: datapoints.size() != explanations.size()" << std::endl;
		exit(0);
	}

	std::cout << "Average MFP: " << double_vector_avg(avg_mfp) << std::endl; */

	/****************************************************************/
	/****************************************************************/
	/****************************************************************/

	return 0;
}
