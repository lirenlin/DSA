def gray_code (n):
    '''
    G(N) = (B(n)/2) xor B(n)
    '''
    result = [ i>> 1 ^ i for i in range (pow (2, n))]


