#include "pocketcalculator.h"
#include "sevensegment.h"
#include "calc.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <iostream>
#include <limits>

const std::string ERROR_MESSAGE =
		" -                  \n"
		"|                   \n"
		" -   -   -   -   -  \n"
		"|   |   |   | | |   \n"
		" -           -      \n";

void printLargeDigitTest() {
	std::ostringstream os;
	printLargeDigit(3, os);
	ASSERT_EQUAL(
			" - \n"
			"  |\n"
			" - \n"
			"  |\n"
			" - \n", os.str());
}

void printSingleDigitsTest() {
	std::ostringstream os;
	printLargeNumber(3, os);
	ASSERT_EQUAL(
			" -  \n"
			"  | \n"
			" -  \n"
			"  | \n"
			" -  \n", os.str());
}

void printMultipleDigitsTest() {
	std::ostringstream os;
	printLargeNumber(1234, os);
	ASSERT_EQUAL(
			"     -   -      \n"
			"  |   |   | | | \n"
			"     -   -   -  \n"
			"  | |     |   | \n"
			"     -   -      \n", os.str());
}

void printErrorTest() {
	std::ostringstream os;
	printError(os);
	ASSERT_EQUAL(ERROR_MESSAGE, os.str());
}

void printNegativeNumberTest(){
	std::ostringstream os;
	printLargeNumber(-15, os);
	ASSERT_EQUAL(
		"         -  \n"
		"      | |   \n"
		"--       -  \n"
		"      |   | \n"
		"         -  \n", os.str());
}

void printMaxSymbolsTest() {
	std::ostringstream os;
	printLargeNumber(12345678,os);
	ASSERT_EQUAL(
		"     -   -       -   -   -   -  \n"
		"  |   |   | | | |   |     | | | \n"
		"     -   -   -   -   -       -  \n"
		"  | |     |   |   | | |   | | | \n"
		"     -   -       -   -       -  \n", os.str());
}

void printMoreThanMaxSymbolsTest() {
	std::ostringstream os;
	ASSERT_THROWS(printLargeNumber(123456789,os), std::length_error);
}

void additionTest() {
	ASSERT_EQUAL(5, calc(2, 3, '+'));
	ASSERT_EQUAL(-3, calc(2, -5, '+'));
	ASSERT_EQUAL(-3, calc(-5, 2, '+'));
	ASSERT_EQUAL(std::numeric_limits<int>::max(), calc(std::numeric_limits<int>::max(),0,'+'));
	ASSERT_EQUAL(-1, calc(std::numeric_limits<int>::max(),std::numeric_limits<int>::min(),'+'));
	ASSERT_EQUAL(-1, calc(std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),'+'));
}

void subtractionTest() {
	ASSERT_EQUAL(-1, calc(2, 3, '-'));
	ASSERT_EQUAL(5, calc(2, -3, '-'));
	ASSERT_EQUAL(-5, calc( -3, 2,'-'));
	ASSERT_EQUAL(std::numeric_limits<int>::max(), calc(std::numeric_limits<int>::max(),0,'-'));
}

void multiplicationTest() {
	ASSERT_EQUAL(6, calc(2, 3, '*'));
	ASSERT_EQUAL(-6, calc(2, -3, '*'));
	ASSERT_EQUAL(-6, calc(-2, 3, '*'));
	ASSERT_EQUAL(6, calc(-2, -3, '*'));
	ASSERT_EQUAL(std::numeric_limits<int>::max(), calc(std::numeric_limits<int>::max(),1,'*'));
	ASSERT_EQUAL(0, calc(std::numeric_limits<int>::max(),0,'*'));
}

void divisionTest() {
	ASSERT_EQUAL(2, calc(6, 3, '/'));
	ASSERT_EQUAL(2, calc(5, 2, '/'));
	ASSERT_THROWS(calc(6, 0, '/'), std::logic_error);
	ASSERT_EQUAL(std::numeric_limits<int>::max(), calc(std::numeric_limits<int>::max(),1,'/'));
	ASSERT_EQUAL(std::numeric_limits<int>::min(), calc(std::numeric_limits<int>::min(),1,'/'));
	ASSERT_EQUAL(1, calc(std::numeric_limits<int>::max(),std::numeric_limits<int>::max(),'/'));
	ASSERT_EQUAL(1, calc(std::numeric_limits<int>::min(),std::numeric_limits<int>::min(),'/'));
}

void unsupportedOperatorTest() {
	ASSERT_THROWS(calc(2, 4, '!'), std::logic_error);
	ASSERT_THROWS(calc(2, 4, '('), std::logic_error);
	ASSERT_THROWS(calc(2, 4, ')'), std::logic_error);
	ASSERT_THROWS(calc(2, 4, '\\'), std::logic_error);
	ASSERT_THROWS(calc(2, 4, '?'), std::logic_error);
	ASSERT_THROWS(calc(2, 4, '&'), std::logic_error);
	ASSERT_THROWS(calc(2, 4, '|'), std::logic_error);
}

void moduloTest() {
	ASSERT_EQUAL(2, calc(17, 5, '%'));
	ASSERT_THROWS(calc(17, 0, '%'), std::logic_error);
	ASSERT_EQUAL(0, calc(std::numeric_limits<int>::max(),1,'%'));
	ASSERT_EQUAL(0, calc(std::numeric_limits<int>::max(),std::numeric_limits<int>::max(),'%'));
	ASSERT_EQUAL(5, calc(std::numeric_limits<int>::max(),std::numeric_limits<int>::max()-5,'%'));
}

void repeatedInputsTest(){
	std::ostringstream os{};
	std::istringstream is{"2 + 3 \n2+3\n3*6\n"};
	startCalc(is, os);
	ASSERT_EQUAL(
			" -  \n"
			"|   \n"
			" -  \n"
			"  | \n"
			" -  \n"
			" -  \n"
			"|   \n"
			" -  \n"
			"  | \n"
			" -  \n"
			"     -  \n"
			"  | | | \n"
			"     -  \n"
			"  | | | \n"
			"     -  \n", os.str());
}

void repeatedWrongInputsTest(){
	std::ostringstream os{};
	std::istringstream is{"2 + c \n2+3\n3*6\n"};
	startCalc(is, os);
	ASSERT_EQUAL(ERROR_MESSAGE, os.str());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(printLargeDigitTest));
	s.push_back(CUTE(printSingleDigitsTest));
	s.push_back(CUTE(printMultipleDigitsTest));
	s.push_back(CUTE(printErrorTest));
	s.push_back(CUTE(printNegativeNumberTest));
	s.push_back(CUTE(printMaxSymbolsTest));
	s.push_back(CUTE(printMoreThanMaxSymbolsTest));

	s.push_back(CUTE(additionTest));
	s.push_back(CUTE(subtractionTest));
	s.push_back(CUTE(multiplicationTest));
	s.push_back(CUTE(divisionTest));
	s.push_back(CUTE(moduloTest));
	s.push_back(CUTE(unsupportedOperatorTest));

	s.push_back(CUTE(repeatedInputsTest));
	s.push_back(CUTE(repeatedWrongInputsTest));

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}