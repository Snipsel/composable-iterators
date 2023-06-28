#pragma once
#include<cstdint>

class range{
    struct End{};

    int64_t       _begin;
    int64_t const _end;
    int64_t const _step;

    static constexpr inline int64_t abs(int64_t const val){
        auto const mask = val >> 63;
        return (val ^ mask) - mask;
    }

    static constexpr inline int64_t get_step( int64_t const begin,
                                              int64_t const end,
                                              int64_t const step){
        return begin<=end? abs(step): -abs(step);
    }
    static constexpr inline int64_t get_end( int64_t const begin,
                                             int64_t const end, 
                                             int64_t const _step){
        auto const step = get_step(begin, end, _step);
        auto const iterations = (end-begin)/step;
        return begin + step*iterations;
    }
public:
    constexpr inline range(int64_t const end)
        : _begin{0},
          _end  {end},
          _step {end<0? -1: 1} {}
    constexpr inline range(int64_t const begin, int64_t const end)
        :_begin{begin},
         _end  {end},
         _step {end<begin? -1: 1} {}
    constexpr inline range(int64_t const begin, int64_t const end, int64_t const step) 
        :_begin{begin},
         _end  {get_end(begin,end, step)},
         _step {get_step(begin, end, step)} {}

    range& begin(){ return *this; }
    End     end() { return End{}; }

    constexpr inline int64_t operator*(){ return _begin; }
    constexpr inline bool operator!=(End) const {return _begin!=_end;}
    constexpr inline range& operator++() { _begin += _step; return *this;}
};

