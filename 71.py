def simplify_path (path):
    array = path.split ('/')
    stack = list ()
    stack.append ('')

    for item in array:
        if item == '':
            continue
        if item == ".":
            continue
        elif item == "..":
            if len (stack) == 1:
                break;
            stack.pop ()
        else:
            stack.append (item)
    if len (stack) == 1:
        return '/'
    else:
        return '/'.join (stack)

print simplify_path ("/a/./b/../../c/")
print simplify_path ("/home/")
print simplify_path ("/../../")
