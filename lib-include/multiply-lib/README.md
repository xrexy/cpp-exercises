# Building

First, build the object file

```bash
❯ g++ -c -fPIC multiply.cpp -o multiply.o
```

Then build the lib files (.so for linux, .dll for windows)

```bash
# Linux
❯ g++ -shared -o libmultiply.so multiply.o

# Windows (with MinGW)
❯ g++ -shared -o libmultiply.dll multiply.o
```
