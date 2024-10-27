#include <mem.h>
#include <NancenOSConfig.h>

static Mem_Block *freeList;
static uint8_t heap[HEAP_SIZE];

void Mem_Init()
{
    freeList = (Mem_Block *)heap;
    freeList->size = HEAP_SIZE - sizeof(Mem_Block);
    freeList->next = NULL;
}

void *Mem_Alloc(size_t size)
{
    Mem_Block *current = freeList;
    Mem_Block *previous = NULL;

    // Align the requested size to a multiple of pointer size
    size = (size + sizeof(void *) - 1) & ~(sizeof(void *) - 1);

    while (current != NULL)
    {
        if (current->size >= size)
        {
            // Found a suitable block
            if (current->size > size + sizeof(Mem_Block))
            {
                // Split the block
                Mem_Block *newBlock = (Mem_Block *)((uint8_t *)current + sizeof(Mem_Block) + size);
                newBlock->size = current->size - size - sizeof(Mem_Block);
                newBlock->next = current->next;

                current->size = size;
                current->next = NULL;

                if (previous != NULL)
                {
                    previous->next = newBlock;
                }
                else
                {
                    freeList = newBlock;
                }
            }
            else
            {
                // Cannot split, remove the block from free list
                if (previous != NULL)
                {
                    previous->next = current->next;
                }
                else
                {
                    freeList = current->next;
                }
                current->next = NULL;
            }

            // Return the address after the memory block header
            return (void *)((uint8_t *)current + sizeof(Mem_Block));
        }

        previous = current;
        current = current->next;
    }

    // No suitable block found
    return NULL;
}

void Mem_Free(void *ptr)
{
    if (ptr == NULL)
        return;

    Mem_Block *blockToFree = (Mem_Block *)((uint8_t *)ptr - sizeof(Mem_Block));
    Mem_Block *current = freeList;
    Mem_Block *previous = NULL;

    // Find the correct position to insert the block into the free list
    while (current != NULL && current < blockToFree)
    {
        previous = current;
        current = current->next;
    }

    // Insert the block into the free list
    blockToFree->next = current;
    if (previous != NULL)
    {
        previous->next = blockToFree;
    }
    else
    {
        freeList = blockToFree;
    }

    // Merge with the next block if adjacent
    if ((uint8_t *)blockToFree + sizeof(Mem_Block) + blockToFree->size == (uint8_t *)current)
    {
        blockToFree->size += sizeof(Mem_Block) + current->size;
        blockToFree->next = current->next;
    }

    // Merge with the previous block if adjacent
    if (previous != NULL && (uint8_t *)previous + sizeof(Mem_Block) + previous->size == (uint8_t *)blockToFree)
    {
        previous->size += sizeof(Mem_Block) + blockToFree->size;
        previous->next = blockToFree->next;
    }
}
