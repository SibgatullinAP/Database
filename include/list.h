#ifndef LIST_H
#define LIST_H

#include "listNode.h"

bool compByName (ListNode* x, ListNode* y);
bool compByPhone (ListNode* x, ListNode* y);
bool compByGroup (ListNode* x, ListNode* y);

class List
{
	private:
            ListNode  *HeadSelect = nullptr;
            ListNode  *Head = nullptr;
	    ListNode  *Tail = nullptr;
	    ListNode  *Current = nullptr;

        public:
	    friend class DataBase;
	    List ()  = default;
	    ~List ();

	    int read (FILE *fp = stdin);
	    bool insert(ListNode * tmp);
	    int print(FILE * outFile);
	    ListNode * search(Command & command);
	    void clear(ListNode *);

	    void callQuickSort(bool (*comp)(ListNode*, ListNode*));
	    void quickSort(ListNode* head,ListNode *first, ListNode *last, ListNode *prev_first, bool (*comp)(ListNode*, ListNode*));

	    void sortByName() { bool (*comp)(ListNode*, ListNode*) = compByName; callQuickSort(comp);}
	    void sortByPhone() { bool (*comp)(ListNode*, ListNode*) = compByPhone; callQuickSort(comp);}
	    void sortByGroup() { bool (*comp)(ListNode*, ListNode*) = compByGroup; callQuickSort(comp);}

	    ListNode * getHead() const;

	    void deleteList();
	    void deleteHead();
	    void deleteCurrent();

	    ListNode * moveFromList(ListNode  *a);

	    void addHead(ListNode * a);
	    void addBeforeHead(ListNode  *a);
	    void addAfterHead(ListNode  *a);

	    void addAfterTail(ListNode  *a);

	    void addLeft(ListNode  *dest, ListNode  *src);
	    void addRight(ListNode  *dest, ListNode  *src);
};

#endif
