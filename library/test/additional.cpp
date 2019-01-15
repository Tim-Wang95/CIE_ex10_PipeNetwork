#include "PipeNetwork.hpp"
#include "Node.hpp"
#include "Tube.hpp"

#include "catch.hpp"


namespace cie {
	namespace pipenetwork {

		TEST_CASE("Node_test_additional") {
			Node node(1.1, 0.9, 19, 95);

			double tolerance = 1e-14;

			CHECK(node.x() == Approx(1.1).epsilon(tolerance));
			CHECK(node.y() == Approx(0.9).epsilon(tolerance));
			CHECK(node.flow() == Approx(19).epsilon(tolerance));
			CHECK(node.id() == 95);
		}

		TEST_CASE("Tube_test_additional") {
			Node node1(1.1, 0.9, 19, 95);
			Node node2(4.1, 4.9, 0, 96);

			Tube tube(&node1, &node2, 0.3);

			double tolerance = 1e-14;

			CHECK(tube.length() == Approx(5).epsilon(tolerance));

			double pi = 3.14159265358979323846;

			double permeability = pi * 9.81 * std::pow(0.3, 4) / (128 * 1e-6 * 5);

			CHECK(tube.permeability() == Approx(permeability).epsilon(tolerance));
		}


	}
}

