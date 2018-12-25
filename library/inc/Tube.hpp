#ifndef TUBE_HPP
#define TUBE_HPP

//#include "PipeNetwork.hpp"
#include <cmath>
#include "Node.hpp"

namespace cie {
	namespace pipenetwork {

		class Tube /*: public PipeNetwork*/ {
			public:
			Tube(Node* node1, Node* node2, double diameter);
			double length() const;
			double permeability() const;
			const Node* node1() const;
			const Node* node2() const;

			private:
			double x1_, y1_, x2_, y2_, d;
			Node* n1; Node* n2;
		};

	}
}

#endif
