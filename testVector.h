#pragma once
#include "vector.h"
#include <cassert>
#include <cmath>
#include <iostream>

class TestVector {
public:
	// Static method to run all tests
	static void runTests() {

		//test the operators
		testScalarMultiplicationOperator();
		testOperatorSum();
		testOperatorSumEqual();
		testOperatorSubtraction();

		//test the methods
		testNorm();
		testNormSquared();		
		testDotProduct();
		testCrossProduct();
		testComponentProduct();
		testNormalization();

		std::cout << "All vector tests passed!" << std::endl;
	}

private:

	//#################OPERATOR TEST#################

	static void testScalarMultiplicationOperator() {
		vect a(1.0f, 2.0f, 3.0f);
		vect s = a * 2.0f;
		assert(s.x == 2.0f && s.y == 4.0f && s.z == 6.0f);
	}

	static void testOperatorSum() {
		vect a(1, 2, 3), b(4, 5, 6);
		vect sum = a + b;
		assert(sum.x == 5 && sum.y == 7 && sum.z == 9);
	}

	static void testOperatorSumEqual() {
		vect a(1, 2, 3);
		vect b(4, 5, 6);
		a += b;
		assert(a.x == 5 && a.y == 7 && a.z == 9);
	}

	static void testOperatorSubtraction() {
		vect a(1, 2, 3), b(4, 5, 6);
		vect diff = a - b;
		assert(diff.x == -3 && diff.y == -3 && diff.z == -3);
	}


	//#################METHOD TEST#################

	static void testNorm() {
		vect a(1.0f, 2.0f, 3.0f);
		assert(a.getNorm() == std::sqrtf(14.0f));
	}

	static void testNormSquared() {
		vect a(1.0f, 2.0f, 3.0f);
		assert(a.getNormSquared() == 14.0f);
	}	

	static void testDotProduct() {
		vect a(1, 2, 3), b(4, 5, 6);
		assert(a.ProduitScalaire(b) == 32.0f);
	}

	static void testCrossProduct() {
		vect a(1, 2, 3), b(4, 5, 6);
		vect cross = a.ProduitVectoriel(b);
		assert(cross.x == -3 && cross.y == 6 && cross.z == -3);
	}

	static void testComponentProduct() {
		vect a(1, 2, 3), b(4, 5, 6);
		vect comp = a.composantProduct(b);
		assert(comp.x == 4 && comp.y == 10 && comp.z == 18);
	}

	static void testNormalization() {
		vect a(1.0f, 2.0f, 3.0f);
		vect n = a.normalize();
		assert(std::abs(n.getNorm() - 1.0f) < 1e-6); // Check that the length of the normalized vector is approximately 1
	}
};
