#pragma once
#include <iostream>
#include <stdexcept>

template <typename Key, typename Info>
class Sequence
{
    struct Node;
    Node *head;
    std::size_t length;

    friend std::ostream& operator<<(std::ostream& os, const Sequence<Key, Info>& seq){
        Node *curr = seq.head;
        while(curr){
            os << curr->key << ' ' << curr->info << '\n';
            curr = curr->next;
        }
        return os;
    }

public:
    class SequenceInvalidArgument;

    Sequence() noexcept : head(nullptr), length(0)
    {}

    bool is_empty() const noexcept { return length == 0; }
    std::size_t size() const noexcept { return length; }

    //undefined behaviour for emty set
    /*Info& front() { return head->info; }
    const Info& front() const { return head->info; }
    Info& back() { return head->info; }
    const Info& back() const { return head->info; }*/

    void push_front(const Key& key, const Info& info);
    void push_back(const Key& key, const Info& info);
    void insert_after(const Key& loc, const Key& new_key, const Info& new_info, int occurrence = 1);
    void pop_front() noexcept;
    void pop_back() noexcept;
    void remove(const Key& loc, int occurrence = 1);

};

#include "sequence.tpp"
