#include "PipeNetwork.hpp"

int main() {

	std::string infilename = "C:/Users/tan84/Desktop/input.txt";
	std::string outfilename = "C:/Users/tan84/Desktop/pipedata.txt";

	// calculate fluxes
	cie::pipenetwork::PipeNetwork p(infilename);
	std::vector<double> q = p.computeFluxes();
	
	// output file
	std::ofstream outfile; 
	outfile.open(outfilename);
	for (int i = 0; i < q.size(); i++) {
		outfile << i+1 << ".  " << q[i] << " " << std::endl;
	}
	outfile.close();

	// read file back in
	std::string line;
	std::ifstream read(outfilename);
	while (std::getline(read, line)) {
		std::cout << line << std::endl;
	}
	read.close();

	std::cout << std::endl;
	std::cout << std::endl;

	return 0;
}
