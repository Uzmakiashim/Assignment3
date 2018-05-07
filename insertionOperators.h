//implement the insertion operators (i.e. operator<<) for the Container class in this file
//also implement the insertion operators (i.e. operator<<) for the HashingVault class in this file
//their implementations should call the print function of the class
//hint: don't need to include any header in this file

//container class

template <typename KeyType, typename ValueType>
ostream& operator<<(ostream& os,const Container<KeyType,ValueType>&  Container_obj)
{
	Container_obj.print(os);
	return os;

}

template <typename KeyType, typename ValueType>
ostream& operator<<(ostream& os,const HashingVault <KeyType,ValueType>& Hash_Vault)
{
	Hash_Vault.print(os);
	return os;
}
