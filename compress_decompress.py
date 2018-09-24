def decompress(start, text):
    i = start
    dec_text = ''
    while i < len(text) and text[i] != ']':
        if text[i].isdigit():
            l = 0
            while text[i] != '[': #guaranteed that i < len(text)
                l = l*10 + int(text[i])
                i += 1

            i += 1 #for escaping '['

            i, dec_text_next = decompress(i, text)
            dec_text += ''.join([dec_text_next] * l)
        else:
            dec_text += text[i]
            i += 1

    if i < len(text) and text[i] == ']':
        i += 1

    return i, dec_text

def decompress_main(text):
    new_text = '1[' + text + ']'
    _ , dec_text = decompress(2, new_text)
    return dec_text

if __name__ == '__main__':
    print decompress_main("2[2[abbb]c]") == "abbbabbbcabbbabbbc"
    print decompress_main("2[aabc]d") == "aabcaabcd"
    print decompress_main("10[a]") == "aaaaaaaaaa"
    print decompress_main("aaa") == "aaa"
    print decompress_main("3[a]") == "aaa"
