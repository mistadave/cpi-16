#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "Word.h"
#include "kwic.h"

void outWordTest(){
	std::ostringstream os{};
	Word w{"Friendly"};
	os << w;
	ASSERT_EQUAL("Friendly", os.str());
}

void constructorNonAlphaTest(){
	ASSERT_THROWS(Word{"Abc123"},std::invalid_argument);
	ASSERT_THROWS(Word{"123"},std::invalid_argument);
	ASSERT_THROWS(Word{" "},std::invalid_argument);
	ASSERT_THROWS(Word{"ab3c"},std::invalid_argument);
	ASSERT_THROWS(Word{"ab!c"},std::invalid_argument);
	ASSERT_THROWS(Word{"ab c"},std::invalid_argument);
	ASSERT_THROWS(Word{"H3ll0"},std::invalid_argument);
	ASSERT_THROWS(Word{""},std::invalid_argument);
}

void compareTest(){
	Word w1{"Hello"};
	Word w2{"airplane"};
	Word w3{"home"};
	ASSERT(w2 < w1);
	ASSERT(w2 < w3);
	ASSERT(w1 < w3);
}

void inputMultipleWordsTest() {
	std::ostringstream os{};
	std::istringstream is{"monday01 asdf"};
	Word w1, w2;
	is >> w1 >> w2;
	os << w1 << " " << w2;
	ASSERT_EQUAL("monday asdf", os.str());
}

void inputSentenceTest(){
	std::istringstream is{"this is a test\n"};
	Sentence s{};
	is >> s;
	ASSERT_EQUAL(4, s.size());
}

void outputSentenceTest(){
	std::ostringstream os{};
	Sentence s{Word{"Monday"},Word{"Tuesday"}, Word{"Friday"}};
	os << s;
	ASSERT_EQUAL("Monday Tuesday Friday ", os.str());
}

void kwicTestSentence() {
	std::ostringstream os{};
	std::istringstream is{"this is a test\nthis is another test\n"};
	std::cout << "Hello";
	os << "out";
	kwic(is, os);
	ASSERT_EQUAL("compl, tely, weird, matted, in, put", os.str());
}

void kwicTest(){
	std::istringstream is{"A B C D E \n C Plus Plus"};
	std::ostringstream os{};
	kwic(is, os);
	ASSERT_EQUAL("A B C D E \nB C D E A \nC D E A B \nC Plus Plus \nD E A B C \nE A B C D \nPlus C Plus \nPlus Plus C \n" , os.str());
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(outWordTest));
	s.push_back(CUTE(constructorNonAlphaTest));
	s.push_back(CUTE(inputMultipleWordsTest));
	s.push_back(CUTE(kwicTest));
	s.push_back(CUTE(compareTest));
	s.push_back(CUTE(inputSentenceTest));
	s.push_back(CUTE(outputSentenceTest));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



