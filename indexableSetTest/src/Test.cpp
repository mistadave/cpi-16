#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "indexableSet.h"
#include <algorithm>

indexableSet<int> createIntSet(){
	return indexableSet<int>{ 1, 2, 3, 4, 5, 6};
}

void atTest(){
	auto set = createIntSet();
	ASSERT_EQUAL(1, set.at(0));
}

void atOfConstTest(){
	auto const set = createIntSet();
	ASSERT_EQUAL(1, set.at(0));
}

void atToLargeTest(){
	auto set = createIntSet();
	ASSERT_THROWS(set.at(6), std::out_of_range);
}

void negativeAtTest(){
	auto set = createIntSet();
	ASSERT_EQUAL(5, set.at(-2));// should be index 3
}

void negativeAtEqualSetSizeTest(){
	auto set = createIntSet();
	ASSERT_EQUAL(1, set.at(-6));// should be index 0
}

void negativeAtLargerAsSetSizeTest(){
	auto set = createIntSet();
	ASSERT_THROWS(set.at(-7), std::out_of_range);
}

void backTest(){
	auto set = createIntSet();
	ASSERT_EQUAL(6, set.back());
}

void frontTest(){
	auto set = createIntSet();
	ASSERT_EQUAL(1, set.front());
}

void negativeOperatorTest(){
	auto set = createIntSet();
	ASSERT_EQUAL(set[-2], 5);
}

void operatorTest(){
	auto set = createIntSet();
	ASSERT_EQUAL(set[2], 3);
	ASSERT_EQUAL(set[4], 5);
	ASSERT_EQUAL(set[0], 1);
}

struct caselessCompare{
	bool operator() (const std::string &s1, const std::string &s2){
		return std::lexicographical_compare(
				std::begin(s1), std::end(s1), std::begin(s2), std::end(s2),
				[](char left, char right){
					return std::tolower(left) < std::tolower(right);
		});
	}// ignore case sensitive strings
};

indexableSet<std::string, caselessCompare> createStringSet(){
	return indexableSet<std::string, caselessCompare>{"Dave", "DAVE", "davE", "Michi", "MICHI", "michi"};
}

void stringSetTest(){
	auto set = createStringSet();
	ASSERT_EQUAL(2, set.size());
	auto set2 = indexableSet<std::string, caselessCompare>{"Dave", "DaVE", "Michi", "MIChi", "Hans", "hAnS", "Jan"};
	ASSERT_EQUAL(4, set2.size());
}

void beginStringSetTest(){
	auto set = createStringSet();
	ASSERT_EQUAL("Dave", set.front());
}

void endStringSetTest(){
	auto set = createStringSet();
	ASSERT_EQUAL("Michi", set.back());
}

void defaultConstructorTest(){
	indexableSet<std::string> sset;
	sset.insert("hallo");
	sset.insert("something");
	sset.insert("Nothing");
	ASSERT_EQUAL(3, sset.size());
}

void iteratorConstructorTest(){
	auto set = createStringSet();
	indexableSet<std::string> iset(set.find("Dave"), set.end());
	ASSERT_EQUAL(2, iset.size());
}

void copyConstructorTest(){
	auto set = createStringSet();
	indexableSet<std::string, caselessCompare> cset(set);
	ASSERT_EQUAL(2, cset.size());
	cset.insert("Claudio");
	ASSERT_EQUAL(3, cset.size());
}

void moveConstructorTest(){
	auto set = createStringSet();
	indexableSet<std::string, caselessCompare> mset(std::move(set));
	ASSERT_EQUAL(0, set.size());
	ASSERT_EQUAL(2, mset.size());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(atTest));
	s.push_back(CUTE(atOfConstTest));
	s.push_back(CUTE(atToLargeTest));
	s.push_back(CUTE(negativeAtTest));
	s.push_back(CUTE(negativeAtEqualSetSizeTest));
	s.push_back(CUTE(negativeAtLargerAsSetSizeTest));
	s.push_back(CUTE(negativeOperatorTest));
	s.push_back(CUTE(frontTest));
	s.push_back(CUTE(backTest));
	s.push_back(CUTE(operatorTest));
	s.push_back(CUTE(stringSetTest));
	s.push_back(CUTE(beginStringSetTest));
	s.push_back(CUTE(endStringSetTest));
	s.push_back(CUTE(defaultConstructorTest));
	s.push_back(CUTE(iteratorConstructorTest));
	s.push_back(CUTE(copyConstructorTest));
	s.push_back(CUTE(moveConstructorTest));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



