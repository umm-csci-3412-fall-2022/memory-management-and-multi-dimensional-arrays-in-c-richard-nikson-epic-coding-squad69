# Tips and suggestions <!-- omit in toc -->

This contains some general comments, tip, and suggestions for this lab.

- [Correctness](#correctness)
- [Style and clarity: The big issues](#style-and-clarity-the-big-issues)
- [Style and clarity: Odds and ends](#style-and-clarity-odds-and-ends)
- [Algorithmic issues](#algorithmic-issues)

## Correctness

The one non-subtle issue that has come more than once is
    people simply failing to free temporary memory they'd allocated.
    `valgrind` is very good about catching these kinds of problems, so
    there's really no reason for not finding and fixing those problems.

There has been a strong inverse correlation between length and
    correctness. Broken `array_merge` submissions often run
    well onto the second page, where the correct ones almost all fit
    nicely on a single page. This may be partly due to the increased
    tendency of broken programs to have print code and commented code,
    but probably more generally reflects a lack of clarity.

People often get lost in their array indices, and some remain
    lost there throughout. This is a nice example of a problem where
    loop invariants could be really useful in helping you stay clear
    about what you know and where.

Folks often use a variable before they initialized it.
    Typically this was a counter that needed to be initialized to 0, but
    never was. Unlike Java, C makes no promises about how variables will
    be initialized, so you have to make sure that you initialize them
    properly. (One can make a strong case for not assuming any
    particular initialization in Java and being explicit about it there
    as well.) Unfortunately leaving out initialization like this can be
    very tricky to find, because tests can (often) pass and code can
    (usually) appear to work just fine since the initial value of that
    variable can depend on what other function calls have been made and
    what values they've left behind in memory.

Groups often have off-by-one errors where they weren't allocating
    space the null terminator on their result strings. If, for example,
    you know you need enough space to store a string of N characters,
    you need to make sure that you allocate *N+1* characters so there's
    room for the null terminator at the end. This can be tricky to find
    because the tests may actually pass even if you make this make this
    mistake. `valgrind` picks it up, though, and complains about
    illegal reads and writes when we try to access the memory location
    where the null terminator would need to be, but which we never
    allocated space for.

<!--
(To be honest, I'm not entirely sure *why* the tests pass.
    I assume that somehow we're getting lucky and getting a 0 byte at
    the end of our strings. I suspect that if we dug around some we
    could come up with a test that would fail, but I haven't been able
    to do so yet.)
-->

We have sometimes seen a subtle mistake where folks went through something like the following sequence of steps:

1. Dynamically allocate an array that was potentially empty (because *n=0*): `int *a = calloc(n, sizeof(int));`.
2. Copy some data into that array using a loop that (correctly) did nothing if *n=0*.
3. Access the first item in the array, which might not actually be there, e.g., `int i = a[0];`.
4. Protect the remainder of the code (through an `if` or loop with appropriate bounds) so that the value taken from the array was never *used* if n=0.

This is broken since the line `int i = a[0];` is accessing a
memory location that hasn't been allocated to your program. It's
probably a legal memory address, though, so it's unlikely to actually
*fail*. And since the subsequent guards ensure that you never actually
use the (probably random) value that you got back, there probably aren't
any tests that will actually catch the mistake. Luckily `valgrind` catches
it, complaining about an illegal read.

## Style and clarity: The big issues

Please use decent variable names! C is a challenging language and
    can be very hard to debug; don't make it worse by using charming
    names like `result`, `res2`, and `res3` (`res3` is what's actually
    returned, BTW) or `temp` and `temp2`.

Initialize variables where you use them. Several people declared
    them and initialized a variable up top, but then didn't use it for
    3/4 of a page. This leaves the reader to hunt through the
    intervening code to make sure it wasn't changed somewhere in
    between. (Breaking things up into smaller functions would do much to
    lessen this problem - see below.)

Use functions to break things up! Many of the submissions have
    `array_merge` as a single function that went on for over a page. Several people have a
    second function that looks for duplicates, which is nice, but that
    was about it by way of modularity for most folks. Remember the bit
    about C being a challenging language, and not making it worse?
    Applies here, too. A nice rule of thumb (for any language) is that a
    function should have at most one loop. Almost everyone had at least
    three loops in their `array_merge` function, with several people
    getting as high as 6. I'd have a look at that if I were you.

## Style and clarity: Odds and ends

You should remove printing code from "production" code (i.e.,
    working code that you turn in).

Don't `#include` `.c` files; you want to compile `.c` files
    separately and link them in. (If this is confusing or unclear to
    you, then you definitely should ask a question about it.) Because
    `#include` is a purely textual operation, it will *work* on `*.c`
    files, or `*.java`, or `*.rb`, or random JPEGs, but most of those
    aren't good ideas. What one typically does is *only* include
    the `*.h` files which provide the headers, but none of the
    implementation details. You then compile all the `*.c` files,
    as they provided the needed implementations, and the
    linker pulls them all together into a working executable.

Pay attention to warnings, and ask if you don't understand what it's
    saying. There are often cases where the compiler warnings pointed
    right to the problem.

Use C's `bool` type (with values `true` and `false`) instead of `int`s
with the values 0 and 1. Booleans are a lot more readable and less error
prone.

## Algorithmic issues

People have often used a variant of linear search to see if an item was
    duplicated. Use the fact that your array is sorted (or go ahead and
    sort it if it isn't) to simplify this (and speed it up, but the
    simplicity is arguably the bigger issue).
