#pragma once
#include<cstdint>

template<typename F>
struct filter{

    template<typename T>
    class Iterator{
        using TBegin = decltype((*(T*)nullptr).begin());
        using TEnd   = decltype((*(T*)nullptr).end());
        using TValue = decltype((*(T*)nullptr).begin().operator*());
        struct End{};
    
        [[no_unique_address]] TBegin       _begin;
        [[no_unique_address]] TEnd   const _end;
        [[no_unique_address]] F      const _f;
    
    public:
        Iterator(T t, F f)
                : _begin{t.begin()},
                _end  {t.end()},
                _f    {f} {
            while(_begin!=_end && !_f(*_begin))
                ++_begin;
        }
        
        constexpr inline Iterator<T>&  begin() { return *this; }
        constexpr inline End         end()   { return End{}; }
    
        constexpr inline bool operator!=(End) const { return _begin!=_end; }
        constexpr inline Iterator<T>& operator++() {
            do{
                ++_begin; 
            }while(_begin!=_end && !_f(*_begin));
            return *this;
        }
        constexpr inline TValue operator*() { return *_begin; }
    };

    [[no_unique_address]] F const f;
    filter(F func) : f(func) {}
};

template<typename T, typename F>
auto operator|(T t, filter<F> thunk){
    using C = typename filter<F>::template Iterator<T>;
    return C(t, thunk.f);
}

