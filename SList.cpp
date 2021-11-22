#include<iostream>
#define bool int
#define true 1
#define True 1
#define TRUE 1
#define FALSE 0
#define False 0
#define false 0
using namespace std;
class Iterator
{
private:
int releaseIteratorAfterIteration;
Iterator *iterator;
public:
Iterator()
{
this->releaseIteratorAfterIteration=1;
this->iterator=NULL;
}
Iterator(Iterator *iterator)
{
this->releaseIteratorAfterIteration=1;
this->iterator=iterator;
}
Iterator(const Iterator &other)
{
this->releaseIteratorAfterIteration=1;
this->iterator=other.iterator;
}
virtual ~Iterator()
{
if(this->releaseIteratorAfterIteration=1) delete this->iterator;
}
void setReleaseIteratorAfterIteration(int releaseIteratorAfterIteration)
{
this->releaseIteratorAfterIteration=releaseIteratorAfterIteration;
}
Iterator & operator=(const Iterator &other)
{
this->iterator=other.iterator;
return *this;
}
virtual int hasMoreElements()
{
if(iterator!=NULL) return this->iterator->hasMoreElements();
return 0;
}
virtual int next()
{
if(iterator!=NULL) return this->iterator->next();
return 0;
}
};
class Iterable
{
public:
virtual Iterator getIterator()=0;
};
class SList:public Iterable
{
public:
virtual void add(int data,bool *success)=0;
virtual int get(int index,int *success)const=0;
virtual int getSize()const=0;
virtual void insertAt(int index,int data,bool *success)=0;
virtual int removeAt(int index,int *success)=0;
virtual void update(int index,int data,int *success)=0;
virtual void removeAll()=0;
virtual void clear()=0;
};

/*The classes have:
1)default constructor(DONE)
2)parameterized constructor(DONE)
3)copy constructor(DONE)
4)operator= method(DONE)
5)operator+= method(DONE)
6)operator[] method(DONE)
7)operator +
8)virtual destructor(DONE)*/

class SArrayList:public SList
{
private:
char allocationFlag;
int **ptr;
int capacity;
int size;
int faltu;
int number[10];
bool addRow();
public:
class SArrayListIterator:public Iterator
{
int size;
int **ptr;
int index;
public:
SArrayListIterator(int **ptr,int size)
{
this->size=size;
this->index=0;
this->ptr=ptr;
}
SArrayListIterator(const SArrayListIterator &other)
{
this->index=other.index;
}
SArrayListIterator & operator=(const SArrayListIterator &other)
{
this->index=other.index;
return *this;
}
int hasMoreElements()
{
return index<size;
}
int next()
{
if(index==size) return 0;
int rowIndex=index/10;
int columnIndex=index%10;
int data=ptr[rowIndex][columnIndex];
index++;
return data;
}
};
Iterator getIterator()
{
SArrayListIterator *sArrayListIterator;
sArrayListIterator=new SArrayListIterator(this->ptr,this->size);//by default index =0(constructor)
Iterator k(sArrayListIterator);
k.setReleaseIteratorAfterIteration(0);
return k;
}
SArrayList();
SArrayList(int bufferSize);
virtual ~SArrayList();
SArrayList(const SArrayList &other);
SArrayList(const SList &other);
SArrayList & operator=(const SArrayList &other);
SArrayList & operator=(const SList &other);
void operator+=(const SArrayList &other);
void operator+=(const SList &other);
SArrayList operator+(const SArrayList &other);
SArrayList operator+(const SList &other);
int & operator[](int a);
void add(int data,bool *success);
int get(int index,int *success) const;
void insertAt(int index,int data,bool *success);
int removeAt(int index,int *success);
void removeAll();
void clear();
int getSize() const;
void update(int index,int data,int *success);
};
bool SArrayList::addRow()
{
if(capacity%100==0)
{
int numberOfPointers;
numberOfPointers=this->capacity/10;
int **tmp=new int *[numberOfPointers+10];
if(tmp==NULL) return false;
for(int e=0;e<numberOfPointers;e++) tmp[e]=this->ptr[e];
delete [] this->ptr;
this->ptr=tmp;
}
int i=this->capacity/10;
ptr[i]=new int[10];
if(this->ptr[i]==NULL) return false;
this->capacity=this->capacity+10;
return true;
}
SArrayList::SArrayList()
{
this->allocationFlag=0;
this->ptr=new int *[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
}
SArrayList::SArrayList(int bufferSize)
{
this->allocationFlag=0;
if(bufferSize<=0)
{
this->ptr=new int *[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
}
else
{
int rows;
int numberOfPointers;
rows=bufferSize/10;
if(bufferSize%10!=0) rows++;
numberOfPointers=rows+(10-(rows%10));
this->ptr=new int*[numberOfPointers];
for(int e=0;e<rows;e++)
{
this->ptr[e]=new int[10];
}
this->capacity=rows*10;
this->size=0;
}
}
SArrayList::SArrayList(const SArrayList &other) 
{
this->allocationFlag=0;
int bufferSize=other.size;
if(bufferSize<=0)
{
this->ptr=new int *[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
}
else
{
int rows;
int numberOfPointers;
rows=bufferSize/10;
if(bufferSize%10!=0) rows++;
numberOfPointers=rows+(10-(rows%10));
this->ptr=new int*[numberOfPointers];
for(int e=0;e<rows;e++)
{
this->ptr[e]=new int[10];
}
this->capacity=rows*10;
this->size=0;
}
int succ;
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
SArrayList::SArrayList(const SList &other)
{
this->allocationFlag=0;
this->ptr=new int *[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
int e;
int succ;
for(e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
SArrayList & SArrayList::operator=(const SArrayList &other)
{
if(other.allocationFlag==0)
{
this->size=0;
int succ;
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
else
{
if(this->allocationFlag==0)
{
int rows=this->capacity/10;
int j;
for(j=0;j<rows;j++)
{
delete [] this->ptr[j];
}
delete [] this->ptr;
this->ptr=other.ptr;
this->capacity=other.capacity;
this->size=other.size;
}
}
return *this;
}
SArrayList & SArrayList::operator=(const SList &other)
{
this->size=0;
int succ;
int e;
for(e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
return *this;
}
void SArrayList::operator+=(const SArrayList &other)
{
int succ;
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
void SArrayList::operator+=(const SList &other)
{
int succ;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
int & SArrayList::operator[](int index)
{
if(index<0 || index>9)
{
faltu=0;
return faltu;
}
return number[index]; 
}
SArrayList SArrayList::operator+(const SArrayList &other)
{
int succ;
SArrayList k;
for(int e=0;e<this->size;e++) k.add(this->get(e,&succ),&succ);
for(int e=0;e<other.size;e++) k.add(other.get(e,&succ),&succ);
k.allocationFlag=1;
return k;
}
SArrayList SArrayList::operator+(const SList &other)
{
int succ;
SArrayList k;
for(int e=0;e<this->size;e++) k.add(this->get(e,&succ),&succ);
for(int e=0;e<other.getSize();e++) k.add(other.get(e,&succ),&succ);
return k;
}
SArrayList::~SArrayList()
{
if(this->allocationFlag==0)
{
int rows=this->capacity/10;
int j;
for(j=0;j<rows;j++)
{
delete [] this->ptr[j];
}
delete [] this->ptr;
}
}
void SArrayList::add(int data,bool *success)
{
if(success) *success=false;
if(this->size==this->capacity)
{
if(!addRow()) return;
}
int rowIndex,columnIndex;
rowIndex=this->size/10;
columnIndex=this->size%10;
this->ptr[rowIndex][columnIndex]=data;
this->size++;
if(success) *success=true;
}
int SArrayList::get(int index,int *success) const
{
if(success) *success=false;
if(index<0 || index>=this->size) return 0;
int rowIndex=index/10;
int columnIndex=index%10;
if(success) *success=true;
return ptr[rowIndex][columnIndex];
}
void SArrayList::insertAt(int index,int data,bool *success)
{
if(success) *success=false;
if(index<0 || index>=this->size) return;
if(index==this->size)
{
this->add(data,success);
return;
}
bool succ;
int k=this->get(this->size-1,&succ);
this->add(k,&succ);
if(succ==false) return;
int j;
j=this->size-3;
while(j>=index)
{
this->update(j+1,this->get(j,&succ),&succ);
j--;
}
this->update(index,data,&succ);
if(success) *success=true;
}
int SArrayList::removeAt(int index,int *success)
{
if(success) *success=false;
if(index<0 || index>=size) return 0;
bool succ;
int data=this->get(index,&succ);
int j;
int ep=size-2;
j=index;
while(j<=ep)
{
this->update(j,this->get(j+1,&succ),&succ);
j++;
}
this->size--;
if(success) *success=true;
return data;
}
void SArrayList::removeAll()
{
this->size=0;
}
void SArrayList::clear()
{
this->size=0;
}
int SArrayList::getSize() const
{
return this->size;
}
void SArrayList::update(int index,int data,int *success)
{
if(success) *success=false;
if(index<0 || index>=size) return;
int rowIndex=index/10;
int columnIndex=index%10;
this->ptr[rowIndex][columnIndex]=data;
if(success) *success=true;
}
//SFORWARD LIST IMPLEMENTATION STARTS HERE
class SForwardList:public SList
{
class SNode
{
public:
int data;
SNode *next;
SNode()
{
this->next=NULL;
}
};
private:
SNode *start,*end;
int size;
char allocationFlag;
int faltu;
int number[10];
public:
class SForwardListIterator:public Iterator
{
SNode *ptr;
public:
SForwardListIterator()
{
this->ptr=NULL;
}
SForwardListIterator(SNode *ptr)
{
this->ptr=ptr;
}
SForwardListIterator(const SForwardListIterator &other)
{
this->ptr=other.ptr;
}
SForwardListIterator & operator=(const SForwardListIterator &other)
{
this->ptr=other.ptr;
return *this;
}
int hasMoreElements()
{
return this->ptr!=NULL;
}
int next()
{
if(this->ptr==NULL) return 0;
int data=this->ptr->data;
this->ptr=this->ptr->next;
return data;
}
};
public:
Iterator getIterator()
{
SForwardListIterator *sForwardListIterator;
sForwardListIterator=new SForwardListIterator(this->start);
Iterator k(sForwardListIterator);
k.setReleaseIteratorAfterIteration(0);
return k;
}
SForwardList();
SForwardList(int bufferSize);
SForwardList(const SForwardList &other);
SForwardList(const SList &other);
SForwardList & operator=(const SForwardList &other);
SForwardList & operator=(const SList &other);
void operator+=(const SForwardList &other);
void operator+=(const SList &other);
SForwardList operator+(const SForwardList &other);
SForwardList operator+(const SList &other);
int & operator[](int a);
void add(int data,bool *success);
int get(int index,int *success) const;
void insertAt(int index,int data,bool *success);
int removeAt(int index,int *success);
void removeAll();
void clear();
int getSize() const;
void update(int index,int data,int *success);
virtual ~SForwardList();
};
SForwardList::SForwardList()
{
this->allocationFlag=0;
this->start=NULL;
this->end=NULL;
this->size=0;
}
SForwardList::SForwardList(int bufferSize)
{
this->allocationFlag=0;
this->start=NULL;
this->end=NULL;
this->size=0;
}
SForwardList::SForwardList(const SForwardList &other) 
{
this->allocationFlag=0;
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
int succ;
for(int e=0;e<other.getSize();e++) 
{
this->add(other.get(e,&succ),&succ);
}
}
SForwardList::SForwardList(const SList &other) 
{
this->allocationFlag=0;
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
int succ;
for(int e=0;e<other.getSize();e++) 
{
this->add(other.get(e,&succ),&succ);
}
}
SForwardList & SForwardList::operator=(const SForwardList &other)
{
this->size=0;
if(allocationFlag==0)
{
this->size=other.size;
this->start=other.start;
this->end=other.end;
}
else
{
int succ;
for(int e=0;e<other.getSize();e++) 
{
this->add(other.get(e,&succ),&succ);
}
}
return *this;
}
SForwardList & SForwardList::operator=(const SList &other)
{
this->size=0;
int succ;
for(int e=0;e<other.getSize();e++) 
{
this->add(other.get(e,&succ),&succ);
}
return *this;
}
void SForwardList::operator+=(const SForwardList &other)
{
int k;
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&k),&k);
}
void SForwardList::operator+=(const SList &other)
{
int k;
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&k),&k);
}
int & SForwardList::operator[](int index)
{
if(index<0 || index>9)
{
faltu=0;
return faltu;
}
return number[index]; 
}
SForwardList SForwardList::operator+(const SForwardList &other)
{
SForwardList k;
k+=(*this);
k+=other;
return k;
}
SForwardList SForwardList::operator+(const SList &other)
{
SForwardList k;
k+=(*this);
k+=other;
return k;
}
SForwardList::~SForwardList()
{
if(this->allocationFlag==0)
{
this->clear();
}
}
void SForwardList::add(int data,bool *success)
{
if(success) *success=false;
SNode *t;
t=new SNode;
if(t==NULL) return;
t->data=data;
if(this->start==NULL)
{
this->start=this->end=t;
}
else
{
end->next=t;
end=t;
}
this->size++;
if(success) *success=true;
}
int SForwardList::get(int index,int *success)const
{
if(success) *success=false;
if(index<0 || index>=this->size) return 0;
SNode *t;
t=this->start;
for(int x=0;x<index;x++) t=t->next; 
if(success) *success=true;
return t->data; 
}
void SForwardList::insertAt(int index,int data,bool *success)
{
if(success) *success=false;
if(index<0 || index>this->size) return;
if(index==this->size)
{
this->add(data,success);
return;
}
SNode *gg;
gg=new SNode;
if(gg==NULL) return;
gg->data=data;
int x;
SNode *t,*j;
t=this->start;
for(x=0;x<index;x++)
{
j=t;
t=t->next;
}
if(t==this->start)
{
gg->next=this->start;
this->start=gg;
}
else
{
gg->next=t;
j->next=gg;
}
this->size++;
if(success) *success=true;
}
int SForwardList::removeAt(int index,int *success)
{
int data;
if(success) *success=false;
if(index<0 || index>this->size) return 0;
SNode *t,*j;
int x;
t=this->start;
for(x=0;x<index;x++)
{
j=t;
t=t->next;
}
data=t->data;
if(t==this->start && t==this->end)
{
this->start=this->end=NULL;
}
else if(t==this->start) 
{
this->start=this->start->next;
}
else if(t==this->end)
{
j->next=NULL;
this->end=j;
}
else
{
j->next=t->next;
}
this->size--;
delete t;
if(success) *success=true;
return data;
}
void SForwardList::removeAll()
{
clear();
}
void SForwardList::clear()
{
SNode *t;
while(start!=NULL)
{
t=this->start;
this->start=this->start->next;
delete t;
}
this->end=NULL;
this->size=0;
}
int SForwardList::getSize() const
{
return this->size;
}
void SForwardList::update(int index,int data,int *success)
{
if(success) *success=false;
if(index<0 || index>=this->size) return;
SNode *t;
int x;
for(t=this->start,x=0;x<index;x++,t=t->next);
t->data=data;
if(success) *success=true;
}
int main()
{
cout<<"Array list"<<endl;
SArrayList list1;
int k;
list1.add(10,&k);
list1.add(220,&k);
list1.add(330,&k);
list1.add(54540,&k);
list1.add(7540,&k);
list1.add(3520,&k);
list1.add(340,&k);
Iterator iterator1=list1.getIterator();
Iterator iterator2=list1.getIterator();
Iterator iterator3=list1.getIterator();
cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;
cout<<"---------------------------"<<endl;
cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;
cout<<"Now iterating Forward List"<<endl;
cout<<"********************************"<<endl;
SForwardList list2;
list2.add(143,&k);
list2.add(234,&k);
list2.add(5467,&k);
list2.add(5442,&k);
list2.add(876,&k);
list2.add(3520,&k);
list2.add(340,&k);
iterator1=list1.getIterator();
iterator2=list1.getIterator();
iterator3=list1.getIterator();
cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator3.next()<<endl;
cout<<"---------------------------"<<endl;
cout<<iterator1.next()<<endl;
cout<<iterator2.next()<<endl;
cout<<iterator2.next()<<endl;
return 0;
}



int ForwardListmain()
{
SArrayList list1;
bool k;
for(int x=50;x<=60;x++)
{
list1.add(x,&k);
}
SForwardList list2(list1);
for(int e=0;e<list2.getSize();e++)
{
cout<<"List 2 Elements:"<<list2.get(e,&k)<<endl;
}
list1+=list2;
cout<<"---------------------------"<<endl;
for(int e=0;e<list1.getSize();e++)
{
cout<<"List 2 Elements:"<<list1.get(e,&k)<<endl;
}
return 0;
}

int mainSArrayList()
{
SForwardList list1;
int number[10];
bool k;
for(int x=50;x<=60;x++)
{
list1.add(x,&k);
}
cout<<"Size is :: "<<list1.getSize()<<endl;
for(int e=0;e<list1.getSize();e++)
{
cout<<list1.get(e,&k)<<" ";
}
SForwardList list2(list1);
for(int x=100;x<=110;x++)
{
list2.add(x,&k);
}
cout<<endl;
cout<<"Size is :: "<<list2.getSize()<<endl;
for(int e=0;e<list2.getSize();e++)
{
cout<<list2.get(e,&k)<<" ";
}
cout<<endl;
SForwardList list3;
for(int e=900;e<=1000;e++) list3.add(e,&k);
for(int e=0;e<list3.getSize();e++) cout<<list3.get(e,&k)<<" ";
cout<<"Size is :"<<list3.getSize()<<endl;
//list3+=list2;
/*cout<<"Print list3 after the assingment+="<<endl;
for(int e=0;e<list3.getSize();e++) cout<<list3.get(e,&k)<<" ";
cout<<"Size is :"<<list3.getSize()<<endl;*/
SForwardList list4;
/*list4[0]=12345;
cout<<list4[0]<<endl;
list4[12]=987655;
cout<<list4[12]<<endl;*/
cout<<"After performing list5=list4+list3"<<endl;
SForwardList list5;
list5=list2+list3;
for(int e=0;e<list5.getSize();e++) cout<<list5.get(e,&k)<<" ";
return 0;
}