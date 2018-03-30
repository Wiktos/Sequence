template <typename Key, typename Info>
std::ostream& operator<<(std::ostream& os, const Sequence<Key, Info>& seq){
    typename Sequence<Key, Info>::Node *curr = seq.head;
    while(curr){
        os << curr->key << ' ' << curr->info << '\n';
        curr = curr->next;
    }
    return os;
}

template <typename Key, typename Info>
struct Sequence<Key, Info>::Node
{
    Key key;
    Info info;
    Node *next;
};

template <typename Key, typename Info>
class Sequence<Key, Info>::SequenceInvalidArgument final : public std::invalid_argument
{
public:
    using std::invalid_argument::invalid_argument;
};

template <typename Key, typename Info>
bool Sequence<Key, Info>::operator==(const Sequence<Key, Info>& rhs) const noexcept{
    if(size() != rhs.size())
        return false;

    Node *left = head;
    Node *right = rhs.head;
    while(left){
        if(left->key != right->key || left->info != right->info)
            return false;
        left = left->next;
        right = right->next;
    }

    return true;
}

template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence<Key, Info>& rhs){
    if(this == &rhs)
        return *this;

    clear();
    Node *curr = rhs.head;
    while(curr){
        this->push_back(curr->key, curr->info);
        curr = curr->next;
    }

    return *this;
}

template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(Sequence<Key, Info>&& rhs) noexcept{
    if(this == &rhs)
        return *this;

    clear();
    head = std::move(rhs.head);
    length = std::move(rhs.length);
    rhs.head = nullptr;
    rhs.length = 0;

    return *this;
}

template <typename Key, typename Info>
Info& Sequence<Key, Info>::front() {
    if(is_empty())
            throw std::runtime_error("Empty sequence");
    return head->info;
}

template <typename Key, typename Info>
const Info& Sequence<Key, Info>::front() const {
    if(is_empty())
            throw std::runtime_error("Empty sequence");
    return head->info;
}

template <typename Key, typename Info>
Info& Sequence<Key, Info>::back() {
    if(is_empty())
        throw std::runtime_error("Empty sequence");
    Node *curr = head;
    while(curr->next)
        curr = curr->next;
    return curr->info;
}

template <typename Key, typename Info>
const Info& Sequence<Key, Info>::back() const {
    if(is_empty())
            throw std::runtime_error("Empty sequence");
    Node *curr = head;
    while(curr->next)
        curr = curr->next;
    return curr->info;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::push_front(const Key& key, const Info& info){
        if(is_empty()){
            head = new Node{key, info, nullptr};
            length++;
            return;
        }

        Node *new_elem = new Node{key, info, head};
        head = new_elem;
        length++;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::push_back(const Key& key, const Info& info){
    if(is_empty()){
        head = new Node{key, info, nullptr};
        length++;
        return;
    }

   Node *curr = head;
    while(curr->next)
        curr = curr->next;

    Node *new_elem = new Node{key, info, nullptr};
    curr->next = new_elem;
    length++;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::insert_after(const Key& loc, const Key& new_key, const Info& new_info, int key_occurence){
    if(is_empty() || key_occurence < 1)
        throw SequenceInvalidArgument("Sequence::insert_after exception");

    Node *curr = head;
    int occur_cnt = 0;
    while(curr){
        if(curr->key == loc){
            occur_cnt++;
            if(key_occurence == occur_cnt){
                Node *new_elem = new Node{new_key, new_info, curr->next};
                curr->next = new_elem;
                return;
            }
        }
        curr = curr->next;
    }

    throw SequenceInvalidArgument("Sequence::insert_after exception");
}

template <typename Key, typename Info>
void Sequence<Key, Info>::pop_front() noexcept {
    if(is_empty())
        return;

    Node *front = head;
    head = head->next;
    length--;
    delete front;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::pop_back() noexcept {
    if(is_empty())
        return;

    if(!head->next){
        delete head;
        head = nullptr;
        length--;
        return;
    }

    Node *last = head;
    while(last->next)
        last = last->next;

    Node *new_last = head;
    while(new_last->next != last)
        new_last = new_last->next;

    delete last;
    length--;
    new_last->next = nullptr;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::remove(const Key& loc, int key_occurence){
    if(is_empty() || key_occurence < 1)
        throw SequenceInvalidArgument("Sequence::remove exception");

    Node *curr = head;
    int occur_cnt = 0;
    if(head->key == loc){
        occur_cnt++;
        if(key_occurence == occur_cnt){
            head = head->next;
            delete curr;
            length--;
            return;
        }
    }

    while(curr->next){
        if(curr->next->key == loc){
            occur_cnt++;
            if(key_occurence == occur_cnt){
                Node *new_next = curr->next->next;
                delete curr->next;
                curr->next = new_next;
                length--;
                return;
            }
        }
        curr = curr->next;
    }

    throw SequenceInvalidArgument("Sequence::remove exception");
}

template <typename Key, typename Info>
void Sequence<Key, Info>::clear() noexcept{
    Node *curr = head;
    while(curr){
        head = head->next;
        delete curr;
        curr = head;
    }

    length = 0;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::contain(const Key& loc, int key_occurence) const{
    if(key_occurence < 1)
        throw SequenceInvalidArgument("Sequence::contain wrong key_occurence");

    Node *curr = head;
    int occur_cnt = 0;
    while(curr){
        if(curr->key == loc){
            occur_cnt++;
            if(key_occurence == occur_cnt)
                return true;
        }
        curr = curr->next;
    }

    return false;
}

template <typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::subsequence(const Key& loc, int size, int key_occurence) const {
    if(size < 1 || key_occurence < 1)
        throw SequenceInvalidArgument("Sequence::subsequence invalid size or key_occurence");

    //finding starting point
    Node* start = head;
    int occur_cnt = 0;
    while(start){
        if(start->key == loc){
            occur_cnt++;
            if(occur_cnt == key_occurence){
                break;
            }
        }
        start = start->next;
    }

    Sequence<Key, Info> ret_seq;
    for(int i = 0; i < size; i++){
        if(!start)
            break;
        ret_seq.push_back(start->key, start->info);
        start = start->next;
    }

    return ret_seq;
}

template <typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::subsequence(const_iterator begin, const_iterator end) const{
    Sequence<Key, Info> retv;

    while(begin != end){
        const typename iterator::NodeView node = *begin;
        retv.push_back(node.key, node.info);
        if(!begin.has_next())
            break;
        begin++;
    }
    return retv;
}

template <typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::merge(const Sequence<Key, Info> seq) const {
    Sequence<Key, Info> ret_seq(*this);

    Node *curr = seq.head;
    while(curr){
        ret_seq.push_back(curr->key, curr->info);
        curr = curr->next;
    }

    return ret_seq;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::swap(Sequence<Key, Info>& seq){
    Sequence<Key, Info> temp(*this);
    *this = seq;
    seq = temp;
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence() noexcept{
    clear();
}
