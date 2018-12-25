#include "catch.hpp"
#include "linalg.hpp"

#include <fstream>

namespace cie
{
	namespace linalg
	{

		TEST_CASE("Matrix")
		{
			CHECK(Matrix(3, 0.0).size() == 3);

			Matrix matrix1(2, 4.2);
			Matrix matrix(matrix1);

			REQUIRE(matrix.size() == 2);

			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					CHECK(matrix(i, j) == 4.2);

					matrix(i, j) = i * 10.0 + j;
				}
			}

			const Matrix& ref = matrix;

			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					CHECK(ref(i, j) == i * 10.0 + j);
				}
			}
		}

		TEST_CASE("Matrix_zero_size")
		{
			Matrix m;

			REQUIRE_NOTHROW(m = Matrix(0, 2.0));

			CHECK(m.size() == 0);

			REQUIRE_NOTHROW(m = Matrix{ std::vector<Vector>{ } });

			CHECK(m.size() == 0);
		}

		TEST_CASE("Matrix_inconsistent_input")
		{
			std::vector<Vector> inconsistentData
			{
				Vector{  0.0, 0.0, 0.0 },
				Vector{  0.0, 0.0 },
				Vector{  0.0, 0.0, 0.0 }
			};

			CHECK_THROWS_AS(Matrix{ inconsistentData }, std::runtime_error);

			CHECK_THROWS_AS(Matrix{ { Vector { } } }, std::runtime_error);
		}

		namespace linalgtesthelper
		{
			template<typename ContainerType>
			std::vector<double> writeAndParse(const ContainerType& container)
			{
				std::ofstream outfile("write.txt");

				REQUIRE_NOTHROW(linalg::write(container, outfile));

				outfile.close();

				std::vector<double> values;

				std::ifstream infile("write.txt");

				double result;
				while (infile >> result)
				{
					values.push_back(result);
				}

				infile.close();

				return values;
			}
		}

		TEST_CASE("write_vector")
		{
			Vector v{ 0.0, 2.0, 4.0 };

			auto result = linalgtesthelper::writeAndParse(v);

			REQUIRE(result.size() == 3);

			CHECK(result[0] == v[0]);
			CHECK(result[1] == v[1]);
			CHECK(result[2] == v[2]);
		}

		TEST_CASE("write_matrix")
		{
			Matrix m({ Vector{ 1.0, -2.0 },
						Vector{ -8.0, 4.0 } });

			auto result = linalgtesthelper::writeAndParse(m);

			REQUIRE(result.size() == 4);

			CHECK(result[0] == m(0, 0));
			CHECK(result[1] == m(0, 1));
			CHECK(result[2] == m(1, 0));
			CHECK(result[3] == m(1, 1));
		}

		TEST_CASE("norm")
		{
			Vector vector{ 4.0, 3.0 };

			double tolerance = 1e-12;

			CHECK(norm(vector) == Approx(5.0).epsilon(tolerance));

			Matrix matrix({ Vector{  1.2,  3.3,  9.1 },
							 Vector{  2.9,  8.6,  2.6 },
							 Vector{ -4.8,  0.3, -2.1 } });

			CHECK(norm(matrix) == Approx(14.553693689232297).epsilon(tolerance));
		}

		TEST_CASE("solve")
		{
			Matrix matrix({ Vector{  5.2,  1.2,  7.3, -2.3 },
							 Vector{  8.9, -7.6, -0.2,  3.4 },
							 Vector{ -5.7,  6.2, -3.4,  7.8 },
							 Vector{  9.8, -0.7,  5.4, -2.1 } });

			Vector rhs{ -3.8, 0.3, 6.1, 2.8 };

			REQUIRE(matrix.size() == 4);

			Vector solution = solve(matrix, rhs);

			REQUIRE(solution.size() == 4);

			double tolerance = 1e-12;

			CHECK(solution[0] == Approx(1.3218868527560599).epsilon(tolerance));
			CHECK(solution[1] == Approx(1.4702413909379624).epsilon(tolerance));
			CHECK(solution[2] == Approx(-1.7634954348963456).epsilon(tolerance));
			CHECK(solution[3] == Approx(-0.1893110309940256).epsilon(tolerance));
		}

		TEST_CASE("solve_singular")
		{
			Matrix matrix({ Vector{  1.0, -1.0 },
							 Vector{ -1.0,  1.0 } });

			Vector rhs{ 0.0, 0.0 };

			REQUIRE(matrix.size() == 2);

			CHECK_THROWS_AS(solve(matrix, rhs), std::runtime_error);
		}

	} // namespace linalg
} // namespace cie
