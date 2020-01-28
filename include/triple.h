#ifndef TRIPLE_H
#define TRIPLE_H

namespace pathfinder
{
template <class T1, class T2, class T3> struct triple
{
    typedef T1 first_type;///<type def for first component of triple
    typedef T2 second_type;///<type def for first component of triple
    typedef T3 third_type;///<type def for first component of triple

    T1 first;///<first component of the triple
    T2 second;///<second component of the triple
    T3 third;///<third component of the triple
    triple() : first(T1()), second(T2()), third(T3()) {}///<constructor
    triple(const T1& x, const T2& y, const T3& z) : first(x), second(y), third(z) {}///<constructor
    template <class U, class V, class W>
    triple(const triple<U, V, W> &t) : first(t.first), second(t.second), third(t.third) { }///<constructor
};
}

#endif //TRIPLE_H
