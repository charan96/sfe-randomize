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

	// READ FROM FILE FOR QUERY AND ORD FEATS (FIXME)
	/*std::vector<std::vector<int> > expls = read_bench_expl_file(OUTFILE);

	int randnum = randint(0, ndata.size());
	std::vector<double> query = ndata.at(randnum - 1).second;
	std::vector<int> ordered_feats = expls.at(randnum);

	printf("rand num: %d\n", randnum);
	print_vector(query);
	printf("\n\n");
	print_vector(ordered_feats);

	return 0; */

	// BUILDING EXPL FILES
	/* std::vector<std::vector<int> > ranked_feats = get_ranked_features(INFILE, ndata, df);
	std::cout << "finished ranking; writing to file" << std::endl;
	build_expl_file(ranked_feats); */

	IsolationForest iff = build_Isolation_forest(df);
	
	std::vector<double> query = {-0.591456511418738,-0.0382327712748949,-0.600837877821693,-0.00711012151427251,0.343956152809745,0.0753308156077501,0.145498235892871,-0.554884846882962,-0.543937066541179};
	std::vector<int> ordered_feats = {7, 9, 5, 8, 3, 6, 2, 4, 1};
	std::cout << "comp val: " << compute_mfp(query, ordered_feats, ndata, df, &iff) << std::endl;

	//==== ANomaly ====
	query = {0.634225779210607,0.000249471088424276,-0.937811698014425,-0.00711012151427251,-2.05676717764049,0.0201831675886131,-1.22734993098309,1.6862154712962,2.03277698493842};
	ordered_feats = {9, 8, 7, 5, 2, 4, 6, 3, 1};
	std::cout << "comp val: " << compute_mfp(query, ordered_feats, ndata, df, &iff) << std::endl;
	
	query = {2.51360529150894,0.000249471088424276,-0.263864057628962,-0.00711012151427251,-3.34946435557524,0.112095914287175,-2.52392875525482,3.3203511199685,4.06291532852841};
	ordered_feats = {9, 8, 5, 7, 4, 6, 3, 2, 1};
	std::cout << "comp val: " << compute_mfp(query, ordered_feats, ndata, df, &iff) << std::endl;

	query = {0.389089321084738,0.000249471088424276,1.98262807698925,-0.0344912414815925,0.805633716357868,-0.103899040454445,0.984461004539289,0.00539023266182758,-0.465854822556949};
	ordered_feats = {1, 9, 6, 2, 8, 7, 3, 4, 5}; 


	std::cout << "comp val: " << compute_mfp(query, ordered_feats, ndata, df, &iff) << std::endl;

	// std::cout << "comp val: " << compute_mfp(query, ordered_feats, ndata, df, &iff) << std::endl;

	return 0;
}
