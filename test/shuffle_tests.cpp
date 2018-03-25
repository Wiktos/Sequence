#include <sstream>

#include "shuffle_tests.h"
#include "seq_tests.h"
#include "../templates/shuffle.h"
#include "../templates/sequence.h"


void shuffle_test::test_check_param_method(){
    if(!check_shuffle_argument(1, 1, 1, 1))
       seq_test::error_messenger().report("test check shuffle argument - correct test");
    if(!check_shuffle_argument(0, 0, 0, 0))
       seq_test::error_messenger().report("test check shuffle argument - correct test");
    if(!check_shuffle_argument(12, 321, 12, 8765))
       seq_test::error_messenger().report("test check shuffle argument - correct test");
}

void shuffle_test::test_shuffle_method(){
    Sequence<int, int> s1;
    for(int i = 1; i < 9; i++)
        s1.push_back(i, i);

    Sequence<int, int> s2;
    for(int i = 1; i < 13; i++)
        s2.push_back(i * 10, i * 10);

    Sequence<int, int> s3 = shuffle(s1, 0, 1, s2, 2, 1, 3);
    std::stringstream expected("1 1\n30 30\n2 2\n40 40\n3 3\n50 50\n");
    std::stringstream output;
    output << s3;
    if(output.str() != expected.str())
        seq_test::error_messenger().report("test shuffle method failed");
}
