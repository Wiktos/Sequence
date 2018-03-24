#include "seq_tests.h"

using namespace std;

void seq_test::test_constructors(){
    Sequence<int, int> my_tested;
    if(!my_tested.is_empty())
        seq_test::error_messenger().report("is_empty() test constructor error");
    if(my_tested.size())
        seq_test::error_messenger().report("size() test constructor error");
}

void seq_test::test_accessing_elem_methods(){
    Sequence<int, int> my_tested;

    try{
        my_tested.front();
        seq_test::error_messenger().report("back() exception should be thrown");
    }
    catch(std::runtime_error& ex){
    }

    try{
        my_tested.back();
        seq_test::error_messenger().report("back() exception should be thrown");
    }
    catch(std::runtime_error& ex){
    }

    my_tested.push_back(1, 1);
    int head = my_tested.front();
    int tail = my_tested.back();
    if(head != tail)
        seq_test::error_messenger().report("back front wrong output");
}

void seq_test::test_push_front_and_push_back(){
    Sequence<int, int> my_tested;
    my_tested.push_back(1, 1);
    my_tested.push_back(2, 2);

    if(my_tested.is_empty())
        seq_test::error_messenger().report("is_empty() test1 pushing error");
    if(my_tested.size() != 2)
        seq_test::error_messenger().report("size() test1 pushing error");

    my_tested.push_front(3, 3);
    my_tested.push_front(4, 4);

    if(my_tested.size() != 4)
        seq_test::error_messenger().report("size() test2 pushing error");

    stringstream expected_output("4 4\n3 3\n1 1\n2 2\n");
    stringstream output_received;
    output_received << my_tested;
    if(output_received.str() != expected_output.str())
        seq_test::error_messenger().report("operator << test pushing error");
}

void seq_test::test_insert_after(){
    Sequence<int, int> my_tested;
    my_tested.push_back(1, 1);
    my_tested.push_back(2, 2);
    my_tested.push_back(3, 3);

    //lambda expression used to perform tests with correct arguments
    auto perform_correct_arg_test = [&](int loc, int new_key, int new_info, int occurrence = 1)->void{
        try{
            my_tested.insert_after(loc, new_key, new_info, occurrence);
        }
        catch(Sequence<int, int>::SequenceInvalidArgument& ex){
            seq_test::error_messenger().report("correct arg test inserting_after error");
        }
    };

    perform_correct_arg_test(1, 1, 1);
    perform_correct_arg_test(2, 1, 1);
    perform_correct_arg_test(3, 1, 1);
    perform_correct_arg_test(1, 1, 1, 3);

    //lambda expression used to perform tests with invalid arguments
    auto perform_invalid_arg_test = [&](const std::string msg, int loc, int new_key, int new_info, int occurrence = 1)->void{
        try{
            my_tested.insert_after(loc, new_key, new_info, occurrence);
            seq_test::error_messenger().report(msg);
        }
        catch(Sequence<int, int>::SequenceInvalidArgument& ex){
        }
    };

    perform_invalid_arg_test("test4 inserting_after error - occurrence", 1, 1, 1, 0);
    perform_invalid_arg_test("test5 inserting_after error - unknown loc", 5, 1, 1);
    perform_invalid_arg_test("test3 inserting_after error - invalid occurrence", 3, 1, 2, 2);
}

void seq_test::test_pop_back(){
    Sequence<int, int> my_tested;

    //basic test
    my_tested.push_back(1, 1);
    my_tested.pop_back();

    if(!my_tested.is_empty())
        seq_test::error_messenger().report("pop_back() test error - is_empty() == true");
    if(my_tested.size())
        seq_test::error_messenger().report("pop_back() test error - size() != 0");

    //test sequence's length management
    my_tested.push_back(1, 1);
    my_tested.push_back(2, 2);
    my_tested.pop_back();

    if(my_tested.size() != 1)
        seq_test::error_messenger().report("pop_back() test error - length != 1");

    //test of seq modification
    stringstream expected_output("1 1\n");
    stringstream output_received;
    output_received << my_tested;
    if(output_received.str() != expected_output.str())
        seq_test::error_messenger().report("pop_back() test error - wrong stream output");
}

void seq_test::test_pop_front(){
    Sequence<int, int> my_tested;

    //basic test
    my_tested.push_back(1, 1);
    my_tested.pop_front();

    if(!my_tested.is_empty())
        seq_test::error_messenger().report("pop_front() test error - is_empty() == true");
    if(my_tested.size())
        seq_test::error_messenger().report("pop_front() test error - size() != 0");

    //test sequence's length management
    my_tested.push_back(1, 1);
    my_tested.push_back(2, 2);
    my_tested.pop_front();

    if(my_tested.size() != 1)
        seq_test::error_messenger().report("pop_front() test error - length != 1");

    //test of seq modification
    stringstream expected_output("2 2\n");
    stringstream output_received;
    output_received << my_tested;
    if(output_received.str() != expected_output.str())
        seq_test::error_messenger().report("pop_front() test error - wrong stream output");
}

void seq_test::test_remove(){
    Sequence<int, int> my_tested;

    //basic test
    my_tested.push_back(1, 1);
    my_tested.remove(1);

    if(!my_tested.is_empty())
        seq_test::error_messenger().report("remove() test error - is_empty() == true");
    if(my_tested.size())
        seq_test::error_messenger().report("remove() test error - size() != 0");

    //test sequence's length management
    my_tested.push_back(1, 1);
    my_tested.push_back(2, 1);
    my_tested.push_back(1, 1);
    my_tested.remove(1, 2);

    if(my_tested.size() != 2)
        seq_test::error_messenger().report("remove() test error - length != 1");

    //test of seq modification
    auto test_seq_output_stream = [&](const std::string& proper_output)->void{
        stringstream expected_output(proper_output);
        stringstream output_received;
        output_received << my_tested;
        if(output_received.str() != expected_output.str())
        seq_test::error_messenger().report("remove() test error - wrong stream output");
    };

    test_seq_output_stream("1 1\n2 1\n");

    my_tested.push_back(3, 1);
    my_tested.remove(2);

    test_seq_output_stream("1 1\n3 1\n");

    //test of proper throwing exception
    auto test_throwing_except = [&](int loc, int occurence = 1)->void{
        try{
            my_tested.remove(loc, occurence);
            seq_test::error_messenger().report("test_throwing_except exception should be thrown");
        }
        catch(Sequence<int, int>::SequenceInvalidArgument& ex){
        }
    };

    test_throwing_except(0);
    test_throwing_except(3, 2);
}

void seq_test::test_clear(){
    Sequence<int, int> my_tested;
    my_tested.push_back(1, 1);
    my_tested.push_back(1, 1);
    my_tested.push_back(1, 1);
    my_tested.clear();
    if(my_tested.size())
        seq_test::error_messenger().report("clear() doesn't set lenght = 0");
}

void seq_test::test_subsequence(){
    Sequence<int, int> my_tested;

    auto test_seq_output_stream = [&](const std::string& proper_output, const Sequence<int, int>& seq)->void{
        stringstream expected_output(proper_output);
        stringstream output_received;
        output_received << seq;
        if(output_received.str() != expected_output.str())
        seq_test::error_messenger().report("subsequence() test error - wrong stream output");
    };

    Sequence<int, int> sub_sequence(my_tested.subsequence(1, 2));
    test_seq_output_stream("", sub_sequence);

    for(auto i = 0; i < 3; i++)
        my_tested.push_back(i, i);

    sub_sequence = my_tested.subsequence(1, 2);
    test_seq_output_stream("1 1\n2 2\n", sub_sequence);
}

void seq_test::test_merge_and_binary_op(){
    Sequence<int, int> my_tested;

    auto test_seq_output_stream = [&](const std::string& proper_output, const Sequence<int, int>& seq)->void{
        stringstream expected_output(proper_output);
        stringstream output_received;
        output_received << seq;
        if(output_received.str() != expected_output.str())
        seq_test::error_messenger().report("merge() test error - wrong stream output");
    };

    for(auto i = 0; i < 3; i++)
        my_tested.push_back(i, i);


    const Sequence<int, int> copied(my_tested);
    Sequence<int, int> merged_seq1 = my_tested.merge(copied);

    test_seq_output_stream("0 0\n1 1\n2 2\n0 0\n1 1\n2 2\n", merged_seq1);

    Sequence<int, int> merged_seq2 = my_tested + copied;
    test_seq_output_stream("0 0\n1 1\n2 2\n0 0\n1 1\n2 2\n", merged_seq2);

    Sequence<int, int> merged_seq3;
    merged_seq3 += my_tested;
    merged_seq3 += copied;
    test_seq_output_stream("0 0\n1 1\n2 2\n0 0\n1 1\n2 2\n", merged_seq3);
}

void seq_test::test_contain_method(){
    Sequence<int, int> my_tested;
    try{
        my_tested.contain(1, -1);
        seq_test::error_messenger().report("contain test - exception should be thrown");
    }
    catch(Sequence<int, int>::SequenceInvalidArgument& ex){
    }

    my_tested.push_back(1, 1);
    if(my_tested.contain(1, 2))
        seq_test::error_messenger().report("contain test - wrong key_occurence passed");
    if(!my_tested.contain(1, 1))
        seq_test::error_messenger().report("contain test - good key_occurence failed");
}

void seq_test::test_compare_method(){
    Sequence<int, int> first;
    Sequence<int, int> second;
    bool compare_res = first.compare(second, [](const Sequence<int, int> first, const Sequence<int, int> second) ->bool{
                        return first.size() > second.size();
                     });

    if(compare_res)
        seq_test::error_messenger().report("compare method error");
}

void seq_test::test_iterator_class(){
    Sequence<int, int> my_tested;
    Sequence<int, int>::iterator iter = my_tested.begin();
    Sequence<int, int>::const_iterator const_iter1 = my_tested.begin();

    //checking begin() return nullptr
    if(iter != nullptr || const_iter1 != nullptr)
        seq_test::error_messenger().report("iterator test !nullptr");

    my_tested.push_back(1, 1);
    //checking begin() return head
    iter = my_tested.begin();
    Sequence<int, int>::const_iterator const_iter2 = my_tested.begin();

    if(iter == nullptr || const_iter2 == nullptr)
        seq_test::error_messenger().report("iterator test =nullptr");

    //checking contain value
    Sequence<int, int>::iterator::NodeView node = *iter;
    if(node.key != 1 || node.info != 1)
        seq_test::error_messenger().report("iterator test contain value not equal to proper one");

    node.key = 3;
    Sequence<int, int>::iterator iter_bis = my_tested.begin();
    if((*iter_bis).key != 3)
        seq_test::error_messenger().report("iterator test wrong modification");

    my_tested.push_back(2, 2);
    iter++;
    if((*iter).key != 2)
        seq_test::error_messenger().report("iterator test wrong op++");

}
