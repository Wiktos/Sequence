#pragma once
#include "sequence.h"

template <typename Key, typename Info>
Sequence<Key, Info> shuffle(const Sequence<Key, Info>& s1, int start1, int len1,
                            const Sequence<Key, Info>& s2, int start2, int len2,
                            int repeat)
{
    Sequence<Key, Info> retv;

    if(repeat == 0)
        return retv;

    //getting value from first list
    typename Sequence<Key, Info>::const_iterator first_iter = s1.begin();

    for(int i = 0; i <= start1; i++){
        if(!first_iter.has_next())
            break;
        first_iter++;
    }

    for(int i = 0; i < len1; i++){
        if(!first_iter.has_next())
            break;
        std::pair<Key, Info> node = *first_iter;
        retv.push_back(node.first, node.second);
        first_iter++;
    }

    //getting value from second list
    typename Sequence<Key, Info>::const_iterator sec_iter = s2.begin();

    for(int i = 0; i <= start2; i++){
        if(!sec_iter.has_next())
            break;
        sec_iter++;
    }

    for(int i = 0; i < len2; i++){
        if(!sec_iter.has_next())
            break;
        std::pair<Key, Info> node = *sec_iter;
        retv.push_back(node.first, node.second);
        sec_iter++;
    }

    return retv + shuffle(s1, start1 + len1, len1,
                          s2, start2 + len2, len2,
                          repeat - 1);
}
