#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "command.h"

class List;
class DataBase;
class AVLTree;
class RedBlackTreeName;

class ListNode: public Record
{
    private:
        ListNode  *Next = nullptr;
	ListNode  *Previous = nullptr;
	ListNode *NextSelect = nullptr;

    public:
	friend class List;
	friend class DataBase;
	friend class AVLTree;
	friend class RedBlackTreeName;

	ListNode () = default;
	~ListNode() = default;

	ListNode  *getNext() const {return Next;}
	ListNode  *getPrev() const{return Previous;}
	void setNext(ListNode  *next){this -> Next = next;}
	void setPrev (ListNode  *prev){this -> Previous = prev;}

	int operator== (ListNode &x)
	{
	    if(((this->getGroup()) == (x.getGroup()))
	        && ((this->getPhone()) == (x.getPhone()))
	        && ((strcmp(this->getName(), x.getName())) == 0))
	    {
		return true;
	    }
	    return false;
	}

	friend bool compByName (ListNode* x, ListNode* y);
	friend bool compByPhone (ListNode* x, ListNode* y);
	friend bool compByGroup (ListNode* x, ListNode* y);
};

#endif
