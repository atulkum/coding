#include "SkipList.h"
#include <algorithm>

template <class T>
SkipList<T>::SkipList(){
	head = new Node<T>(T(), SkipList<T>::maxHeight);
	head->height = 1;
}

template <class T>
SkipList<T>::~SkipList(){
	makeEmpty();
	delete head;
}

template <class T>
bool SkipList<T>::find(const T & x) const{
    	Node<T> *n = head;
    	for(int i = head->height -1; i >= 0; --i){
		while(n->next[i] != NULL && n->next[i]->data < x){
			n = n->next[i];
		}
	}
	n = n->next[0];
	if(n != 0 && n->data == x){
		return true;
	}else{
		return false;
	}
}


template <class T>
void SkipList<T>::remove(const T & x){
 	Node<T> **update = new Node<T>*[SkipList<T>::maxHeight];
        Node<T> *n = head;
        for(int i = head->height -1; i >= 0; --i){
                while(n->next[i] != NULL && n->next[i]->data < x){
                        n = n->next[i];
                }
                update[i] = n;
        }
        n = n->next[0];

        if(n != 0 && n->data == x){
                for(int i = 0; i < head->height; ++i){
                	if(update[i]->next[i] == n){
				update[i]->next[i] = n->next[i];
			}else{
				break;
			}
                }
		delete n;
		while(head->height > 1 && head->next[head->height-1] == NULL){
			head->height--;
		}
        }
        delete[] update;
}
template <class T>
void SkipList<T>::insert(const T & x){
    	Node<T> **update = new Node<T>*[SkipList<T>::maxHeight];
    	Node<T> *n = head;
    	for(int i = head->height -1; i >= 0; --i){
		while(n->next[i] != NULL && n->next[i]->data < x){
			n = n->next[i];
		}
		update[i] = n; 
	}
	n = n->next[0];
	
	if(n != 0 && n->data == x){
		return;
	}else{
		int level = randomLevel();
		if(level > head->height){
    			for(int i = head->height; i < level; ++i){
				update[i] = head;
			}	
			head->height = level;
		}
		n = new Node<T>(x, level);
		for(int i = 0; i < level; ++i){
			n->next[i] = update[i]->next[i];
			update[i]->next[i] = n;
		}
	}
	delete[] update;
}


template <class T>
bool SkipList<T>::isEmpty() const{
	return (head->next[0] == NULL);
}

template <class T>
void SkipList<T>::makeEmpty(){
    Node<T> *n = head;
    
    while(n->next[0] != NULL){
            Node<T> *temp = n->next[0];
	    delete n;
	    n = temp;
    }
    head = new Node<T>();
}

template <class T>
int SkipList<T>::randomLevel(){
	int height = 1;
	int maxHt = SkipList<T>::maxHeight;
	maxHt = std::min(head->height + 1, maxHt);
	while(getRandomNumber() < 0.5 && height <= maxHt){
		height++;
	}	
	return height;
}


template <class T>
double SkipList<T>::getRandomNumber()
{
    static int i = 0;
    static double a[10] = {0.32945,0.85923,0.12982,0.16250,0.56537,0.64072,0.27597,0.83957,0.75531,0.22502};
    
    return a[(i++)%10];
}


template <class T>
void SkipList<T>::printList()
{
    Node<T> *n = head;
    
    if (isEmpty())
    {
        std::cout << "Empty List" << std::endl;
    } else {
        while(n->next[0] != NULL)
        {
            n = n->next[0];
            // Print node data
            std::cout << "Node " << n->data << " height " << n->height << ": ";
            
            // Print levels
            for (int i=(n->height - 1); i >= 0; i--) {
                std::cout << "Level " << i << " -> ";
                if (n->next[i] != NULL) {
                    std::cout << n->next[i]->data;
                } else {
                    std::cout << "NULL";
                }
                std::cout << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

template class SkipList<int>;


