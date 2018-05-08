//submit this file
//you do NOT need to include any header in this file
//just write your BST implementation here right away

template <typename KeyType, typename ValueType>
BST<KeyType , ValueType>::BST(const BST& another)
{
	//making sure that it does not copy  a null pointer or empty tree
	if(another.root!=nullptr)
	{
		//creating a new root
		root = new BSTNode<KeyType, ValueType>(*(another.root));	//still need to figure out why there was a bug
		//root->left = another.root->left;
		//root->right = another.root->right;
		//this->size = another.size;

		//root = another.root;
	}

}

template <typename KeyType, typename ValueType>
bool BST<KeyType, ValueType>::isEmpty() const
{
	if(root==nullptr)
		return true;
	else
		return false;
}

//return the subtree that has the minimum-value node as its root node
  //return nullptr if the tree is empty
template <typename KeyType, typename ValueType>
const BST<KeyType , ValueType>* BST<KeyType, ValueType>:: findMin() const
{
	if(this->isEmpty())
	{
		return nullptr;
	}

	if(root->left.root!=nullptr)
	{
		 return root->left.findMin();
	}
	return this;
	/*
	 * Recursive way of doing this function but base is porblamatic
	if(root->left==nullptr)
	{
		return *this;	// when the left pointer is not meaning that the BST subtree is going to be sent
	}*/

	//const BSTNode<Keytype,ValueType>* node = root;
	 //BST<Keytype,ValueType>* node = this;
	//goes to the last left node which is the smallest as it  is a BST

	 //while(!node->root->left .isEmpty())
	//{
	//	node= node->root->left;
	//}

	//return node;
}



	//return the reference to the right subtree
template <typename KeyType, typename ValueType>
const BST<KeyType , ValueType>&  BST<KeyType, ValueType>::rightSubtree() const
{
	return this->root->right;
}

	//return the reference to the left subtree
template <typename KeyType, typename ValueType>
const BST<KeyType , ValueType>&  BST<KeyType, ValueType>::leftSubtree() const
{
	return this->root->left;
}

//add a node to the tree, according to the given key and value
//you have to use the exact algorithm described in the lecture notes
//you should have the exact same result as our sample output
//it should do nothing to the tree and return false when there is already a node that has the same key
//otherwise, it should add the node and return true
template <typename KeyType, typename ValueType>
bool  BST<KeyType, ValueType>::add(KeyType key, ValueType value)
 {
	if(this->isEmpty())
	{
		//condition when there are no nodes in the tree or tree is empty hence we make one
		root = new BSTNode<KeyType, ValueType>(key,value);
		//do we need to make the left and right null ptr?
		return true;
	}
	else if(this->root->data.key==key) // || this->root->left.pair.key==key)
	{
		//when a key with same value already exists
		return false;
	}
	else if (this->root->data.key>key)
	{
		return this->root->left.add(key, value);	//added return
	}
	else
	{
		return this->root->right.add(key, value);	//added return
	}
 }

//remove a node from the tree, according to the given key
//if the key is found, it should remove the node and return true
//otherwise, return false
//note: you have to use the exact algorithm described in the lecture notes
//when you need to delete a node that has 2 children,
//you must replace the deleted node with the minimum node in its right sub-tree
template <typename KeyType, typename ValueType>
bool  BST<KeyType, ValueType>::remove(KeyType key)
{

	//when key does not exist
	if(this->isEmpty())
		return false;

	//go to either left or right subtree depending on the key
	if(key > this->root->data.key)
		this->root->right.remove(key);
	else if(key < this->root->data.key)
			this->root->left.remove(key);

	//for node with two child
	else if(this->root->left.root != nullptr &&this->root->right.root != nullptr)
	{
		const BST<KeyType, ValueType>* min_tree=this->root->right.findMin();
		this->root->data = min_tree->root->data;
		this->root->right.remove(min_tree->root->data.key);
	}

	else
	{
		BSTNode<KeyType, ValueType>* node_to_delete = root;
		root = (root->left.isEmpty())? root->right.root:root->left.root;

		node_to_delete->left.root = nullptr;
		node_to_delete->right.root = nullptr;
		delete node_to_delete;
		return true;


	}

	//when key belongs to the last node and does not have any children
//	else if(this->root->left==nullptr && this->root->right==nullptr && this->root->data.key==key)
//	{
//		delete root;
//		root = nullptr;
//	}

	//when the node to delete only has one child, prevnode = current_node->next !!
//	else if((this->root->left!=nullptr || this->root->right!=nullptr) && (this->root->data.key==key))
//	{
//		if(this->root->left!=nullptr)
//		{
//			BSTNode<KeyType, ValueType>* save_node = this->root->left;
//			this->root->left= nullptr;
//			delete root;
//			root = save_node;
//			return true;
//		}
//		if(this->root->right!=nullptr)
//		{
//			BSTNode<KeyType, ValueType>* save_node = this->root->right;
//			this->root->right= nullptr;
//			delete root;
//			root = save_node;
//			return true;
//		}
//	}









}


//return the node's value given a key
//if the key is not found in the tree, refer to Container for the code that you should use
template <typename KeyType, typename ValueType>
ValueType  BST<KeyType, ValueType>:: get(KeyType key) const
{
	if(this->isEmpty())
	{
		if (typeid(ValueType) == typeid(int))
			return 0;
		else
			return ValueType();
	}
	if(root->data.key==key)
		return root->data.value;
	else if(root->data.key<key)
		return this->root->right.get(key);
	else //if(root->data.key>key)	//removed because this is the last condition so
		return this->root->left.get(key);

}

//return the number of nodes in this tree
template <typename KeyType, typename ValueType>
int BST<KeyType, ValueType>::count() const
{
	if(this->root==nullptr)
		return 0;

	return (1 + this->root->left.count() + this->root->right.count());

//	if(this->root->left->root!=nullptr)
//	{
//		return 1+ this->root->left->count();
//	}
//	if(this->root->left->root!=nullptr)
//	{
//		return 1 + this->root->right->count();
//	}
}

//return the height of this tree
//tree height is defined in the lecture notes
//also, height of an empty tree (i.e. no node at all) is 0
//and that of a single-node tree (i.e. only the root node exists) is 0
template <typename KeyType, typename ValueType>
int BST<KeyType, ValueType>::height() const
{
	if(this->isEmpty())
		return 0;
	else if(this->root->left.root==nullptr && this->root->right.root==nullptr)
		return 0;

		int left_subtree = this->root->left.height();
		int right_subtree = this->root->right.height();

		if(left_subtree>right_subtree)
			return 1+ left_subtree;
		else
			return 1+right_subtree;
}

//as described in the Container class
template <typename KeyType, typename ValueType>
const Pair<KeyType, ValueType>* BST<KeyType, ValueType>::operator[] (int n) const
{
	if(n<0 || n> (this->count()-1))
		return nullptr;


	 int number_of_nodes = this->root->left.count();

	 if(n < number_of_nodes)
		 return this->root->left.operator[](n);
	 else if(n==number_of_nodes)
		 return &(this->root->data);
	 else
		 return this->root->right.operator[](n-number_of_nodes-1);




//
//	BST<KeyType, ValueType>* new_root = new BST<KeyType,ValeType>(*this);
//	BSTNode<KeyType, ValueType>* array_of_node[this->count()];
//
//	for(int i=0;i<this->size;i++)
//	{
//	 array_of_node[i]= new BSTNode<keyType,ValueType>(new_root->findMin()->key,new_root->findMin()->Value);
//	 new_root->remove(new_root->findMin());
//	}

//	else if(n==0)
//		return &(this->root->data);
//
//	if(root->left.root!=nullptr)
//	return this->root->left.operator[](n-1);	//not sure about the returns though for this line
//
//	if(root->right.root!=nullptr)
//	return this->root->right.operator[](n-1);	//and this line



	//use an array to store all the values from min to max then use n as index and return ?
	// use total number of nodes there are then total node - n = how many times you need to traverse through

//	{
//		if(this->count() - n ==0 )
//			return &(this->root->data);
//		else if(this->root->left.root!=nullptr)
//		{
//			return this->root->left.operator[](n+1);
//		}
//		else
//		{
//			return this->root->right.operator[](n+1);
//		}
//
//
//	}
//
//	{
//		if(this->count() - n ==0)
//			return &(this->root->data);
//		else if(this->root->left.root!=nullptr)
//			return this->root->left.operator[](n+1);
//	}
//}




}








//as described in the Container class
//refer to the webpage for detailed description
template <typename KeyType, typename ValueType>
void BST<KeyType, ValueType>::print(ostream& os) const
{

	if(this->isEmpty())
		return;

	//if(this->root->left.root ==nullptr )
	//	os<<"("<<this->root.data.key<<","<<this->root->left.data.key;
	 if(this->root->left.root!=nullptr)
		this->root->left.print(os);

	os<<"("<<this->root->data.key<<","<<this->root->data.value<<")";
	//if (this->root->right.root== nullptr)
		//os<<"("<<this->root.data.key<<","<<this->root->left.data.key;
	if(this->root->right.root!=nullptr)
		this->root->right.print(os);
	else
		return ;
	/*


	if(this->root->left.root ==nullptr )
		os<<"("<<this->root->left->root.data.key<<","<<this->root->left.data.key;

	else if(this->root->left.root!=nullptr)
	{
		this->root->left.root->print(os);
	}
	os<<"("<<this->root->data.key<<","<<this->root->data.key;

	if (this->root->right.root== nullptr)
	{
		os<<"("<<this->root->left.data.key<<","<<this->root->left.data.key;

	}
	else if(this->root->right.root!=nullptr)
	{
		this->root->right.root->print(os);
	}
	else
		return ;
	 */


}

