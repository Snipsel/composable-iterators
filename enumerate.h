#pragma once
#include<cstdint>

struct enumerate{
    template<typename T>
    class Iterator{
        using TBegin = decltype((*(T*)nullptr).begin());
        using TEnd   = decltype((*(T*)nullptr).end());
        using TValue = decltype((*(T*)nullptr).begin().operator*());
        struct End{};
        struct Pair{
            int64_t i;
            TValue  v;
        };
    
        int64_t _count;
        [[no_unique_address]] TBegin  _begin;
        [[no_unique_address]] TEnd    _end;
    public:
        Iterator(T t)
            :_count{ 0 },
            _begin{ t.begin() },
            _end  { t.end()   } {}
        
        constexpr inline Iterator<T>& begin() { return *this; }
        constexpr inline End          end()   { return End{}; }
    
        constexpr inline bool operator!=(End) const { return _begin!=_end; }
        constexpr inline Iterator<T>& operator++() { ++_count; ++_begin; return *this; }
        constexpr inline Pair operator*() { return Pair{ _count, *_begin }; }
    };
};

template<typename T>
enumerate::Iterator<T> operator|(T t, enumerate thunk){
    return enumerate::Iterator(t);
}

