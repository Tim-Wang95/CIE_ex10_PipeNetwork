#include "PipeNetwork.hpp"

namespace cie {
	namespace pipenetwork {

		// Constructor
		PipeNetwork::PipeNetwork(const std::string& filename) {

			std::ifstream infile(filename);
			infile >> numOfNodes; infile >> numOfTubes;
			node_ = new Node*[numOfNodes];
			tube_ = new Tube*[numOfTubes];
			Q.assign(numOfNodes,0);
			B = new linalg::Matrix(numOfNodes);

			for (int i = 0; i < numOfNodes*3; i++) {
				//for (int count = 0; count < 3; count++) {
					double value; infile >> value;
					node_data.push_back(value);
				//}
			}

			for (int j = 0; j < numOfTubes*3; j++) {
				//for (int count = 0; count < 3; count++) {
					double value; infile >> value;
					tube_data.push_back(value);
				//}
			}

			for (int i = 0; i < numOfNodes; i++) {
				node_[i] = new Node(node_data[i * 3], node_data[i * 3 + 1], node_data[i * 3 + 2], i);
			}

			for (int i = 0; i < numOfTubes; i++) {
				tube_[i] = new Tube(node_[(int)tube_data[i * 3]], node_[(int)tube_data[i * 3 + 1]],
					tube_data[i * 3 + 2]);
			}

			for (int i = 0; i < numOfTubes; i++) {
				B->operator()(tube_[i]->node1()->id(), tube_[i]->node1()->id()) += tube_[i]->permeability();
				B->operator()(tube_[i]->node2()->id(), tube_[i]->node2()->id()) += tube_[i]->permeability();
				B->operator()(tube_[i]->node1()->id(), tube_[i]->node2()->id()) -= tube_[i]->permeability();
				B->operator()(tube_[i]->node2()->id(), tube_[i]->node1()->id()) -= tube_[i]->permeability();
			}

			for (int i = 0; i < numOfNodes; i++) {
				Q[i] += node_[i]->flow();
				B->operator()(i, 0) = 0;
				B->operator()(0, i) = 0;
			}
			B->operator()(0, 0) = 1;

			Q[0] = 0;
		}

		// Calculation Function
		std::vector<double> PipeNetwork::computeFluxes() const {
			
			std::vector<double> h = linalg::solve(*B, Q);
			std::vector<double> q(numOfTubes);
			for (int i = 0; i < numOfTubes; i++) {
				q[i] = tube_[i]->permeability()*(h[tube_[i]->node1()->id()] - h[tube_[i]->node2()->id()]);
			}

			return q;
		}

		/*
		void PipeNetwork::print() {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					std::cout << B->operator()(i, j) << " ";
				}
				std::cout << std::endl;
			}
			//std::cout << tube_[0]->permeability();
			std::cout << std::endl;
			std::cout << std::endl;
		}
		*/
	}
}
