#ifndef PIPE_NETWORK_HPP
#define PIPE_NETWORK_HPP

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "linalg.hpp"
#include "Node.hpp"
#include "Tube.hpp"

namespace cie {
	namespace pipenetwork {

		class PipeNetwork {
		public:
			PipeNetwork(const std::string& filename);
			std::vector<double> computeFluxes() const;
			void print();
			//PipeNetwork(linalg::Matrix matrix) : B(matrix) {}

		private:
			int numOfNodes, numOfTubes;
			std::vector<double> node_data, tube_data; 
			Node** node_; Tube** tube_;
			linalg::Matrix* B; //Permeability matrix
			std::vector<double> Q; //Load vector
			//linalg::Matrix* Node_data; linalg::Matrix* Tube_data;
		};
	}
}


#endif