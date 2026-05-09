#ifndef MovieCollection_H__
#define MovieCollection_H__

#define EMPTY_TREE_ERROR 0xDEADBEEF

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std; 

struct Movie {
    string movieName;
    string director;
    string genre;

    Movie* left = NULL;
    Movie* right = NULL;

    Movie(string bm, string a, string g) {
        movieName = bm;
        director = a;
        genre = g;
    }

    void *operator new(std::size_t bytes);
    void operator delete(void *);
};

class MovieCollection {
    private:
        Movie* root;

    public:
        MovieCollection();
        ~MovieCollection();
        
        void addMovie(string movieName, string director, string genre);
        void showMovieCollection();
        void showMovie(string movieName);
        void showMoviesByDirector(string director);
        int showNumberInGenre(string genre);
        void printLeaves();
        int getHeightOfMovieCollection();
        void deleteTree(Movie* node);
        void addMovieHelper(Movie* &node, Movie* newNode);
        void printMovieRecursive(Movie* movie);
        void showMovieHelper(string movieName);
        void byDirectorHelper(Movie* current, string director);
        void leafNodeHelperFunction(Movie* currNode);
        int getHeightHelper(Movie* current);
};

struct traceNode
{
  std::string pType;
  void *ptr;
  traceNode *next = NULL;
  traceNode(){}
  traceNode(std::string t, void *p, traceNode *n) : pType(t), ptr(p), next(n) {}
};

extern traceNode *traceHead;
extern bool verbose;
extern int numAllocs;

inline traceNode * addTraceNode(std::string pType, void *ptr, traceNode *traceHead)
{
  traceNode *nn = new traceNode(pType, ptr, traceHead);
  return nn;
}

inline traceNode * removeTraceNode(traceNode *traceHead, void *ptr)
{

  if (traceHead == nullptr){
    std::cerr << "[ERROR] Attempted to delete a node that was never allocated." << std::endl;
    exit(1);
  }
  else if (traceHead->ptr == ptr){
    traceNode *tmp = traceHead->next;
    delete traceHead;
    return tmp;
  }
  else{
    traceHead->next = removeTraceNode(traceHead->next, ptr);
    return traceHead;
  }
}
//----------------------Overloads tree nodes---------------------------
inline void* Movie::operator new(std::size_t bytes)
{
  numAllocs += 1;
  void * buf = malloc(bytes);
  memset(buf, 0x0, bytes);

  if(verbose){
    std::cout << "[GRADER] Created Movie with address: " << buf << std::endl;
  }

  traceHead = addTraceNode("BST", buf, traceHead);

  return buf;
}

inline void Movie::operator delete(void *ptr)
{
  numAllocs -= 1;

  if (verbose){
      std::cout << "[GRADER] Deleted Movie with address: " << ptr << std::endl;
  }

  traceHead = removeTraceNode(traceHead, ptr);

  free(ptr);
}

inline void printNode(traceNode * n)
{
  if(n->pType=="BST"){
    Movie *b = (Movie*) n->ptr;
    cout << "    Movie <" << b->movieName << ">" << endl;
  }
}

#endif
