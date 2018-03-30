template <typename Key, typename Info>
class Sequence<Key, Info>::iterator
{
    mutable Node *it;

public:
    struct NodeView
    {
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
        NodeView retv{it->key, it->info};
        return retv;
    }

    NodeView* operator->(){
        std::unique_ptr<NodeView> retv(new NodeView{it->key, it->info});
        return retv.get();
    }

    const NodeView* operator->() const{
        std::unique_ptr<NodeView> retv(new NodeView{it->key, it->info});
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

    iterator operator++(int) const{
        iterator curr(it);
        it = it->next;
        return curr;
    }

    iterator operator++() const{
        it = it->next;
        return *this;
    }

    iterator operator+(int rhs) const{
        for(int i = 0; i < rhs; i++)
            it = it->next;

        return *this;
    }
};
