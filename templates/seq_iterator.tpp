template <typename Key, typename Info>
class Sequence<Key, Info>::iterator
{
    mutable Node *it;
public:
    iterator(Node *node) : it(node){
    }

    iterator operator=(const iterator& rhs) {
        it = rhs.it;
        return *this;
    }

    std::pair<Key*, Info*> operator*() noexcept{
        return std::make_pair(&(it->key), &(it->info));
    }
    std::pair<Key, Info> operator*() const noexcept{
        return std::make_pair(it->key, it->info);
    }

    std::pair<Key*, Info*>* operator->(){
        std::pair<Key*, Info*> retv = *this;
        return std::move(retv);
    }

    std::pair<Key, Info>* operator->() const{
        std::pair<Key, Info> retv = *this;
        return std::move(retv);
    }

    bool operator==(iterator rhs) const noexcept{
        return it == rhs.it;
    }
    bool operator!=(iterator rhs) const noexcept{
        return it != rhs.it;
    }

    bool has_next() const noexcept {
        return it->next ? true : false;
    }

    //undefine behaviour
    iterator operator++(int) const{
        iterator curr(it);
        it = it->next;
        return curr;
    }
    //undefine behaviour
    iterator operator++() const{
        it = it->next;
        return *this;
    }
    //undefine behaviour
    iterator operator+(int rhs) const{
        for(int i = 0; i < rhs; i++)
            it = it->next;

        return *this;
    }
};
