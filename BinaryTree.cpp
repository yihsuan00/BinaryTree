#include "BinaryTree.h"

using namespace std;

template<typename K, typename V>
BinaryTree<K, V>::BinaryTree() {
	makeEmpty();
}

/**
*  Returns the number of entries stored in the dictionary.  Entries with
*  the same key (or even the same key and value) each still count as
*  a separate entry.
*  @return number of entries in the dictionary.
**/
template<typename K, typename V>
int BinaryTree<K, V>::size() {
	return tsize;
}

/**
*  Tests if the dictionary is empty.
*
*  @return true if the dictionary has no entries; false otherwise.
**/
template<typename K, typename V>
bool BinaryTree<K, V>::isEmpty() {
	return size() == 0;
}

template<typename K, typename V>
void BinaryTree<K, V>::insertHelper(Entry<K, V>* entry, const K& key, BinaryTreeNode<K, V>* node) {
	if (key.compareTo(node->entry->getkey()) <= 0) {
		if (node->leftChild == NULL) {
			node->leftChild = new BinaryTreeNode<K, V>(entry, node);
		}
		else {
			insertHelper(entry, key, node->leftChild);
		}
	}
	else {
		if (node->rightChild == NULL) {
			node->rightChild = new BinaryTreeNode<K, V>(entry, node);
		}
		else {
			insertHelper(entry, key, node->rightChild);
		}
	}
}

/**
*  Create a new Entry object referencing the input key and associated value,
*  and insert the entry into the dictionary.
*  Multiple entries with the same key (or even the same key and
*  value) can coexist in the dictionary.
*
*  @param key the key by which the entry can be retrieved.
*  @param value an arbitrary object.
**/
template<typename K, typename V>
void BinaryTree<K, V>::insert(const K& key, const V& value) {
	Entry<K, V>* entry = new Entry<K, V>(key, value);
	if (root == NULL) {
		root = new BinaryTreeNode<K, V>(entry);
	}
	else {
		insertHelper(entry, key, root);
	}
	tsize++;
}

/**
*  Search for a node with the specified key, starting from "node".  If a
*  matching key is found (meaning that key1.compareTo(key2) == 0), return
*  a node containing that key.  Otherwise, return null.
*
*  Be sure this method returns null if node == null.
**/
template<typename K, typename V>
BinaryTreeNode<K, V>* BinaryTree<K, V>::findHelper(const K& key, BinaryTreeNode<K, V>* node) {
	if (node == NULL)
		return NULL;

	else
	{
		while (node != NULL) {
			if (key.compareTo(node->entry->getkey()) == 0)
				return node;
			else if (key.compareTo(node->entry->getkey()) < 0)
			{
				node = node->leftChild;
			}
			else
			{
				node = node->rightChild;
			}

		}

	}

}

/**
*  Search for an entry with the specified key.  If such an entry is found,
*  return true; otherwise return false.
*
*  @param key the search key.
*  @return an entry containing the key and an associated value, or null if
*          no entry contains the specified key.
**/
template<typename K, typename V>
Entry<K, V>* BinaryTree<K, V>::find(const K& key) {
	BinaryTreeNode<K, V>* node = findHelper(key, root);
	if (node != NULL) {
		return node->entry;
	}
	else {
		return NULL;
	}
}

/**
*  Remove an entry with the specified key.  If such an entry is found,
*  remove it from the table.
*  If several entries have the specified key, choose one arbitrarily, then
*  remove it.
*
*  @param key the search key.
*/
template<typename K, typename V>
void BinaryTree<K, V>::remove(const K& key) {
	BinaryTreeNode<K,V>* node= findHelper(key, root);
	if (node != NULL)
	{
		if (node->leftChild == NULL&&node->rightChild == NULL)
		{
			if (node->parent != NULL)
			{
				if (key.compareTo(node->parent->entry->getkey()) >= 0)
				{
					node->parent->rightChild = NULL;
				}
				else
				{
					node->parent->leftChild = NULL;
					root = NULL;
				}
			}
			delete node;
			node = NULL;
			tsize--;
		}
	  else if (node->leftChild != NULL&&node->rightChild != NULL)
		{
			BinaryTreeNode<K, V>* a = node->rightChild->findmin(node->rightChild);
			if (a != NULL)
			{
			
				if (a->rightChild != NULL)
				{
					a->rightChild->parent = a->parent;
					a->parent->leftChild = a->rightChild;
				}
				
				if (node->parent != NULL)
				{
					node->leftChild->parent = a;
					node->rightChild->parent = a;
					a->leftChild = node->leftChild;
					a->rightChild = node->rightChild;
					if (key.compareTo(node->parent->entry->getkey()) >= 0)
					{
						node->parent->rightChild = a;
					}
					else
					{
						node->parent->leftChild = a;
					}
					node->parent = a->parent;
				}
				else
				{
					a->parent = NULL;
					root = a;
					root->rightChild = node->rightChild;
					root->leftChild = node->leftChild;
					node->leftChild->parent = root;
					node->rightChild->parent = root;
				}
				delete node;
				node = NULL;
				tsize--;
			}
			if (a == NULL&&node->rightChild != NULL)
			{
				if (node->parent != NULL)
				{
					node->leftChild->parent = node->rightChild;
					node->rightChild->leftChild = node->leftChild;
					if (key.compareTo(node->parent->entry->getkey()) >= 0)
					{
						node->parent->rightChild = node->rightChild;
					}
					else
					{
						node->parent->leftChild = node->rightChild;
					}
					node->parent = node->rightChild->parent;
				}
				else
				{
					node->rightChild->parent = NULL;
					root = node->rightChild;
					node->leftChild->parent = root;
					root->leftChild = node->leftChild;
					root->rightChild = NULL;
				}
				delete node;
				node = NULL;
				tsize--;

			}


		}
		else
		{
			if (node->leftChild != NULL)
			{
				if (node->parent != NULL)
				{
					node->leftChild->parent = node->parent;
					if (key.compareTo(node->parent->entry->getkey()) >= 0)
					{
						node->parent->rightChild = node->leftChild;
					}
					else
					{
						node->parent->leftChild = node->leftChild;
					}
				}
				else
				{
					node->leftChild->parent=NULL;
					root = node->leftChild;
				}
				delete node;
				node = NULL;
				tsize--;
			}
			else {
				if (node->parent != NULL)
				{
					node->rightChild->parent = node->parent;
					if (key.compareTo(node->parent->entry->getkey()) >= 0)
					{
						node->parent->rightChild = node->rightChild;
					}
					else
					{
						node->parent->leftChild = node->rightChild;
					}
				}
				else
				{
					node->rightChild->parent = NULL;
					root = node->rightChild;
				}
				delete node;
				node = NULL;
				tsize--;
			}

		}

	}

	// Your solution here.*/
}


/**
*  Remove all entries from the dictionary.
*/
template<typename K, typename V>
void BinaryTree<K, V>::makeEmpty() {
	if (isEmpty())
	{
		return;
	}
	else
	{
		BinaryTreeNode<K, V> *current = root;
		while (current != NULL)
		{
			BinaryTreeNode<K, V> *temp = root->rightChild->findmin(root->rightChild) ;
			if (temp == NULL)
			{
				temp = current->leftChild;
			}
			remove( current->entry->getkey());
			current = temp;
		
		}

	}
	// Your solution here.
	;
}

/**
*  Convert the tree into a string.
**/
template<typename K, typename V>
std::string BinaryTree<K, V>::toString() {
	if (root == NULL) {
		return "";
	}
	else {
		return root->toString();
	}
}