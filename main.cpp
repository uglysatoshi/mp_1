#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

struct CList
{
	int info;
	CList * pnext;
};
typedef struct CList *pCList;

struct CTree
{
	int info;
	CTree *pleft, *pright;
};
typedef struct CTree *pCTree;

struct CList2
{
	int info;
	CList2 * pnext;
};
typedef struct CList2 *pCList2;

void AddToTree (pCList2 & head, int info)
{
	CList2 * pnew = new CList2();
	pnew -> info = info;
	pnew -> pnext = head;
	head = pnew;
}

int ListCount(pCList2 head)
{
	int res = 0;
	CList2 * p = head;
	while(p != NULL)
	{
		p = p -> pnext;
		res++;
	}
	return res;
}

int TreeCount(pCTree root)
{
	int res = 0;
	CTree * p = root;
	while(p != NULL)
	{
		p = p -> pleft;
		res++;
	}
	return res;
}

void CreateTree(pCList2 & headCopy, pCTree & root, int listCount)
{
	if (listCount == 0 || headCopy == NULL){
		root = NULL;
		return;
	}
	if (listCount < 0)
		listCount = ListCount (headCopy);
	root = new CTree;
	root->info = headCopy->info;
	headCopy = headCopy->pnext;
	CreateTree (headCopy, root->pleft,
	listCount / 2); 
	CreateTree (headCopy, root->pright,
	listCount - (listCount / 2) - 1);
}

void CreateTreeByList (pCList2 head, pCTree & root)
{
if (head == NULL){
 root = NULL;
 return;
}
pCList2 headCopy = head;
CreateTree (headCopy, root, ListCount(headCopy));
}

void AddToList (pCList & head, int info)
{
	CList * pnew = new CList();
	pnew -> info = info;
	pnew -> pnext = head;
	head = pnew;
}

void AvgListResource(pCList head, double &sum, int &count)
{
	if (head == NULL)
	 return;
	sum = sum + head ->info;
	count ++;
	AvgListResource(head->pnext, sum, count);
}

double AvgList(pCList head)
{	
	double sum = 0;
	int count = 0;
	AvgListResource(head, sum, count);
	if (count > 0)
		sum = sum / count;
	return sum;

}

void DisposeList (pCList & head)
{
	pCList p;
	while (head != NULL)
	{
		p = head -> pnext;
		delete head;
		head = p;
	}
}

void DisposeList2 (pCList2 & head)
{
	pCList2 p;
	while (head != NULL)
	{
		p = head -> pnext;
		delete head;
		head = p;
	}
}

void DisposeTree (pCTree & root)
{
if (root == NULL)
 return;
DisposeTree (root->pleft);
DisposeTree (root->pright);
delete root;
root = NULL;
}

void instr()
{
	cout << "1 - Enter a list" << endl;
	cout << "2 - Output the average value of the list" << endl;
	cout << "3 - Enter a tree" << endl;
	cout << "4 - Output the length of the largest branch of the tree" << endl;
	cout << "0 - Exit" << endl;
}

int main (int argc, char *argv[])
{
	pCList list = 0;
	pCList2 list2 = 0;
	pCTree TreeRoot = NULL;
	int cnt, info, cnt2, info2, choise;
	instr();

	do
	{
		cout << "Select a menu item: ";
		cin >> choise;
		switch (choise)
		{
		case 1:
			cout << "Enter the size of the list: ";
			cin >> cnt;
			for (int i = 0; i<cnt; i++)
			{
				cout << "Enter an element: ";
				cin >> info;
				AddToList(list, info);
			}
			break;
		case 2:
			cout << "The average value of the list is " << AvgList(list) << endl;
			break;
		case 3:
			cout << "Enter the number of tree elements: ";
			cin >> cnt2;
			for (int i = 0; i<cnt2; i++)
			{
				cout << "Enter an element: ";
				cin >> info2;
				AddToTree(list2, info2);
			}
			CreateTreeByList(list2, TreeRoot);
			break;
		case 4:
			cout <<"Length of the largest tree branch is "<< TreeCount(TreeRoot) << endl;
			break;
		}
	}
	while (choise != 0);

	DisposeList(list);
	DisposeList2(list2);
	DisposeTree(TreeRoot);
	return 0;
}