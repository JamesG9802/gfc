#ifndef __GFC_LIST_H__
#define __GFC_LIST_H__

#include <SDL.h>

typedef void gfc_work_func(void*);/**<prototype for a work function*/
typedef void gfc_work_func_context(void*,void*);/**<prototype for a work function*/

typedef struct
{
    void *data;
}ListElementData;

/**
 * @brief the GFC List is an automatically expanding general purpose list
 * the list stores data in contiguous memory
 */
typedef struct
{
    ListElementData *elements;
    Uint32 size;
    Uint32 count;
}List;

/**
 * @brief allocated a new empty list
 * @return NULL on memory error or a new empty list
 */
List *gfc_list_new();

/**
 * @brief allocate a new empty list of size 'count'
 * @param count how many elements you wish to support in this list.
 * @return NULL on memory error or a new empty list
 */
List *gfc_list_new_size(Uint32 count);

/**
 * @brief make a copy of a list.  
 * @note: THIS DOES NOT COPY ANY DATA POINTED TO BY THE OLD LIST
 * @param old the list to copy
 * @return NULL on error or no old data to copy,  A new list that contains the same 
 * information as the old list.  (data pointers will be copied)
 */
List *gfc_list_copy(List *old);

/**
 * @brief deletes a list that has been previously allocated
 * @param list the list to delete;
 */
void gfc_list_delete(List *list);

/**
 * @brief clears out the list, but does NOT free any data that the list may have been pointing to
 * @param list the list to clear
 * @note effectively zeroes out the list without freeing any data
 */
void gfc_list_clear(List *list);

/**
 * @brief get the data stored at the nth element
 * @param list the list to pull data from
 * @param n which element to look out
 * @return NULL on error (such as if n > the element count) or the address of the data otherwise
 */
void *gfc_list_get_nth(List *list,Uint32 n);

/**
 * @brief set the data stored at the nth element
 * @param list the list to change
 * @param n which element to change
 * @param data the new data to set it to
 * @note the old data WILL NOT be cleaned up
 */
void gfc_list_set_nth(List *list,Uint32 n,void *data);

/**
 * @brief add an element to the end of the list
 * @note as of 2023, the original list is what is returned on success and you do not HAVE to assign it back to this function
 * @param list the list to add to
 * @param data the data to assign to the new element
 * @return NULL on error, your list otherwise
 */
List *gfc_list_append(List *list,void *data);

/**
 * @brief add an element to the beginning of the list
 * @note must catch the returned list to replace the list you had
 * @param list the list to add to
 * @param data the data to assign to the new element
 * @return NULL on error, your list otherwise
 */
List *gfc_list_prepend(List *list,void *data);

/**
 * @brief instert a new element at the position provided
 * @param list the list to insert into
 * @param data the data to assin to the new element
 * @return NULL on error, or the provided list otherwise
 */
List *gfc_list_insert(List *list,void *data,Uint32 n);

/**
 * @brief delete the element at the nth position in the array
 * @note this does not clean up the information that the list is referring to
 * @param list the list to delete out of
 * @param n the element to delete.  This is no-op if the nth element is beyond the scope of the list (event is logged)
 * @return -1 on error, 0 otherwise
 */
int gfc_list_delete_nth(List *list,Uint32 n);

/**
 * @brief delete the item at the end of the list
 * @note this does not clean up the information that the list is referring to
 * @param list the list to delete from;
 * @return 0 if all is well, -1 on error
 */
int gfc_list_delete_last(List *list);

/**
 * @brief delete the first element in the list pointing to the address of data
 * @note does not delete the data itself
 * @param list the list to delete the element from
 * @param data used to match against which element to delete
 * @return -1 on error, 0 otherwise
 */
int gfc_list_delete_data(List *list,void *data);

/**
 * @brief search the list for the given item
 * @param list the list to search
 * @param data the data to search for
 * @return -1 on not found or error, the index otherwise
 */
int gfc_list_get_item_index(List *list,void *data);

/**
 * @brief get the number of tracked elements in the list
 * @param list the list the check
 * @return the count in the list.  Will be zero if list was NULL
 */
Uint32 gfc_list_get_count(List *list);

/**
 * @brief iterate over each element in the array and call the function provided
 * @param list the list to iterate over
 * @param function a pointer to a function that will be called.  Data will be set to the list data element
 */
void gfc_list_foreach(List *list,void (*function)(void *data));

/**
 * @brief iterate over each element in the array and call the function provided
 * @param list the list to iterate over
 * @param function a pointer to a function that will be called.  Data will be set to the list data element, context will be the contextData provided
 * @param contextData the data that will also be provided to the function pointer for each element
 */
void gfc_list_foreach_context(List *list,void (*function)(void *data,void *context),void *contextData);

/**
 * @brief swap the locations of two items in the list.
 * @param list the list to alter
 * @param a the first item
 * @param b the second item
 */
void gfc_list_swap_indices(List *list,Uint32 a, Uint32 b);

/**
 * @brief add the elements from b into a
 * @note the data is not duplicated and b will still point to the same data that is now also referenced in a
 * @note the new address of a is returned
 * @param a the list that will get new items added to it
 * @param b the list that will provide new items for a
 * @return NULL on failure, a pointer to the new list otherwise
 */
List *gfc_list_concat(List *a,List *b);

/**
 * @brief same as gfc_list_concat but b is freed when complete
 * @note the new address of a is returned
 * @param a the list to add items to
 * @param b the list to provide the items.  This list is freed, but the data referenced is now referenced by a
 * @return NULL on failure, a pointer to the new list otherwise
 */
List *gfc_list_concat_free(List *a,List *b);


#endif
