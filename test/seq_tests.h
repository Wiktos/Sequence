#include <sstream>
#include "error_messenger.h"
#include "../source_code/sequence.h"

namespace seq_test{

    auto error_messenger = []()->ErrorMessenger&{
        return ErrorMessenger::get_instance();
    };

    void test_constructors();
    void test_push_front_and_push_back();
    void test_insert_after();
    void test_pop_back();
    void test_pop_front();
    void test_remove();
    void test_clear();
    void test_subsequence();
    void test_merge_and_binary_op();

}
