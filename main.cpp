#include "tests.h"

int main()
{
    test::test_constructors();
    test::test_push_front_and_push_back();
    test::test_insert_after();
    test::test_pop_back();
    test::test_pop_front();
    test::test_remove();
    test::test_clear();
    test::test_subsequence();
    test::test_merge_and_binary_op();

    test::error_messenger().print_report(std::cout);

    return 0;
}
