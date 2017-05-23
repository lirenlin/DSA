def letterCombinations(digits):
    '''recursive'''
    digit2letters = {
        '2': "abc",
        '3': "def",
        '4': "ghi",
        '5': "jkl",
        '6': "mno",
        '7': "pqrs",
        '8': "tuv",
        '9': "wxyz",
    }
    res = []
    if len (digits) == 1:
        res = [c for c in digit2letters [digits[0]]]
        return res

    for c in digit2letters[digits[0]]:
        for item in letterCombinations (digits[1:]):
            res.append (c + item)
    return res

print letterCombinations("233")

def letterCombinations(digits, curr, res):
    '''iterative'''
    digit2letters = {
        '2': "abc",
        '3': "def",
        '4': "ghi",
        '5': "jkl",
        '6': "mno",
        '7': "pqrs",
        '8': "tuv",
        '9': "wxyz",
    }
    if not digits:
        res.append (curr)
        return

    for c in digit2letters[digits[0]]:
        letterCombinations (digits[1:], curr + c,res)

res = []
letterCombinations("233", "",  res)
print res
