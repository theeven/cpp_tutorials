#ifndef COPY_H
#define COPY_H

template <typename In, typename Out>
Out myCopy( In b, In e, Out r ) {
    while( b != e ) {
        *r = *b;
        ++r;
        ++b;
    }
    return r;
}

#endif
