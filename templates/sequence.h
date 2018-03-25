#pragma once
#include <stdexcept>
#include <functional>

template <typename Key, typename Info>
class Sequence
{
    //private member types
    struct Node;
    Node *head;
    std::size_t length;

    //output stream operator
    template <typename K, typename I>
    friend std::ostream& operator<<(std::ostream& os, const Sequence<K, I>& seq);

public:
    //public member types
    class SequenceInvalidArgument;
    class iterator;
    typedef const iterator const_iterator;

    //constructors
    Sequence() noexcept : head(nullptr), length(0)
    {}
    Sequence(const Sequence<Key, Info>& source) : head(nullptr){
        *this = source;
    }
    Sequence(Sequence<Key, Info>&& source) : head(nullptr){
        *this = source;
    };

    //operators
    Sequence<Key, Info>& operator=(const Sequence<Key, Info>& rhs);
    Sequence<Key, Info>& operator=(Sequence<Key, Info>&& rhs);
    Sequence<Key, Info> operator+(const Sequence<Key, Info>& rhs) const{
        return this->merge(rhs);
    }
    Sequence<Key, Info>& operator+=(const Sequence<Key, Info>& rhs){
        *this = *this + rhs;
        return *this;
    }

    //compare operations
    bool operator==(const Sequence<Key, Info>& rhs) const noexcept;
    bool operator!=(const Sequence<Key, Info>& rhs) const noexcept {
        return !(*this == rhs);
    }
    bool compare(const Sequence<Key, Info>& rhs, std::function<bool(const Sequence<Key, Info>&, const Sequence<Key, Info>&)> comparator){
        return comparator(*this, rhs);
    }
    bool contain(const Key& loc, int key_occurence = 1) const;

    //element access
    Info& front();
    const Info& front() const;
    Info& back();
    const Info& back() const;

    //iterators
    iterator begin(){
        return head ? iterator(head) : nullptr;
    }
    const_iterator begin() const {
        return head ? iterator(head) : nullptr;
    }

    //capacity
    bool is_empty() const noexcept { return length == 0; }
    std::size_t size() const noexcept { return length; }

    //modifiers
    void push_front(const Key& key, const Info& info);
    void push_back(const Key& key, const Info& info);
    void insert_after(const Key& loc, const Key& new_key, const Info& new_info, int key_occurence = 1);
    void pop_front() noexcept;
    void pop_back() noexcept;
    void remove(const Key& loc, int key_occurence = 1);
    void clear() noexcept;
    void swap(Sequence<Key, Info>& seq);

    //operations
    Sequence<Key, Info> subsequence(const Key& loc, int size, int key_occurence = 1) const;
    Sequence<Key, Info> subsequence(const_iterator begin, const_iterator end) const;
    Sequence<Key, Info> merge(const Sequence<Key, Info> seq) const;

    ~Sequence() noexcept;
};

#include "sequence.tpp"
#include "seq_iterator.tpp"
