def numDecodings (s):
    user_dict = dict ()
    for i in range (1, 27):
        user_dict[str (i)] = chr (i+64)
    user_dict[str (0)] = ""

    size = len (s)
    dp = [[""] for __ in range (size)]
    dp[size - 1] = [user_dict [s[size-1]]]

    for i in range (size - 2, -1, -1):
        if s[i] != '0':
            if dp[i+1] != ['']:
                dp[i] = [user_dict[s[i]] + item for item in dp[i+1]]
            if i < size - 1 and s[i:i+2] in user_dict:
                new_char = user_dict[s[i:i+2]]
                if i+2 == size:
                    dp[i] = [new_char] + dp[i] if dp[i] != [''] else [new_char]
                elif dp[i+2] == ['']:
                    continue
                else:
                    new_list = [new_char + item for item in dp[i+2]]
                    dp[i] = new_list + dp[i] if dp[i] != [''] else new_list

    return dp[0]

print numDecodings ("110")
print numDecodings ("111")
print numDecodings ("40")

