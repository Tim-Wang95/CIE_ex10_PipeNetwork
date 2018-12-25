#include "PipeNetwork.hpp"

int main() {

	std::string filename = "C:/Users/tan84/Desktop/input.txt";
	cie::pipenetwork::PipeNetwork p(filename);

	//p.print();

	std::vector<double> q = p.computeFluxes();

	for (int i = 0; i < q.size(); i++) {
		std::cout << i+1 << ".  " << q[i] << " " << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	return 0;
}
