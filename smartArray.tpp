//submit this file
//you do NOT need to include any header in this file
//just write your SmartArray implementation here right away
	//constructor: set data to nullptr and size to 0

	//Pair<KeyType, ValueType>** data; //data represents a dynamic array of pointers to dynamic Pair objects;
				//the size of the array is always just big enough to contain all the items
				//the items inside should always be sorted in ascending order of their keys
				//should point to nullptr initially

	//int size; //the exact size of the data array, i.e., the exact number of items in the array
			  //should be 0 initially
template <typename KeyType, typename ValueType>
SmartArray<KeyType , ValueType>::SmartArray():data(nullptr),size(0)
{

}

//destructor: avoid memory leak
template <typename KeyType, typename ValueType>
SmartArray<KeyType , ValueType>::~SmartArray()
{
	if(size==0)
		return;
	else
	{
	for(int i=0;i<size;i++)
	{
		delete data[i];
	}
	delete[]data;
	}


}

//if the given key already can be found in the array, do nothing and return false
//add the given (key, value) item to a proper location of the array
//(to maintain the ascending order of the keys) and return true
//for adding a new item, you will need to increase the size of the array by 1
template <typename KeyType, typename ValueType>
bool SmartArray<KeyType , ValueType>::add(KeyType key, ValueType value)
{
	if(this->data==nullptr)
		{
			Pair<KeyType , ValueType>** array_pointers = new Pair<KeyType , ValueType>* [++size];
			array_pointers[0] = new Pair<KeyType , ValueType>(key,value); //1
			this->data = array_pointers;
			return true;
		}
	else
	{
		//check if the key already exists
		for(int i =0;i<size;i++)
		{
			if(data[i]->key==key)
				return false;
		}

		//as it is a new data and the array has to be resized
		Pair<KeyType , ValueType>** array_pointers = new Pair<KeyType , ValueType>*[size+1];

		//copying from the old array
		for(int i =0;i<size;i++)
		{
			 array_pointers[i] = new Pair<KeyType , ValueType>(data[i]->key,data[i]->value); //2
		}
		delete []data;

		//adding the new key and value at the end of array
		array_pointers[size] = new Pair<KeyType , ValueType> (key,value); //3
		size++;
		this->data = array_pointers;
		//arrange the array in ascending order

		for(int i =0;i<size;i++)
		{
			for(int j= i+1;j<size;j++)
			{
				if(data[i]->key>data[j]->key)
				{
					Pair<KeyType , ValueType>* saveMe = data[i]; //4
					data[i] = data[j];
					data[j] = saveMe;
				}
				else
					continue;
			}

		}

		return true;
	}

}

	//if there exists an item with the given key, remove the item from the array and return true
	//otherwise, do nothing and return false
	//when an item is removed, you need to resize the array so that the array is just big enough to contain all the remaining items
	//hint: be careful with memory leak as you resize the array
template <typename KeyType, typename ValueType>
bool SmartArray<KeyType , ValueType>::remove(KeyType key)
{

	//check if size of tree is zer
	if(size==0)
		return false;

	//check if key already exists or not
	else
	{
		bool exist = false;
		for(int i=0;i<size;i++)
		{
			if(data[i]->key == key)
				exist = true;
		}

		if(exist)
			return false;
	}


	Pair<KeyType , ValueType>** new_array = new Pair<KeyType , ValueType>*[size-1];

	for(int i=0;i<size;i++)
	{
		if(data[i]->key!=key)
			new_array[i]=data[i];
		else
			continue;
	}

	delete data;
	return true;

}

	//return the value by the given key
	//if the key is not found in the array, refer to Container for the code that you should use
template <typename KeyType, typename ValueType>
ValueType SmartArray<KeyType , ValueType>::get(KeyType key) const
{
	bool key_found = false;
	int index ;
	for(int i =0;i<size;i++)
	{
		if(data[i]->key==key)
		{
			key_found = true;
			index=i;
		}

	}

	if((!key_found) || size==0)
	{
		if (typeid(ValueType) == typeid(int))
						return 0;
					else
						return ValueType();
	}
	else
	{
		return data[index]->value;

	}

}

	//return the number of items in the array (which is also the exact size of the array)
template <typename KeyType, typename ValueType>
int SmartArray<KeyType , ValueType>:: count() const
{
	return size;
}


//return the pointer to the pair item that has the (n+1)-th smallest key
	//for example, if n is 0, you should return the pointer to the smallest item (i.e. first smallest item)
	//for example, if n is 1, you should return the pointer to the second smallest item
	//for example, if n is the same as count()-1, you should return the pointer to the biggest item
	//if n is too small (i.e. <0) or too big, you should return nullptr
template <typename KeyType, typename ValueType>
const Pair<KeyType, ValueType>* SmartArray<KeyType , ValueType>::operator[] (int n) const
{
	if((n>(size-1)) || (n<0) || (size ==0))
		return nullptr;

	else
		return (data[n]);

}

	//as described in the Container class
	//refer to the webpage for detailed description
template <typename KeyType, typename ValueType>
void SmartArray<KeyType , ValueType>::print(ostream& os) const
{
	if(size==0)
		return;
	else
	{
		for(int i =0;i<size;i++)
			os<<"("<<data[i]->key<<","<<data[i]->value<<")";

	}

}

	//return true if the array contains an item with the specified key
	//return false otherwise
template <typename KeyType, typename ValueType>
bool SmartArray<KeyType , ValueType>::has(KeyType key) const
{
	if(size==0)
		return false;
	else
	{
		for(int i=0;i<size;i++)
		{
			if(data[i]->key == key)
				return true;
		}
		return false;
	}

}
