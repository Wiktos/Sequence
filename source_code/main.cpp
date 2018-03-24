#include "../test/seq_tests.h"

int main()
{
    seq_test::test_constructors();
    seq_test::test_push_front_and_push_back();
    seq_test::test_insert_after();
    seq_test::test_pop_back();
    seq_test::test_pop_front();
    seq_test::test_remove();
    seq_test::test_clear();
    seq_test::test_subsequence();
    seq_test::test_merge_and_binary_op();
    seq_test::test_accessing_elem_methods();
    seq_test::test_contain_method();
    seq_test::test_compare_method();
    seq_test::test_iterator_class();

    seq_test::error_messenger().print_report(std::cout);
    return 0;
}
