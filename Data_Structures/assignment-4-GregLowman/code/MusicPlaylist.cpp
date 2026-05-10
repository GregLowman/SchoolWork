
#include "MusicPlaylist.hpp"

MusicPlaylist::MusicPlaylist()
{
}

/*
 * Purpose: Has to detect if a loop is present in the linkedlist pointed by head
 * @param none
 * @return integer length of loop if one exists. If loop not present return -1
 */
int MusicPlaylist::findLoopInPlaylist(){
    Song *slow = head;
    Song *fast = head;
    int counter = -1;

    if (slow != nullptr && fast != nullptr)
    {

        if(fast->next != nullptr)
        {
    
            fast = fast->next->next;
        }

        slow = slow->next;

        while(fast != nullptr && fast->next != nullptr && fast->next->next !=nullptr)
        {        
            slow = slow->next;
            fast = fast->next->next;
            if (slow->songName == fast->songName)
            {
                slow = slow->next;
                int counter = 1;

                //Find the loop length, break when slow counts the loop

                while (slow != fast) 
                {
                    slow = slow->next;
                    counter += 1;
                }
                return counter;
            }
        }
    }
    return counter;
}

/*
 * Purpose: Has to remove all the Song nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void MusicPlaylist::removeSongs(int start, int end){

    int size = 0;
    Song *current = head;

    while(current != nullptr)
        {
            size ++;
            current = current ->next;
        }

    if(head == nullptr) 
    {
        cout << "Playlist is Empty" << endl;
        return;
    }
    else if(start < 1 || end > size || start > end)
    {
        cout << "Invalid start or end values" << endl;
        return;
    }
    else
    {
        current = head;

        if(start == 1 ) 
        {
            while(end-- && head != nullptr)
            {
                Song *toDelete = head;
                head = head->next;
                delete toDelete;
            }
            return;
        }
        else
        {
            Song *previous = head;

            for(int i = 1; i < (start - 1); i ++)
            {
                previous = previous->next;
            }

            Song *current = previous->next;
            int deleteIndex = end - start + 1;
            Song *deleteSong;

            while(deleteIndex-- && current != nullptr)
            {
                deleteSong = current;
                current = current->next;
                previous->next = current;
                delete deleteSong;
            }
            return;
        }
        return;
    }
}


/*
 * Purpose: Interweave songs from two playlists into a new merged linked list,
 * starting with the first song in headOne. Reuses existing nodes by relinking pointers.
 * If one list is shorter, the remaining nodes of the other are appended.
 * @param two linked-list heads headOne and headTwo
 * @return none
 */
void MusicPlaylist::mergeTwoPlaylists(Song *headOne, Song * headTwo){
    int sizeOne = 0, sizeTwo = 0;
    Song *currentOne = headOne;
    Song *currentTwo = headTwo;
    Song *holdOne, *holdTwo;

    if(!headOne && !headTwo)
    {
        this->head = nullptr;
        return;
    }

    else if(!headTwo)
    {
        this->head = headOne;
        return;
    }

    else if(!headOne)
    {
        this->head = headTwo;
        return;
    }

// Set size of first linked list
    else
    {
        while(currentOne)
        {
            sizeOne++;
            currentOne = currentOne->next;
        }
    // Set size of second linked list
        while(currentTwo)
        {
            sizeTwo++;
            currentTwo = currentTwo->next;
        }

    // Reset current pointers back to the head of the lists
        currentOne = headOne;
        currentTwo = headTwo;

    // Set the size of the merged list 
        int mergeSize = sizeOne + sizeTwo;


    //Loop while the size of the list increments down by one
        while(mergeSize--)
        {

        // Handle the case of neither one of them being null pointer (empty)
            while(currentOne && currentTwo)
            {
                holdOne = currentOne ->next;
                currentOne->next = currentTwo;
                holdTwo = currentTwo ->next;
                currentTwo->next = holdOne;
                currentOne = holdOne;
                currentTwo = holdTwo;
            }
        //If the second set is empty the first, it does not matter
        //We are already appending to the first so the rest of its contents
        //May remain. This if is to catch the case where the second list
        //Has more to go and we do not want to lose the contents
            
            if(!currentOne && currentTwo)
            {
                currentOne = currentTwo;
            }


            this->head = headOne;
        }
        return;
    }
}