
1. Keyword `volatile`:

    [https://stackoverflow.com/a/72617/3829845](https://stackoverflow.com/a/72617/3829845)

2. Copy blocks of memory:

    ```cpp
    memcpy(a, b, sizeof(a));
    ```

    is faster than

    ```cpp
    std::copy(&a[0], &a[3], &b[0]);
    ```

3. `memcpy` vs `memmove`:

    Addresses of source and destination should not overlap when using `memcpy`.

    `memmove` is always safer but slightly slower than `memcpy`.

4. `malloc` vs `new`:

    `new`/`delete`

    * Allocate/release memory
    * Memory allocated from 'Free Store'
    * Returns a fully typed pointer.
    * new (standard version) never returns a NULL (will throw on failure)
    * Are called with Type-ID (compiler calculates the size)
    * Has a version explicitly to handle arrays.
    * Reallocating (to get more space) not handled intuitively (because of copy constructor).
    * Whether they call malloc/free is implementation defined.
    * Can add a new memory allocator to deal with low memory (set_new_handler)
    * operator new/delete can be overridden legally
    * constructor/destructor used to initialize/destroy the object

    `malloc`/`free`

    * Allocates/release memory
    * Memory allocated from 'Heap'
    * Returns a void*
    * Returns NULL on failure
    * Must specify the size required in bytes.
    * Allocating array requires manual calculation of space.
    * Reallocating larger chunk of memory simple (No copy constructor to worry about)
    * They will NOT call new/delete
    * No way to splice user code into the allocation sequence to help with low memory.
    * malloc/free can NOT be overridden legally

    [https://stackoverflow.com/a/240308/3829845](https://stackoverflow.com/a/240308/3829845)

5. `extern "C"`:

    Overloading of function names is not supported in C. A function `void func(int, int)` would generate a function-name like `_func` by C compiler, but would be `_func_int_int` by C++ compiler. `extern "C"` makes sure that client C codes can link to the correct function.

6. Undefined behaviors:

    Pointer

    * Dereferencing a NULL pointer
    * Dereferencing a pointer returned by a "new" allocation of size zero
    * Using pointers to objects whose lifetime has ended (for instance, stack allocated objects or deleted objects)
    * Dereferencing a pointer that has not yet been definitely initialized
    * Performing pointer arithmetic that yields a result outside the boundaries (either above or below) of an array.
    * Dereferencing the pointer at a location beyond the end of an array.
    * Converting pointers to objects of incompatible types
    * Using memcpy to copy overlapping buffers.

    Buffer overflows

    * Reading or writing to an object or array at an offset that is negative, or beyond the size of that object (stack/heap overflow)

    Integer Overflows

    * Signed integer overflow
    * Evaluating an expression that is not mathematically defined
    * Left-shifting values by a negative amount (right shifts by negative amounts are implementation defined)
    * Shifting values by an amount greater than or equal to the number of bits in the number (e.g. int64_t i = 1; i <<= 72 is undefined)

    Types, Cast and Const

    * Casting a numeric value into a value that can't be represented by the target type (either directly or via   * static_cast)
    * Using an automatic variable before it has been definitely assigned (e.g., int i; i++; cout << i;)
    * Using the value of any object of type other than volatile or sig_atomic_t at the receipt of a signal
    * Attempting to modify a string literal or any other const object during its lifetime
    * Concatenating a narrow with a wide string literal during preprocessing

    Function and Template

    * Not returning a value from a value-returning function (directly or by flowing off from a try-block)
    * Multiple different definitions for the same entity (class, template, enumeration, inline function, static member function, etc.)
    * Infinite recursion in the instantiation of templates
    * Calling a function using different parameters or linkage to the parameters and linkage that the function is defined as using.

    OOP

    * Cascading destructions of objects with static storage duration
    * The result of assigning to partially overlapping objects
    * Recursively re-entering a function during the initialization of its static objects
    * Making virtual function calls to pure virtual functions of an object from its constructor or destructor
    * Referring to nonstatic members of objects that have not been constructed or have already been destructed

    Source file and Preprocessing

    * A non-empty source file that doesn't end with a newline, or ends with a backslash (prior to C++11)
    * A backslash followed by a character that is not part of the specified escape codes in a character or string constant (this is implementation-defined in C++11).
    * Exceeding implementation limits (number of nested blocks, number of functions in a program, available stack space ...)
    * Preprocessor numeric values that can't be represented by a long int
    * Preprocessing directive on the left side of a function-like macro definition
    * Dynamically generating the defined token in a #if expression

    To be classified

    * Calling exit during the destruction of a program with static storage duration

    [https://stackoverflow.com/a/367662/3829845](https://stackoverflow.com/a/367662/3829845)

7. Pass-by-pointer vs pass-by-reference:

    In passing-by-pointer, a `0` value can mean `pass no object` and serve and default argument.

8. Pysical/Bitwise constness vs Logical constness:

    "Physical" constness comes from declaring an object const, and could, in principle, be enforced by placing the object in read-only memory, so it cannot change. Attempting to change it will cause undefined behaviour.

    "Logical" constness comes from declaring a reference or pointer const, and is enforced by the compiler. The object itself may or may not be "physically" const, but the reference cannot be used to modify it without a cast. If the object is not "physically" const, then C++ allows you to modify it, using const_cast to circumvent the protection.

    [https://stackoverflow.com/a/3830484/3829845](https://stackoverflow.com/a/3830484/3829845)

9. Dangling, void, null and wild pointer

    * Dangling pointer: a pointer pointing to a memory location that has been deleted (or freed).
    * Void pointer: a pointer that points to some data location in storage, which doesn’t have any specific type.
    * NULL Pointer: a pointer which is pointing to nothing.
    * Wild pointer: a pointer which has not been initialized to anything (not even NULL).

10. Iterator invalidation rule:

    **Insertion**
    Sequence Containers

    * `vector`: The functions insert, emplace_back, emplace, push_back cause reallocation if the new size is greater than the old capacity. Reallocation invalidates all the references, pointers, and iterators referring to the elements in the sequence. If no reallocation happens, all the iterators and references before the insertion point remain valid. [26.3.11.5/1]
    With respect to the reserve function, reallocation invalidates all the references, pointers, and iterators referring to the elements in the sequence. No reallocation shall take place during insertions that happen after a call to reserve() until the time when an insertion would make the size of the vector greater than the value of capacity(). [26.3.11.3/6]

    * `deque`: An insertion in the middle of the deque invalidates all the iterators and references to elements of the deque. An insertion at either end of the deque invalidates all the iterators to the deque, but has no effect on the validity of references to elements of the deque. [26.3.8.4/1]

    * `list`: Does not affect the validity of iterators and references. If an exception is thrown there are no effects. [26.3.10.4/1].
    The insert, emplace_front, emplace_back, emplace, push_front, push_back functions are covered under this rule.

    * `forward_list`: None of the overloads of insert_after shall affect the validity of iterators and references [26.3.9.5/1]

    * `array`: As a rule, iterators to an array are never invalidated throughout the lifetime of the array. One should take note, however, that during swap, the iterator will continue to point to the same array element, and will thus change its value.

    Associative Containers

    * All Associative Containers: The insert and emplace members shall not affect the validity of iterators and references to the container [26.2.6/9]

    Unordered Associative Containers

    * All Unordered Associative Containers: Rehashing invalidates iterators, changes ordering between elements, and changes which buckets elements appear in, but does not invalidate pointers or references to elements. [26.2.7/9]
    The insert and emplace members shall not affect the validity of references to container elements, but may invalidate all iterators to the container. [26.2.7/14]
    The insert and emplace members shall not affect the validity of iterators if (N+n) <= z * B, where N is the number of elements in the container prior to the insert operation, n is the number of elements inserted, B is the container’s bucket count, and z is the container’s maximum load factor. [26.2.7/15]

    * All Unordered Associative Containers: In case of a merge operation (e.g., a.merge(a2)), iterators referring to the transferred elements and all iterators referring to a will be invalidated, but iterators to elements remaining in a2 will remain valid. (Table 91 — Unordered associative container requirements)

    Container Adaptors

    * `stack`: inherited from underlying container
    * `queue`: inherited from underlying container
    * `priority_queue`: inherited from underlying container

    **Erasure**
    Sequence Containers

    * `vector`: The functions erase and pop_back invalidate iterators and references at or after the point of the erase. [26.3.11.5/3]

    * `deque`: An erase operation that erases the last element of a deque invalidates only the past-the-end iterator and all iterators and references to the erased elements. An erase operation that erases the first element of a deque but not the last element invalidates only iterators and references to the erased elements. An erase operation that erases neither the first element nor the last element of a deque invalidates the past-the-end iterator and all iterators and references to all the elements of the deque. [ Note: pop_front and pop_back are erase operations. —end note ] [26.3.8.4/4]

    * `list`: Invalidates only the iterators and references to the erased elements. [26.3.10.4/3]. This applies to erase, pop_front, pop_back, clear functions.
    remove and remove_if member functions: Erases all the elements in the list referred by a list iterator i for which the following conditions hold: *i == value, pred(*i) != false. Invalidates only the iterators and references to the erased elements [26.3.10.5/15].
    unique member function - Erases all but the first element from every consecutive group of equal elements referred to by the iterator i in the range [first + 1, last) for which *i == *(i-1) (for the version of unique with no arguments) or pred(*i, *(i - 1)) (for the version of unique with a predicate argument) holds. Invalidates only the iterators and references to the erased elements. [26.3.10.5/19]

    * `forward_list`: erase_after shall invalidate only iterators and references to the erased elements. [26.3.9.5/1].
    remove and remove_if member functions - Erases all the elements in the list referred by a list iterator i for which the following conditions hold: *i == value (for remove()), pred(*i) is true (for remove_if()). Invalidates only the iterators and references to the erased elements. [26.3.9.6/12].
    unique member function - Erases all but the first element from every consecutive group of equal elements referred to by the iterator i in the range [first + 1, last) for which *i == *(i-1) (for the version with no arguments) or pred(*i, *(i - 1)) (for the version with a predicate argument) holds. Invalidates only the iterators and references to the erased elements. [26.3.9.6/16]

    * All Sequence Containers: clear invalidates all references, pointers, and iterators referring to the elements of a and may invalidate the past-the-end iterator (Table 87 — Sequence container requirements). But for forward_list, clear does not invalidate past-the-end iterators. [26.3.9.5/32]

    * All Sequence Containers: assign invalidates all references, pointers and iterators referring to the elements of the container. For vector and deque, also invalidates the past-the-end iterator. (Table 87 — Sequence container requirements)

    Associative Containers

    * All Associative Containers: The erase members shall invalidate only iterators and references to the erased elements [26.2.6/9]

    * All Associative Containers: The extract members invalidate only iterators to the removed element; pointers and references to the removed element remain valid [26.2.6/10]

    Container Adaptors

    * `stack`: inherited from underlying container
    * `queue`: inherited from underlying container
    * `priority_queue`: inherited from underlying container

    General container requirements relating to iterator invalidation:

    * Unless otherwise specified (either explicitly or by defining a function in terms of other functions), invoking a container member function or passing a container as an argument to a library function shall not invalidate iterators to, or change the values of, objects within that container. [26.2.1/12]

    * no swap() function invalidates any references, pointers, or iterators referring to the elements of the containers being swapped. [ Note: The end() iterator does not refer to any element, so it may be invalidated. —end note ] [26.2.1/(11.6)]

    As examples of the above requirements:

    * `transform` algorithm: The op and binary_op functions shall not invalidate iterators or subranges, or modify elements in the ranges [28.6.4/1]

    * `accumulate` algorithm: In the range [first, last], binary_op shall neither modify elements nor invalidate iterators or subranges [29.8.2/1]

    * `reduce` algorithm: binary_op shall neither invalidate iterators or subranges, nor modify elements in the range [first, last]. [29.8.3/5]

    [https://stackoverflow.com/a/54004916/3829845](https://stackoverflow.com/a/54004916/3829845)

11. `nullptr` vs `NULL`:

    `nullptr` is pointer type. `NULL` (which equals to `0`) can be ambiguous (i.e. `f(int)` vs `f(foo*)`)
