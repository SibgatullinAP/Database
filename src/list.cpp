#include "list.h"

List::~List()
{
    deleteList();
    Head = Current = Tail = nullptr;
}


void List::clear(ListNode *select)
{
    ListNode *tmp = select;
    while(select)
    {
	tmp = select;
	tmp = tmp->NextSelect;
    }
}

bool List::insert(ListNode *tmp)
{
    if(tmp == nullptr)
    {
	return false;
    }
    tmp->Next = Head;
    tmp->Previous = nullptr;
    if(Head != nullptr)
    {
	Head->Previous = tmp;
    }
    Head = tmp;

    return true;
}


ListNode * List::search(Command & command)
{
    ListNode *current = nullptr;
    ListNode *begin = nullptr;
    ListNode *end = nullptr;

    for(current = Head; current; current = current->Next)
    {
	if(command.check(current))
	{
	    break;
	}
    }
    if(current == nullptr)
    {
	return nullptr;
    }

    begin = end = current;
    for(current = current->Next; current; current = current->Next)
    {
	if(command.check(current))
	{
	    end = end->NextSelect = current;
	}
    }

    end->NextSelect = nullptr;

    return begin;
}


void List::deleteList()
{
    while(Head)
    {
	Current = Head;
	Head = Head -> Next;
	delete Current;
    }
    delete Head;
}

int List::print(FILE* outFile)
{
    ListNode *tmp = Head;

    for (int i = 0; tmp; i ++)
    {
	if(tmp != nullptr)
	{
	    tmp->print(outFile);
	}
	tmp = tmp -> Next;
    }
    tmp = nullptr;
    printf("\n");
    return 0;
}

void List::deleteHead()
{
    if(Head == nullptr)
    {
	return;
    }

    ListNode  *tmp = Head -> Next;
    if(tmp != nullptr)
    {
	tmp -> Previous = nullptr;
	Head -> ~ListNode();
	Head = tmp;
    }
    else
    {
	Head -> ~ListNode();
	Head = nullptr;
	Tail = nullptr;
    }
}

void List::deleteCurrent()
{
    if (Head == nullptr || Current == nullptr)
    {
	return;
    }
    moveFromList(Current);
    Current -> ~ListNode();
}

ListNode * List::moveFromList(ListNode  *tmp)
{
    if(tmp == nullptr)
    {
	return nullptr;
    }
    if(tmp == Head)
    {
	Head = Head->Next;
	if(Head != nullptr)
	{
	    Head->Previous = nullptr;
	}
	return tmp;
    }
    else
    {
	tmp->Previous->Next = tmp->Next;
	if(tmp->Next != nullptr)
	{
	    tmp->Next->Previous = tmp->Previous;
	}
	return tmp;
    }

    return nullptr;
}

void List::addBeforeHead(ListNode  *a)
{
    if(Head == nullptr)
    {
	addHead(a);
	return;
    }
    else
    {
	Head -> Previous = a;
	a -> Next = Head;
	Head = a;
    }
}

void List::addAfterHead(ListNode  *a)
{
    if (Head == nullptr)
    {
	addHead(a);
	return;
    }

    ListNode  *tmp = Head -> Next;
    if(tmp != nullptr)
    {
	tmp -> Previous = a;
	a -> Previous = Head;
	Head -> Next = a;
	a -> Next = tmp;
    }
    else
    {
	Head -> Next = a;
	a -> Previous = Head;
	Tail = a;
    }
}

void List::addHead(ListNode * a)
{
    a->Previous = nullptr;
    a->Next = nullptr;
    Head = Current = Tail = a;
}

ListNode * List::getHead() const
{
    return Head;
}

void List::addAfterTail(ListNode  *a)
{
    if (Tail == nullptr)
    {
	return ;
    }
    Tail -> Next = a;
    a -> Previous = Tail;
    a -> Next = nullptr;
    Tail = a;
}

void List::addLeft(ListNode  *dest, ListNode  *src)
{
    if (dest == nullptr || src == nullptr)
    {
	return;
    }
    if(dest == Head)
    {
	addBeforeHead(src);
	return;
    }
    else
    {
	src -> Next = dest;
	dest -> Previous -> Next = src;
	src -> Previous = dest -> Previous;
	dest -> Previous = src;
	return;

    }
}

void List::addRight(ListNode  *dest, ListNode  *src)
{
    if (dest == nullptr || src == nullptr)
    {
	return;
    }
    if(dest -> Previous == nullptr)
    {
	addAfterHead(src);
	return;
    }
    else if(dest -> Next == nullptr)
    {
	addAfterTail(src);
	return;
    }
    else
    {
	src -> Next = dest -> Next;
	dest -> Next = src;
	src -> Next -> Previous = src;
	src -> Previous = dest;
	return;
    }
}

bool compByName (ListNode* x, ListNode* y)
{
    return (strcmp(x->getName(), y->getName()) >= 0) ? true : false ;
}

bool compByPhone (ListNode* x, ListNode* y)
{
    return x->getPhone() >= y->getPhone();
}

bool compByGroup (ListNode* x, ListNode* y)
{
    return x->getGroup() >= y->getGroup();
}



void List::callQuickSort(bool (*comp)(ListNode *, ListNode *))
{
    quickSort(HeadSelect, HeadSelect, nullptr, nullptr, comp);
}

void List::quickSort (ListNode* head,ListNode *first, ListNode *last, ListNode *prev_first, bool (*comp)(ListNode*, ListNode*))
{
    ListNode *curr, *first_less, *first_more, *less, *more, *new_prev, *new_prev_first, *curr_prev;

    if (head == nullptr)
    {
	return;
    }
    if (first == nullptr)
    {
	return;
    }
    if (first->NextSelect == last)
    {
	return;
    }

    while (first->NextSelect != last)
    {
	first_less = less = nullptr;
	new_prev = prev_first;
	first_more = more = first;
	int length_less = 0;
	int length_more = 1;
	for (curr_prev = first, curr = first->NextSelect; curr != last; curr_prev = curr, curr = curr->NextSelect)
	{
	    if(comp(first,curr))
	    {
		if (less == nullptr)
		{
		    new_prev_first = curr_prev;
		    first_less = less = curr;
		}
		else
		{
		    less->NextSelect = curr;
		    less = curr;
		}
		length_less++;
	    }
	    else
	    {
		more->NextSelect = curr;
		more = curr;
		length_more++;
	    }
	}
	if (first_less != nullptr)
	{
	    more->NextSelect = last;
	    less->NextSelect = first_more;
	    new_prev = less;
	    if (first == HeadSelect)
	    {
		HeadSelect = first_less;
		new_prev_first = nullptr;
	    }
	    else
	    {
		prev_first->NextSelect = first_less;
		new_prev_first = prev_first;
	    }
	}
	else
	{
	    new_prev_first = new_prev;
	    first_less = first_more;
	    new_prev = first_more;
	    first_more = first_more->NextSelect;
	}
	if (length_less < length_more)
	{
	    quickSort (head, first_less, first_more, new_prev_first, comp);
	    first = first_more;
	    prev_first = new_prev;
	}
	else
	{
	    if (first_more != last && first_more->NextSelect != last)
	    {
		quickSort(head, first_more, last, new_prev, comp);
	    }
	    last = first_more;
	    first = first_less;
	    prev_first = new_prev_first;
	}
    }
  return;
}

