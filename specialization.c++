//http://www.gotw.ca/gotw/049.htm

template<typename T1, typename T2>
void f (T1 a, T2 b) {};			// 1
template<typename T> void f( T, T ) {};    // 3
template<typename T> void f( T*, T ) {};   // 5
template<typename T> void f( T, T* ) {};   // 6
template<typename T> void f( int, T* ) {}; // 7, partial specialization
void f( int, double ) {};                  // 9, overload

template<typename T> void f( T ) {};       // 2
template<typename T> void f( T* ) {};      // 4
template<> void f<int>( int ) {};          // 8, specialization
void f( int ) {};                          // 10, overload

int i;
double d;
float ff;
complex<double> c;

f (i);		// call 10
f<int>(i);	// call 8
f (i, i);	// call 3
f (c);		// call 2
f (i, ff);	// call 1
f (i, d);	// call 9
f (c, &c);	// call 6
f (i, &d);	// call 7
f (&d, d);	// call 5
f (&d);		// call 4
f (d, &i);	// call 1
f (&i, &i);	// call 3

// overload > parital specialization > template instantiation.

template<class T1, class T2, int I>
class A             { };             // #1 We can specialize this for the case when T2 is a T1*:

template<class T, int I>
class A<T, T*, I>   { };             // #2 Or for the case when T1 is any pointer:

template<class T1, class T2, int I>
class A<T1*, T2, I> { };             // #3 Or for the case when T1 is int and T2 is any pointer and I is 5:

template<class T>
class A<int, T*, 5> { };             // #4 Or for the case when T2 is any pointer:

template<class T1, class T2, int I>
class A<T1, T2*, I> { };             // #5

A<int, int, 1>   a1;  // uses #1
A<int, int*, 1>  a2;  // uses #2, T is int, I is 1
A<int, char*, 5> a3;  // uses #4, T is char
A<int, char*, 1> a4;  // uses #5, T1 is int,
		      // T2 is char, I is 1
A<int*, int*, 2> a5;  // ambiguous: matches #3 and #5


// overload when you can, specialise when you need to.
// http://www.gotw.ca/publications/mill17.htm
