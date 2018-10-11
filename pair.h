/*
 *  A generic key-value pair
 */

#ifndef PAIR_H_
#define PAIR_H_


template <typename KeyType, typename ValueType>
struct Pair
{
	KeyType key;
	ValueType value;
	Pair(KeyType k, ValueType v) : key(k), value(v) {};
};

#endif /* PAIR_H_ */
