/* 
 * mm-implicit.c -  Simple allocator based on implicit free lists, 
 *                  first fit placement, and boundary tag coalescing. 
 *
 * Each block has header and footer of the form:
 * 
 *      31                     3  2  1  0 
 *      -----------------------------------
 *     | s  s  s  s  ... s  s  s  0  0  a/f
 *      ----------------------------------- 
 * 
 * where s are the meaningful size bits and a/f is set 
 * iff the block is allocated. The list has the following form:
 *
 * begin                                                          end
 * heap                                                           heap  
 *  -----------------------------------------------------------------   
 * |  pad   | hdr(8:a) | ftr(8:a) | zero or more usr blks | hdr(8:a) |
 *  -----------------------------------------------------------------
 *          |       prologue      |                       | epilogue |
 *          |         block       |                       | block    |
 *
 * The allocated prologue and epilogue blocks are overhead that
 * eliminate edge conditions during coalescing.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
  /* SoloTeam */
  "SoloTeam",
  /* Gregory Lowman */
  "Gregory Lowman",
  /* Grlo2648@colorado.edu */
  "Grlo2648@colorado.edu",
  /* Second member's full name (leave blank if none) */
  "",
  /* Second member's email address (leave blank if none) */
  ""
};

/////////////////////////////////////////////////////////////////////////////
// Constants and macros
//
// These correspond to the material in Figure 9.43 of the text
// The macros have been turned into C++ inline functions to
// make debugging code easier.
//
/////////////////////////////////////////////////////////////////////////////
#define WSIZE       4       /* word size (bytes) */  
#define DSIZE       8       /* doubleword size (bytes) */
#define CHUNKSIZE  (1<<12)  /* initial heap size (bytes) */
#define OVERHEAD    8       /* overhead of header and footer (bytes) */

static inline int MAX(int x, int y) {
  return x > y ? x : y;
}

//
// Pack a size and allocated bit into a word
// We mask of the "alloc" field to insure only
// the lower bit is used
//
static inline uint32_t PACK(uint32_t size, int alloc) {
  return ((size) | (alloc & 0x1));
}

//
// Read and write a word at address p
//
static inline uint32_t GET(void *p) { return  *(uint32_t *)p; }
static inline void PUT( void *p, uint32_t val)
{
  *((uint32_t *)p) = val;
}

//
// Read the size and allocated fields from address p
//
static inline uint32_t GET_SIZE( void *p )  { 
  return GET(p) & ~0x7;
}

static inline int GET_ALLOC( void *p  ) {
  return GET(p) & 0x1;
}

//
// Given block ptr bp, compute address of its header and footer
//
static inline void *HDRP(void *bp) {

  return ( (char *)bp) - WSIZE;
}
static inline void *FTRP(void *bp) {
  return ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE);
}

//
// Given block ptr bp, compute address of next and previous blocks
//
static inline void *NEXT_BLKP(void *bp) {
  return  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)));
}

static inline void* PREV_BLKP(void *bp){
  return  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)));
}

// Getters - read the pointer stored in the free block
static inline void *GET_PREV_FREE(void *bp) {
    return (*(void **)(bp));
}

static inline void *GET_NEXT_FREE(void *bp) {
    return (*(void **)((char *)(bp) + sizeof(void *)));
}

// Setters - write a pointer into the free block

static inline void SET_PREV_FREE(void *bp, void *ptr) {
    (*(void **)(bp)) = ptr;
}

static inline void SET_NEXT_FREE(void *bp, void *ptr) {
    (*(void **)((char *)(bp) + sizeof(void *))) = ptr;
}

/////////////////////////////////////////////////////////////////////////////
//
// Global Variables
//

static char *heap_listp;  /* pointer to first block */  
static char *free_listp;

//
// function prototypes for internal helper routines
//
static void *extend_heap(uint32_t words);
static void place(void *bp, uint32_t asize);
static void *find_fit(uint32_t asize);
static void *coalesce(void *bp);
static void printblock(void *bp); 
static void checkblock(void *bp);

//
// mm_init - Initialize the memory manager 
//
int mm_init(void) 
{
  // If there is an error with building the heap structure, return -1
  if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
    return -1;
  
  PUT(heap_listp, 0); //Padding
  PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); //Header
  PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); //Footer
  PUT(heap_listp + (3 * WSIZE), PACK(0, 1)); //Epilogue

  //Place heaplist between the header and footer
  heap_listp += (2 * WSIZE);

  free_listp = NULL;
  //Extend the heap with an initial free block of Chunksize bytes
  if(extend_heap(CHUNKSIZE / WSIZE) == NULL)
    return -1;

  return 0;
}


//
// extend_heap - Extend heap with free block and return its block pointer
//
static void *extend_heap(uint32_t words) 
{
  //char -> 1 byte -> byte by byte control
  char *bp;
  uint32_t size;

  //Convert words to bytes and make sure it is a multiple of 8
  size = words * WSIZE;
  if (size % 8 != 0)
      size = size + (8 - (size % 8));

  //Make sure that extending the heap will be possible 
  if((long)(bp = mem_sbrk(size)) == -1)
    return NULL;

  //Build memory space with allowed memory
  PUT(HDRP(bp), PACK(size, 0)); //Free Header
  PUT(FTRP(bp), PACK(size, 0)); //Free Footer
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0,1)); //Epilogue


  SET_PREV_FREE(bp, NULL);
  SET_NEXT_FREE(bp, NULL);

  return coalesce(bp);
}


//
// Practice problem 9.8
//
// find_fit - Find a fit for a block with asize bytes 
//
static void *find_fit(uint32_t asize)
{
    //Generic Pointer as placeholder
  void *bp;

  //bp equals the heap list, if the size of the head is greater than 0 then continue and set bp to the next position in head list
  for (bp = free_listp; bp != NULL; bp = GET_NEXT_FREE(bp))
  {
    //if the memory in the head of heap list is free AND asize is less than the size of the head of heap list
    if (asize <= GET_SIZE(HDRP(bp)))
    {
      return bp;
    }
  }

  //no fit found
  return NULL;
}

// 
// mm_free - Free a block 
//
void mm_free(void *bp)
{
  //size of the block of memory at the head of bp
  uint32_t size = GET_SIZE(HDRP(bp));

  //Set memory block to free by setting the head and foot to free
  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));

  SET_PREV_FREE(bp, NULL);
  SET_NEXT_FREE(bp, NULL);

  //Merge with any other free blocks
  coalesce(bp);
}

static void remove_free(void *bp)
{
  if (GET_PREV_FREE(bp))
    SET_NEXT_FREE(GET_PREV_FREE(bp), GET_NEXT_FREE(bp));
  else
    free_listp = GET_NEXT_FREE(bp);

  if (GET_NEXT_FREE(bp))
    SET_PREV_FREE(GET_NEXT_FREE(bp), GET_PREV_FREE(bp));
}
static void insert_free(void *bp)
{
  SET_NEXT_FREE(bp, free_listp);
  SET_PREV_FREE(bp, NULL);

  if (free_listp)
    SET_PREV_FREE(free_listp, bp);

  free_listp = bp;
}




//
// coalesce - boundary tag coalescing. Return ptr to coalesced block
//
static void *coalesce(void *bp) 
{
  //Variables to easily determine if the head and foot memory are free or allocated. The size is also retrieved and stored. 
  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
  size_t size = GET_SIZE(HDRP(bp));

  //Both head and foot are allocated, move on
  if(prev_alloc && next_alloc)
  {
    return bp;
  }

  //Size += merges memory by allocating further memory to the head or foot to absorb the free memory

  //previous block is allocated and the next is free
  else if(prev_alloc && !next_alloc)
  {
    remove_free(NEXT_BLKP(bp));
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK (size, 0));
    insert_free(bp);
  }

  //next block is allocated and the previous is free
  else if(!prev_alloc && next_alloc)
  {
    remove_free(PREV_BLKP(bp));
    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
    PUT(FTRP(bp), PACK (size, 0));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp);
    insert_free(bp);
  }

  //Both blocks are free
  else
  {
    remove_free(NEXT_BLKP(bp));
    remove_free(PREV_BLKP(bp));
    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp);
    insert_free(bp);
  }

  return bp;
}

//
// mm_malloc - Allocate a block with at least size bytes of payload 
//
void *mm_malloc(uint32_t size) 
{
  uint32_t asize;
  uint32_t extendsize; 
  char *bp;

  if(size ==0)
    return NULL;

  //Allow for enough memory to include the head, foot, and memory space being requested

  if(size <= DSIZE)
    asize = 4 * DSIZE;
  //Alignment method from text book 
  //Makes sure adequate memory is allocated and it is a multiple of 8
  else 
    asize = DSIZE * ((size + DSIZE + (DSIZE - 1)) / DSIZE);

  //if bp is able to find a fit, place bp in the adjusted size
  if ((bp = find_fit(asize)) != NULL) 
  {
    place(bp, asize);
    return bp;
  }

  //extend size is set to asize or chunksize, whichever is bigger
  extendsize = MAX(asize, CHUNKSIZE);

  //if extend heap returns null, there is no space for this allocation, return null
  if((bp = extend_heap(extendsize / WSIZE)) == NULL)
    return NULL;
  
  //otherwise place bp in asize and return 
  place(bp, asize);
  return bp;
} 

//
//
// Practice problem 9.9
//
// place - Place block of asize bytes at start of free block bp 
//         and split if remainder would be at least minimum block size
//
static void place(void *bp, uint32_t asize)
{
  uint32_t csize = GET_SIZE(HDRP(bp));

  remove_free(bp);

  if ((csize - asize) >= (4 * DSIZE))
  {
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));

    bp = NEXT_BLKP(bp);
    PUT(HDRP(bp), PACK(csize - asize, 0));
    PUT(FTRP(bp), PACK(csize - asize, 0));

    SET_PREV_FREE(bp, NULL);
    SET_NEXT_FREE(bp, NULL);
    insert_free(bp);
  }

  else 
  {
    PUT(HDRP(bp), PACK(csize, 1));
    PUT(FTRP(bp), PACK(csize, 1));
  }
}


//
// mm_realloc -- implemented for you
//
void *mm_realloc(void *ptr, uint32_t size)
{
  void *newp;
  uint32_t copySize;
  uint32_t asize;

  if (ptr == NULL)
    return mm_malloc(size);

  if (size == 0) {
    mm_free(ptr);
    return NULL;
  }

  if (size <= DSIZE)
    asize = 4 * DSIZE;
  else
    asize = DSIZE * ((size + DSIZE + (DSIZE - 1)) / DSIZE);

  // Current block already big enough
  if (asize <= GET_SIZE(HDRP(ptr)))
    return ptr;

  // Try merging with next block if it is free
  uint32_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(ptr)));
  uint32_t combinedsize = GET_SIZE(HDRP(ptr)) + GET_SIZE(HDRP(NEXT_BLKP(ptr)));

  if (!next_alloc && (combinedsize >= asize)) {
    remove_free(NEXT_BLKP(ptr));
    PUT(HDRP(ptr), PACK(combinedsize, 1));
    PUT(FTRP(ptr), PACK(combinedsize, 1));
    return ptr;
  }

  // Last resort, allocate new block copy and free old
  newp = mm_malloc(size);
  if (newp == NULL)
    return NULL;

  copySize = GET_SIZE(HDRP(ptr));
  if (size < copySize)
    copySize = size;

  memcpy(newp, ptr, copySize);
  mm_free(ptr);
  return newp;
}

//
// mm_checkheap - Check the heap for consistency 
//
void mm_checkheap(int verbose) 
{
  //
  // This provided implementation assumes you're using the structure
  // of the sample solution in the text. If not, omit this code
  // and provide your own mm_checkheap
  //
  void *bp = heap_listp;
  
  if (verbose) {
    printf("Heap (%p):\n", heap_listp);
  }

  if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp))) {
	printf("Bad prologue header\n");
  }
  checkblock(heap_listp);

  for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
    if (verbose)  {
      printblock(bp);
    }
    checkblock(bp);
  }
     
  if (verbose) {
    printblock(bp);
  }

  if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp)))) {
    printf("Bad epilogue header\n");
  }
}

static void printblock(void *bp) 
{
  uint32_t hsize, halloc, fsize, falloc;

  hsize = GET_SIZE(HDRP(bp));
  halloc = GET_ALLOC(HDRP(bp));  
  fsize = GET_SIZE(FTRP(bp));
  falloc = GET_ALLOC(FTRP(bp));  
    
  if (hsize == 0) {
    printf("%p: EOL\n", bp);
    return;
  }

  printf("%p: header: [%d:%c] footer: [%d:%c]\n",
	 bp, 
	 (int) hsize, (halloc ? 'a' : 'f'), 
	 (int) fsize, (falloc ? 'a' : 'f')); 
}

static void checkblock(void *bp) 
{
  if ((uintptr_t)bp % 8) {
    printf("Error: %p is not doubleword aligned\n", bp);
  }
  if (GET(HDRP(bp)) != GET(FTRP(bp))) {
    printf("Error: header does not match footer\n");
  }
}

