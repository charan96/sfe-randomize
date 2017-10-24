#include "constants.h"
#include "print_funcs.h"
#include "utilities.h"
#include "randomize-method.h"


int main()
{
	/* reading input file with only nominals */
	dataframe ndata = get_data_set(INFILE);
	doubleframe *df = build_doubleframe(INFILE.c_str(), 0);

	std::vector<std::vector<int> > ranked_feats = get_ranked_features(INFILE, ndata, df);
	std::cout << "finished ranking; writing to file" << std::endl;
	build_expl_file(ranked_feats);
	
	
	/* for (int inst = 0; inst <df->nrow; inst++)
	{
		std::cout << inst+1 << ": ";
		// printf("%f\n", *df->data[inst]);
		std::vector<double> val;

		for (int i=0; i<df->ncol; i++)
			val.push_back(df->data[inst][i]);

		print_vector(val);

		if (inst == 0)
			break;
		// for (int i=0; i< (sizeof(df->data[inst])/sizeof(df->data[inst][1])); i++)
		
		//val.push_back();
		//double val = df->data[inst][3];
		//std::cout << val << std::endl;
	}*/
	/* IsolationForest iff = build_Isolation_forest(df);
	print_vector(iff.AnomalyScore(df)); */

	return 0;
}
