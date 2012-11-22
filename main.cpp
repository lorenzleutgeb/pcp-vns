#include <iostream>                  // for //cout
#include <string>
#include <utility>                   // for pair
#include <boost/graph/graphviz.hpp>
#include "header/pcp.hpp"
#include "header/parser.hpp"
#include "header/oneStepCd.hpp"
#include "header/vns.hpp"

using namespace std;
using namespace pcp;
using namespace boost;


Solution::Solution() {
	this->g = new Graph(0);
	this->colorsUsed = 0;
}

Solution::Solution(Solution *toCopy) {
	this->g = new Graph(0);
	this->numParts = toCopy->numParts;
	this->partition = new int[numParts];
	this->colorsUsed = toCopy->colorsUsed;
	copy_graph(*toCopy->g, *this->g);
}


int main(int, char*[]) {
	Solution *fullG = new Solution();
	
	if (!readGraph(cin, *fullG)) {
		cerr<<"Error reading from stdin"<<endl;
	}
	
	Solution *onestep = (onestepCD(*fullG));
	
	graph_traits<Graph>::edge_iterator ei, ei_end;
	


	cout<<"Onestep solution uses "<<onestep->colorsUsed<<" colors"<<endl;
	
	Solution best = vnsRun(*onestep, *fullG, 1, 0);
	VertexID_Map vertex_id = get(vertex_index2_t(), *best.g);
	write_graphviz(cout, *best.g, make_label_writer(vertex_id));
	cout<<"Writing complete"<<endl;
	return 0;
}