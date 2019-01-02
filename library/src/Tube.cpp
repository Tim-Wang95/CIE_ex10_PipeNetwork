#include "Tube.hpp"
//#include "Node.hpp"

namespace cie {
	namespace pipenetwork {

		Tube::Tube(Node* node1, Node* node2, double diameter):
			x1_(node1->x()), y1_(node1->y()), x2_(node2->x()), y2_(node2->y()),
		    d(diameter), n1(node1), n2(node2) {}

		double Tube::length() const {
			return std::sqrt((x2_-x1_)*(x2_-x1_)+(y2_-y1_)*(y2_-y1_));
		}

		double Tube::permeability() const {
			return 3.14159265358979323846*9.81*std::pow(d, 4) / (128*this->length())*std::pow(10,6);
		}

		const Node* Tube::node1() const { return n1; }
		const Node* Tube::node2() const { return n2; }
	}
}
