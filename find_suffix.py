from random import sample

class Node(object):
    def __init__(self):
        self.children = {}
        self.str_ending = set()

class Trie(object):
    def __init__(self):
        self.root = Node()

    def add_str(self, word):
        curr = self.root
        for c in word:
            if c not in curr.children:
                curr.children[c] = Node()
            curr = curr.children[c]
        curr.str_ending.add(word)

    def search_str(self, word):
        curr = self.root
        for c in word:
            if c in curr.children:
                curr = curr.children[c]
            else:
                break
        if curr != self.root:
            words_matched = self.get_children(curr)
            w = sample(words_matched, k=1)[0]
            return w[::-1]
        else:
            return 'None'

    def get_children(self, root):
        curr_words = set(root.str_ending)
        for child in root.children:
            child_words = self.get_children(root.children[child])
            curr_words.update(child_words)
        return curr_words

if __name__ == '__main__':
    word_dict = ['computing', 'polluting', 'diluting', 'commuting', 'fish', 'recruiting', 'dropping', 'banana']
    trie = Trie()
    for w in word_dict:
        trie.add_str(w[::-1])
    for word in ['orange', 'disputing', 'shooting', 'convoluting']:
        a = trie.search_str(word[::-1])
        print(a)
