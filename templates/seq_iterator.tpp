template <typename Key, typename Info>
class Sequence<Key, Info>::iterator
{
    mutable Node *it;
public:
    struct NodeView{
        Key& key;
        Info& info;
    };

    iterator(Node *node) : it(node){
    }

    iterator operator=(const iterator& rhs) {
        it = rhs.it;
        return *this;
    }

    NodeView operator*() noexcept{
        NodeView retv{it->key, it->info};
        return retv;
    }
    const NodeView operator*() const noexcept{
        const NodeView retv{it->key, it->info};
        return retv;
    }

    NodeView* operator->(){
        NodeView retv{it->key, it->info};
        return &retv;
    }

    const NodeView* operator->() const{
        NodeView retv{it->key, it->info};
        return &retv;
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
