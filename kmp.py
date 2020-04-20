class KMP:      
    def build_prefix_table(self, word):
        n = len(word)
        prefix_table = [0]*(n + 1)
        prefix_table[0] = -1
    
        curr = 0
        for i in range(1, n):
            if word[i] == word[curr]:
                prefix_table[i] = prefix_table[curr]
            else:
                prefix_table[i] = curr
                while curr >= 0 and word[i] != word[curr]:
                    curr = prefix_table[curr]
            curr += 1
        prefix_table[n] = curr
        return prefix_table
    
    def serach(self, s, w):
        prefix_table = self.build_prefix_table(w)
        i = 0
        k = 0
        while i < len(s):
            if s[i] == w[k]:
                i += 1
                k += 1
                if k == len(w):
                    return True
            else:
                k = prefix_table[k]
                if k < 0:
                    k += 1
                    i += 1
        return False
                
