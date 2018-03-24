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
void Sequence<Key, Info>::insert_after(const Key& loc, const Key& new_key, const Info& new_info, int occurrence){
    if(is_empty() || occurrence < 1)
        throw SequenceInvalidArgument("Sequence::insert_after exception");

    Node *curr = head;
    int occur_cnt = 0;
    while(curr){
        if(curr->key == loc){
            occur_cnt++;
            if(occurrence == occur_cnt){
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
void Sequence<Key, Info>::remove(const Key& loc, int occurrence){
    if(is_empty() || occurrence < 1)
        throw SequenceInvalidArgument("Sequence::remove exception");

    Node *curr = head;
    int occur_cnt = 0;
    if(head->key == loc){
        occur_cnt++;
        if(occurrence == occur_cnt){
            head = head->next;
            delete curr;
            length--;
            return;
        }
    }

    while(curr->next){
        if(curr->next->key == loc){
            occur_cnt++;
            if(occurrence == occur_cnt){
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
        head = curr->next;
        delete curr;
        curr = head;
    }

    length = 0;
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence() noexcept{
    clear();
}
