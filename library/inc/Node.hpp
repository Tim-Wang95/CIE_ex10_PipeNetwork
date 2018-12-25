#ifndef NODE_HPP
#define NODE_HPP

//#include "PipeNetwork.hpp"

namespace cie {
	namespace pipenetwork {

		class Node /*: public PipeNetwork*/ {
		public:
		Node(double x, double y, double flow, int id);
		double x() const;
		double y() const;
		double flow() const;
		int id() const;

		private:
		double x_, y_, flow_;
		int id_;
		};

	}
}

#endif