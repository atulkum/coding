import string

char_dict = {}
for str in [string.ascii_lowercase, string.digits, '\' ']:
    for c in str:
        char_dict[c] = len(char_dict)

class TrieNode(object):
    def __init__(self):
        self.matches = set()
        self.children = {}

class Trie(object):
    def __init__(self):
        self.root = TrieNode()
        self.word_dict = []

    def search_word(self, w):
        matched = []
        curr = self.root
        for i, c in enumerate(w):
            idx = char_dict[c]
            if curr.children[idx] == None:
                break
            else:
                curr = curr.children[idx]

            if len(curr.matches) > 0:
                for a in curr.matches:
                    matched.append(a)
        if len(matched) > 0:
            max_len = max([len(self.word_dict[a]) for a in matched])
            return [self.word_dict[a] for a in matched if len(self.word_dict[a]) == max_len]
        else:
            return None

    def search_levenshtein(self, kdel, ksub, kadd, w):
        state = {
            'del': kdel,
            'sub': ksub,
            'add': kadd,
        }
        k = max(kdel, max(ksub, kadd))
        matched = set()
        matched.update(self.search_levenshtein_(w, state, self.root))
        if len(matched) > 0:
            max_len = max([len(self.word_dict[a]) for a in matched])
            return [self.word_dict[a] for a in matched if len(self.word_dict[a]) == max_len]
        else:
            return []

    def search_levenshtein_(self, w, state, curr):
        for k, v in state.items():
            if v < 0:
                return []

        matched = []
        for i, c in enumerate(w):
            idx = char_dict.get(c, -1)
            if idx not in curr.children:
                #deletion
                new_state = state.copy()
                new_state['del'] -= 1
                for a in self.search_levenshtein_(w[i + 1:], new_state, curr):
                    matched.append(a)
                # substitiution/addition
                for child_idx in curr.children:
                    new_current = curr.children[child_idx]
                    new_state = state.copy()
                    new_state['sub'] -= 1
                    for a in self.search_levenshtein_(w[i + 1:], new_state, new_current):
                        matched.append(a)

                    new_state = state.copy()
                    new_state['add'] -= 1
                    for a in self.search_levenshtein_(w[i:], new_state, new_current):
                        matched.append(a)

                return matched
            else:
                curr = curr.children[idx]

            if len(curr.matches) > 0:
                for a in curr.matches:
                    matched.append(a)
        return matched

    def add_word(self, w):
        if w in set(self.word_dict):
            return
        self.word_dict.append(w)
        word_idx = len(self.word_dict) - 1
        curr = self.root
        for c in w:
            idx = char_dict[c]
            if idx not in curr.children:
                curr.children[idx] = TrieNode()
            curr = curr.children[idx]
        curr.matches.add(word_idx)


if __name__ == "__main__":
    t = Trie()

    for w in ['hello', 'hello atul', 'hello hello atul', 'kapi', 'ariana grande']:
        t.add_word(w)

    for w in ['lo atul', 'hepp ptul', 'hlo atul', 'hellol', 'andriana grande']:
        print(w, t.search_levenshtein(2, 4, 2, w))
