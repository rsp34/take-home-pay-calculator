# Feedback

## Style Guidelines
1. Getters and setters are not used in C++. This is closer to Java.

## To Do
- Class not necessary for personal allowance - store the int in tax code and change the getPersonalAllowance method.
- Tax code should have it's own copy rather than using a reference.
- Return not as reference and not as const as this makes the interface hard to use.

## Learning Topics
- References are for efficiency and passing data back and forth

### When to use references

### When to use pointers
- More than 8-bytes use a pointer for speed.

### How should project be structured
- Target link libary
- Static vs dynamic linking
Each CPP file is compiled separately
- Header files expose acros - it's just copying into the top. hence the name.
- Slower compilation for header libraries
- Splitting cpp files enables individual units to be compiled.
- COmpilation units.
- Libraries have a separate include so you can separately give the header files.

Expose a C interface.

Write a header file.

In C++ you forward declare what you need. C++ the order matters.

Maybe add namespaces down the line.

Global namespace + anonymous namespace.

BY default, we get the the default destructor.

Default destructor is not marked as virtual.

Classes inheriting from here just keeps the destructor from this class.

spdlog an argument parse

`typdef int myLongNamedInt`