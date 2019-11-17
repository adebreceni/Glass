#include <climits>
#include <type_traits>
#include <iostream>

template<class T>
static constexpr unsigned bit_size = CHAR_BIT * sizeof(T);

using u32 = unsigned;

static_assert(bit_size<u32> == 32);

template<class T>
constexpr T rotl(const T& data, unsigned n = 1){
	return (data << n) | (data >> (bit_size<T> - n) );
}

template<class T>
constexpr std::enable_if_t<(bit_size<T> <= 32), unsigned>  clz(const T& data){
	return __builtin_clz(data) - (32 - bit_size<T>);
}

template<class T>
constexpr std::enable_if_t<(bit_size<T> > 32 && bit_size<T> <= 64), unsigned> clz(const T& data){
	u32 lower = data & 0xff'ff'ff'ffU;
	u32 upper = data >> 32;
	if(upper)return __builtin_clz(upper) - (64 - bit_size<T>);
	return __builtin_clz(lower) + (bit_size<T> - 32);
}

template<class T, T (*F)(T, T, unsigned)>
int index(const T& curr, const T& next, unsigned k){
	T result = F(curr, next, k);
	if(result == 0)return -1;
	return clz(result);
}

template<class T>
T find_1(T curr, T next, unsigned k){
	while((--k != 0) && (curr != 0)){
		next = rotl(next);
		curr &= (curr << 1) | (next & 1);
	}
	return curr;
}

template<class T>
T find_2(T curr, T next, unsigned k){
	unsigned k_half;
	while(k_half = k/2, k = (k+1)/2, (k_half != 0) && (curr != 0)){
		next = rotl(next, k_half);
		curr &= (curr << k_half) | (next & ((1 << k_half) - 1));
	}
	return curr;
}

int index_1(const u32& curr, const u32& next, unsigned k){
	return index<u32, find_1<u32>>(curr, next, k);
}

int index_2(const u32& curr, const u32& next, unsigned k){
	return index<u32, find_2<u32>>(curr, next, k);
}

