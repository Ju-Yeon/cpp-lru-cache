cpp-lru-cache
=============

Fork a simple LRU cache (https://github.com/lamerman/cpp-lru-cache)
and extend with new function that add set-associative mapping function.


How to run another tests:


There are 3 type of test in src file. First, 'sequential_test_direct' is original test code that write and read sequential data with direct cache. And 'random_test_direct' is test code that read and write random data with direct cache. Last, 'random_test_setAssociative' is test code that read and write random data with set-associative cache. You shoud modify 'add_executable' object from 'CMakeList.txt'.

```
//CMakeList.txt

add_executable(
cpp-lru-cache-test
src/sequential_test_dircet)

```

The default of project is 'sequential_test_direct'. And also you can change the number of way of cache in 'include/lrucache_setAssociative'. Thx :)




Simple and reliable LRU (Least Recently Used) cache for c++ based on hashmap and linkedlist. The library is header only, simple test and example are included.
It includes standard components and very little own logics that guarantees reliability.

Example:

```
/**Creates cache with maximum size of three. When the 
   size in achieved every next element will replace the 
   least recently used one */
cache::lru_cache<std::string, std::string> cache(3);

cache.put("one", "one");
cache.put("two", "two");

const std::string& from_cache = cache.get("two")

```

How to run tests:

```
mkdir build
cd build
cmake ..
make check
```

