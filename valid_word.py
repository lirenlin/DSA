import string
import copy

char_list = list (string.ascii_lowercase)
visited_word = dict ()

def valid_word (word):
    return True

#DFS, BFS should be better.
def solution (word, target, step = 0):
    if word == target:
        print step
        return True

    word = list (word)
    for i in range (len (word)):
        next_word_list = list ()
        for char in char_list:
            if char == word[i]:
                continue
            next_word = copy.deepcopy (word)
            next_word[i] = char
            next_word = ''.join (next_word)

            if next_word in visited_word:
                return False
            else:
                visited_word[next_word] = 1

            if valid_word (next_word):
                if next_word == target:
                    print step + 1
                    return True
                next_word_list.append (next_word)

        for item in next_word_list:
            if solution (item, target, step + 1):
                return True

    return False


solution ("bb", "ac")
