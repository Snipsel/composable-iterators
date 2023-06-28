#pragma once
#include<cstdint>

/* fold
usage:
    it | fold( initial_value, func )
*/
template<typename R, typename F>
struct fold{
    [[no_unique_address]] R init;
    [[no_unique_address]] F f;
    fold(R in, F func)
        : init(in), f(func){}
};
template<typename T, typename R, typename F>
R operator|(T it, fold<R,F> thunk) {
    R ret = thunk.init;
    for(auto&& x: it){
        ret = thunk.f(ret, x);
    }
    return ret;
}

