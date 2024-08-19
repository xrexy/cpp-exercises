# Running

Before running make sure you have all lib files (.dll for windows, and .so for linux)

```bash
❯ g++ main.cpp -Iinclude -Llib -lmultiply -o app
```

- If you're getting `./app: error while loading shared libraries: libmultiply.so: cannot open shared object file: No such file or directory` on Linux run this to fix it:

```bash
❯ export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
```
