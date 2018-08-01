void main()
{
    char a1[3] = "abc";
    char a2[8] = "abcdefgh";
    char b1[]  = "abc";
    char b2[]  = "abcdefgh";
    char* c1   = "abcx";
    char* c2   = "abcdefghx";

    printf("a1:%s is size: %d\n",a1,sizeof(a1)); // 4
    printf("a2:%s is size: %d\n",a2,sizeof(a2)); // 8
    printf("b1:%s is size: %d\n",b1,sizeof(b1)); // with \0
    printf("b2:%s is size: %d\n",b2,sizeof(b2)); // with \0
    printf("c1:%s is size: %d\n",c1,sizeof(c1)); // sizeof pointer
    printf("c2:%s is size: %d\n",c2,sizeof(c2)); // sizeof pointer
}
