#include <iostream>
#include <map>

using namespace std;

#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

template <typename...> class Node;
template <typename...> class Cache;

template <typename AddrType, typename DataType>
class Node <AddrType, DataType>
{
  typedef map<AddrType, DataType> MemType;
public:
  Node (AddrType addr, DataType data):
    addr (addr), data (data), prev (NULL), next (NULL) {}

  Node *prev;
  Node *next;

  AddrType addr;
  DataType data;
};

template <typename AddrType, typename DataType>
class Cache <AddrType, DataType>
{
  typedef map<AddrType, DataType> MemType;
public:
  Cache (): head (NULL), num (0) {};

  DataType readData (AddrType addr);
  void writeData (AddrType addr, DataType data);
  void setMemory (MemType *mem) {mainMem = mem;}
  void dumpCache ();

private:
  void findGetNode (AddrType addr);
  DataType fetchMemory (AddrType addr);
  MemType *mainMem;

  const int size = 10;
  map <AddrType, int> cacheMap;
  int num;

  Node<AddrType, DataType> *head;
};

template <typename AddrType, typename DataType>
DataType Cache<AddrType, DataType>::fetchMemory (AddrType addr)
{
  if (mainMem->find (addr) == mainMem->end ())
    {
      cout << "invalid address: " << addr << endl;
      return 0;
    }
  else
    {
      D (cout << "fetch from mainMem" << endl;)
      return (*mainMem)[addr];
    }
}

template <typename AddrType, typename DataType>
void Cache<AddrType, DataType>::findGetNode (AddrType addr)
{
  Node<AddrType, DataType> *node;
  D (cout << "search cache " << addr << endl;)
  if (cacheMap.find (addr) == cacheMap.end ())
    {
      D (cout << "Not in cache " << addr << endl;)
      DataType val = fetchMemory (addr);
      node = new Node<AddrType, DataType> (addr, val);

      if (num >= size)
	{
	  Node<AddrType, DataType> *tmp = head;
	  while (tmp->next != NULL)
	    tmp = tmp->next;
	  tmp->prev->next = NULL;
	  (*mainMem)[tmp->addr] = tmp->data;
	  D (cout << "Exempt LRU item " << tmp->addr << ":"
	    << tmp->data << " into main memory" << endl;)
	  delete tmp;
	  --num;
	}
      num++;
    }
  else
    {
      D (cout << "found in cache " << addr << endl;)
      node = head;
      while (node != NULL)
	{
	  if (node->addr == addr)
	    break;
	  node = node->next;
	}
      // Remove it from the list
      if (node->prev != NULL)
	node->prev->next = node->next;
      if (node->next != NULL)
	node->next->prev = node->prev;
      node->next = NULL;
      node->prev = NULL;
    }

  if (head != NULL && node != head)
    {
      node->next = head;
      head->prev = node;
    }
  head = node;

  cacheMap[addr] = 1;
}

template <typename AddrType, typename DataType>
void Cache<AddrType,DataType>::writeData (AddrType addr, DataType data)
{
  findGetNode (addr);
  head->data = data;
  D (cout << "write into cache " << addr << ":" << data << endl;)
  D (dumpCache ();)
}

template <typename AddrType, typename DataType>
DataType Cache<AddrType,DataType>::readData (AddrType addr)
{
  findGetNode (addr);
  D (cout << "read from cache: " << addr << ":" << head->data << endl;)
  D (dumpCache ();)
  return head->data;
}

template <typename AddrType, typename DataType>
void Cache<AddrType, DataType>::dumpCache ()
{
  cout << "dump cache" << endl;
  Node <AddrType, DataType> *ite = head;
  while (ite != NULL)
    {
      cout << ite->addr << " -> " << ite->data << endl;
      ite = ite->next;
    }
}


int main ()
{
  map <int, char> memory;
  for (int i = 0; i < 26; ++i)
   memory[i] = 'A' + i;

  for (std::map<int,char>::iterator it=memory.begin();
       it!=memory.end(); ++it)
    cout << it->first << " => " << it->second << '\n';

  Cache <int, char> cache;
  cache.setMemory (&memory);

  cache.writeData (1, 'C');
  for (int i = 1; i < 15; i++)
    cout << "read data " << i << ":" << cache.readData (i) << endl;
  return 0;
}
