# mdsa_url
The project mainly solves the problem of searching for the same IP in massive files.

## Description:

1. You should run `generate_url.cpp` first.
``` bash
g++ generate_url.cpp -o gurl
./gurl
```
2. Create a `split_file` directory to hold small files
```bash
mkdir split_file
```
3. Run `hash_split_file.cpp` to hash massive files into small files that can be stored in memory. And run `set_file.cpp` to find a small file union.
```bash
g++ hash_split_file.cpp -o hsf
./hsf
g++ set_file.cpp -o sf
./sf
```
4. You can see a `same_url.txt` file and it is the result.
```bash
vim same_url.txt
```


---

- bkdr_hash.cpp
Hash a string as a number.

- generate_url.cpp
Generate URLs that match the url rules (letters, numbers, and '-').

- hash_splite_file.cpp
Hash massive files into small files that are readable by memory.

- list_file_name.cpp
C++ lists all the files in the directory.

- set_file.cpp
Use set to find the union and get the same URL in the small file.


