//submit this file
//you do NOT need to include any header in this file
//just write your HashingVault implementation here right away

	//constructor
	//create the hash table
	//you can assume the table is already properly created outside (see main.cpp)
template <typename KeyType, typename ValueType>
HashingVault<KeyType,ValueType>::HashingVault(int size, Container<KeyType, ValueType>** table, int (*fun)(KeyType))
{
	this->size = size;
	this->table = table;
	this->fun = fun;


}

	//destructor
	//while the table (2d array) was created outside
	//y ou should delete the table completely here
template <typename KeyType, typename ValueType>
HashingVault<KeyType,ValueType>::~HashingVault()
{

//	if(size!=0)
//	{
 		for(int i =0;i<size;i++)
		{
			delete table[i];
			table[i]= nullptr;
		}
		delete[]table;
//	}
}

	//add (key, value) pair to the hash table and return true if the key is not already there
	//use the hash function to find which slot to add the item
	//add to the Container at that slot (i.e. table[x] where x is obtained by
	//    applying the hash function to the given key) with Container's add function
	//do nothing and return false if key already exists
template <typename KeyType, typename ValueType>
bool HashingVault<KeyType,ValueType>:: add(KeyType key, ValueType value)
{

	//firt get the hash value by putting the key to the hash function, in this case *fun. After that using that hash
	//value as an index put it in the hasing vault array where you further use BST or smartarray to solve

	//Getting hash value && all the other things are checked in add of container so we do no need to do it here
	return table[fun(key)]->add(key,value);


}

	//return the value that is associated with the key in the hash table
	//if key is not found, this function would return whatever value returned by the Container's get function for the key-not-found situation
template <typename KeyType, typename ValueType>
ValueType HashingVault<KeyType,ValueType>:: get(KeyType key) const
{
	return table[fun(key)]->get(key);
}

	//if the specified key exists, remove the item that has it and return true
	//if key is not found, this function would return false
template <typename KeyType, typename ValueType>
bool HashingVault<KeyType,ValueType>::remove(KeyType key)
{

	return table[fun(key)]->remove(key);
}

	//update the size, containers/table, and the hash function
	//put the items into the new table using the new function
	//make sure you delete the old table completely by the end
template <typename KeyType, typename ValueType>
void HashingVault<KeyType,ValueType>:: rehash(int size, Container<KeyType, ValueType>** table, int (*fun)(KeyType))
{
	if(table==nullptr)
		return;

	for(int i =0;i<size;i++)
	{
		int j = this->table[i]->count();

		for(int k = 0;k<j;k++)
		{
			const Pair<KeyType,ValueType>*  saveMe = this->table[i]->operator[](k);
			int hash_value = fun(saveMe->key);
			table[hash_value]->add(saveMe->key,saveMe->value);


		}
	}

	//deleting each containers in the table
	for(int i =0;i<this->size;i++)
	{
			delete this->table[i];

	}
	delete [](this->table);
	this->table = nullptr;

	this->size = size;
	this->fun = fun;
	this->table = table;

}

	//print the hash table, showing all items in each of the slots, to the given ostream
	//given; do not modify






































