#include <word.h>
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "kwic.h"

void inWithNumberTest() {

	Word w{};
	std::istringstream is {"123Te3st= tada"};
	is >> w;
	ASSERT_EQUAL(Word("Te"), w);
}

void inWordAtEndTest() {
	Word w{};
	std::istringstream is {"125? Hey"};
	is >> w;
	ASSERT_EQUAL(Word("Hey"), w);
}

void noWordFoundTest() {
	Word w{};
	std::istringstream is {"123£( "};
	is >> w;
	ASSERT(is.fail());
}

void wordConstructorExceptionTest(){
	ASSERT_THROWS(Word{"Abc123"},std::invalid_argument);
	ASSERT_THROWS(Word{"123"},std::invalid_argument);
	ASSERT_THROWS(Word{" "},std::invalid_argument);
	ASSERT_THROWS(Word{"ab3c"},std::invalid_argument);
	ASSERT_THROWS(Word{"ab!c"},std::invalid_argument);
	ASSERT_THROWS(Word{"ab c"},std::invalid_argument);
	ASSERT_THROWS(Word{"H3ll0"},std::invalid_argument);
	ASSERT_THROWS(Word{""},std::invalid_argument);
	ASSERT_THROWS(Word{"!%)?"},std::invalid_argument);
}

void outWordTest(){
	std::ostringstream os{};
	Word w{"Friendly"};
	os << w;
	ASSERT_EQUAL("Friendly", os.str());
}

void caseInsetiveTest() {
	ASSERT(Word("Hallo")==Word("hallo"));
}

void readLineTest(){
	std::istringstream is{"kwic is here"};
	kwic(is, std::cout);
}

void compareTest(){
	Word w1{"alpha"};
	Word w2{"Hello"};
	Word w3{"house"};
	ASSERT(w1 < w2);
	ASSERT(w1 < w3);
	ASSERT(w2 < w3);
}

void kwicTest(){
	std::istringstream is{"A B C D \n C Plus Plus"};
	std::ostringstream os{};
	kwic(is, os);
	ASSERT_EQUAL("A B C D \nB C D A \nC D A B \nC Plus Plus \nD A B C \nPlus C Plus \nPlus Plus C \n" , os.str());
}

void kwicSentenceTest(){
	std::istringstream is{"this is a test\n this is another test"};
	std::ostringstream os{};
	kwic(is, os);
	ASSERT_EQUAL("a test this is \nanother test this is \nis a test this \nis another test this \ntest this is a \ntest this is another \nthis is a test \nthis is another test \n" , os.str());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	s.push_back(CUTE(inWithNumberTest));
	s.push_back(CUTE(inWordAtEndTest));
	s.push_back(CUTE(noWordFoundTest));
	s.push_back(CUTE(wordConstructorExceptionTest));
	s.push_back(CUTE(outWordTest));
	s.push_back(CUTE(caseInsetiveTest));
	s.push_back(CUTE(readLineTest));
	s.push_back(CUTE(compareTest));
	s.push_back(CUTE(kwicTest));
	s.push_back(CUTE(kwicSentenceTest));

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}
