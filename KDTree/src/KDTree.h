/**
 * File: KDTree.h
 * Author: (your name here)
 * ------------------------
 * An interface representing a kd-tree in some number of dimensions. The tree
 * can be constructed from a set of data and then queried for membership and
 * nearest neighbors.
 */

#ifndef KDTREE_INCLUDED
#define KDTREE_INCLUDED

#include "Point.h"
#include "BoundedPQueue.h"
#include <stdexcept>
#include <cmath>
#include <limits>
#include <set>

// "using namespace" in a header file is conventionally frowned upon, but I'm
// including it here so that you may use things like size_t without having to
// type std::size_t every time.
using namespace std;

template <size_t N, typename ElemType>
class KDTree {
public:
    // Constructor: KDTree();
    // Usage: KDTree<3, int> myTree;
    // ----------------------------------------------------
    // Constructs an empty KDTree.
    KDTree();
    
    // Destructor: ~KDTree()
    // Usage: (implicit)
    // ----------------------------------------------------
    // Cleans up all resources used by the KDTree.
    ~KDTree();
    
    // KDTree(const KDTree& rhs);
    // KDTree& operator=(const KDTree& rhs);
    // Usage: KDTree<3, int> one = two;
    // Usage: one = two;
    // -----------------------------------------------------
    // Deep-copies the contents of another KDTree into this one.
    KDTree(const KDTree& rhs);
    KDTree& operator=(const KDTree& rhs);
    
    // size_t dimension() const;
    // Usage: size_t dim = kd.dimension();
    // ----------------------------------------------------
    // Returns the dimension of the points stored in this KDTree.
    size_t dimension() const;
    
    // size_t size() const;
    // bool empty() const;
    // Usage: if (kd.empty())
    // ----------------------------------------------------
    // Returns the number of elements in the kd-tree and whether the tree is
    // empty.
    size_t size() const;
    bool empty() const;
    
    // bool contains(const Point<N>& pt) const;
    // Usage: if (kd.contains(pt))
    // ----------------------------------------------------
    // Returns whether the specified point is contained in the KDTree.
    bool contains(const Point<N>& pt) const;
    
    // void insert(const Point<N>& pt, const ElemType& value);
    // Usage: kd.insert(v, "This value is associated with v.");
    // ----------------------------------------------------
    // Inserts the point pt into the KDTree, associating it with the specified
    // value. If the element already existed in the tree, the new value will
    // overwrite the existing one.
    void insert(const Point<N>& pt, const ElemType& value);
    
    // ElemType& operator[](const Point<N>& pt);
    // Usage: kd[v] = "Some Value";
    // ----------------------------------------------------
    // Returns a reference to the value associated with point pt in the KDTree.
    // If the point does not exist, then it is added to the KDTree using the
    // default value of ElemType as its key.
    ElemType& operator[](const Point<N>& pt);
    
    // ElemType& at(const Point<N>& pt);
    // const ElemType& at(const Point<N>& pt) const;
    // Usage: cout << kd.at(v) << endl;
    // ----------------------------------------------------
    // Returns a reference to the key associated with the point pt. If the point
    // is not in the tree, this function throws an out_of_range exception.
    ElemType& at(const Point<N>& pt);
    const ElemType& at(const Point<N>& pt) const;
    
    // ElemType kNNValue(const Point<N>& key, size_t k) const
    // Usage: cout << kd.kNNValue(v, 3) << endl;
    // ----------------------------------------------------
    // Given a point v and an integer k, finds the k points in the KDTree
    // nearest to v and returns the most common value associated with those
    // points. In the event of a tie, one of the most frequent value will be
    // chosen.
    ElemType kNNValue(const Point<N>& key, size_t k) const;

private:
    struct Node {
        Point<N> key;
        int level;
        ElemType value;
        
        Node* left;
        Node* right;
        
        int getSplitIndex(){
            return level%N;
        }
    };
    
    Node* root;
    size_t _size;
    
    Node* findNode(const Point<N>& pt) const;
    Node* insertAndReturn(const Point<N>& pt, const ElemType& value);
    void kNNValue(const Point<N>& key, Node* curr,
                      BoundedPQueue<Node*>& bpq) const;
    
    void deleteTree(Node* curr);
    Node* copyTree(Node* curr);
};
template <size_t N, typename ElemType>
void KDTree<N, ElemType>::deleteTree(Node* curr){
    if(curr == nullptr){
        return;
    }
    deleteTree(curr->left);
    deleteTree(curr->right);
    delete curr;
}

template <size_t N, typename ElemType>
typename KDTree<N, ElemType>::Node*
KDTree<N, ElemType>::copyTree(Node* curr){
    if(curr == nullptr){
        return nullptr;
    }
    
    Node* n = new Node();
    n->key = curr->key;
    n->value = curr->value;
    n->level = curr->level;
    n->left = copyTree(curr->left);
    n->right = copyTree(curr->right);
    
    return n;
}

template <size_t N, typename ElemType>
typename KDTree<N, ElemType>::Node*
KDTree<N, ElemType>::findNode(const Point<N>& pt) const{
    Node* curr= root;
    while(curr != nullptr){
        if(pt ==curr->key){
            return curr;
        }
        int splitIndex = curr->getSplitIndex();
        if(pt[splitIndex] > curr->key[splitIndex]){
            curr = curr->right;
        }else{
            curr = curr->left;
        }
    }
    return nullptr;
}

/** KDTree class implementation details */

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree() {
    root = nullptr;
    _size = 0;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
    deleteTree(root);
    root = nullptr;
    _size = 0;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
    return N;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N>& pt) const{
    return findNode(pt) != nullptr;
}
template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const{
    return _size;
}
template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const{
    return size() == 0;
}
template <size_t N, typename ElemType>
const ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) const{
    Node* n = findNode(pt);
    if(n == nullptr){
        throw out_of_range("Point does not exist");
    }
    return n->value;
}
template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) {
    const KDTree<N, ElemType>& constThis = *this;
    return const_cast<ElemType&>(constThis.at(pt));
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N>& pt, const ElemType& value){
    insertAndReturn(pt, value);
}
template <size_t N, typename ElemType>
typename KDTree<N, ElemType>::Node*
KDTree<N, ElemType>::insertAndReturn(const Point<N>& pt, const ElemType& value){
    Node* curr= root;
    Node* pre = nullptr;
    int level = 0;
    while(curr != nullptr){
        level++;
        Node* nextNode = nullptr;
        if(pt ==curr->key){
            curr->value = value;
            return curr;
        }
        int splitIndex = curr->getSplitIndex();
        if(pt[splitIndex] > curr->key[splitIndex]){
            nextNode = curr->right;
        }else{
            nextNode = curr->left;
        }
        pre = curr;
        curr = nextNode;
    }
    Node* n = new Node();
    n->key = pt;
    n->value = value;
    n->level = level;
    n->left = nullptr;
    n->right = nullptr;
    
    if (curr == root) {
        root = n;
    } else {
        int splitIndex = pre->getSplitIndex();
        pt[splitIndex] > pre->key[splitIndex] ? pre->right = n : pre->left = n;
    }
    _size++;
    return n;
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt){
    Node* n = findNode(pt);
    if(n == nullptr){
        n = insertAndReturn(pt, ElemType());
    }
    return n->value;
}

template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::kNNValue(const Point<N>& key, size_t k) const{
    BoundedPQueue<Node*> bpq(k);
    
    kNNValue(key, root, bpq);
    
    std::multiset<ElemType> values;
    while(!bpq.empty()){
        Node* minVal = bpq.dequeueMin();
        values.insert(minVal->value);
    }
    ElemType best;
    size_t bestFrequency = 0;
    for(auto it = values.begin(); it !=values.end(); ++it) {
        if (values.count(*it) > bestFrequency) {
            best = *it;
            bestFrequency = values.count(*it);
        }
    }
    return best;
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::kNNValue(const Point<N>& key, Node* curr,
                                       BoundedPQueue<Node*>& bpq) const{
    if(curr == nullptr){
        return;
    }
    double newDist = Distance(key, curr->key);
    
    bpq.enqueue(curr, newDist);
    
    int splitIndex = curr->getSplitIndex();
    Node* nextNode = nullptr;
    Node* otherNode = nullptr;
    if(key[splitIndex] > curr->key[splitIndex]){
        nextNode = curr->right;
        otherNode = curr->left;
    }else{
        otherNode = curr->right;
        nextNode = curr->left;
    }
    kNNValue(key, nextNode, bpq);
    double bestDist = bpq.worst();
    if(bpq.size() < bpq.maxSize() || fabs(key[splitIndex] - curr->key[splitIndex]) < bestDist){
        kNNValue(key, otherNode, bpq);
    }
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree& rhs){
    root = copyTree(rhs.root);
    _size = rhs._size;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>& KDTree<N, ElemType>::operator=(const KDTree& rhs){
    if(&rhs != this){
        deleteTree(root);
        root = copyTree(rhs.root);
        _size = rhs._size;
    }
    return *this;
}



#endif // KDTREE_INCLUDED
