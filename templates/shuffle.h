#pragma once
#include "sequence.h"

bool check_shuffle_argument(int start1, int len1, int start2, int len2){
    return (start1 >= 0) && (len1 >= 0) && (start2 >= 0) && (len2 >= 0);
}

template <typename Key, typename Info>
Sequence<Key, Info> shuffle(const Sequence<Key, Info>& s1, int start1, int len1,
                            const Sequence<Key, Info>& s2, int start2, int len2,
                            int repeat)
{
    Sequence<Key, Info> retv;

    if(!check_shuffle_argument(start1, len1, start2, len2))
        return retv;

    if(repeat <= 0)
        return retv;

    //getting value from first list
    if(static_cast<unsigned int>(start1 + len1) <= s1.size())
        retv += s1.subsequence(s1.begin() + start1, s1.begin() + (start1 + len1));
    else{
        if(static_cast<unsigned int>(start1) < s1.size())
            retv += s1.subsequence(s1.begin() + start1, s1.begin() + s1.size());
    }

    //getting value from second list
    if(static_cast<unsigned int>(start2 + len2) <= s2.size())
        retv += s1.subsequence(s2.begin() + start2, s2.begin() + (start2 + len2));
    else{
        if(static_cast<unsigned int>(start2) < s2.size())
            retv += s1.subsequence(s2.begin() + start2, s2.begin() + s2.size());
    }

    return retv + shuffle(s1, start1 + len1, len1,
                          s2, start2 + len2, len2,
                          repeat - 1);
}
