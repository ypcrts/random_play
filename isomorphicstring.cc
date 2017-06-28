#include <cassert>
#include <iterator>
#include <cstdio>
#include <cerrno>
#include <iostream>
#include <unordered_map>

extern int errno;

bool isomorphic(const char *a, const char *b);
int main(const int argc, const char **argv) 
{
  bool ret; 

  if (argc != 3) {
    errno = EINVAL;
    std::perror("fatal");
    return 1;
  }

  ret = isomorphic(argv[1], argv[2]);
  if (ret) {
    std::cout << "isomorphic" << std::endl;
  }
  else {
    std::cout << "not isomorphic" << std::endl;
  }
  return ret;
}

bool isomorphic(const char *a, const char *b)
{
  int len = strlen(a);
  std::unordered_map<char, char> m;

  if (len != strlen(b))
    return false;

  for (int i=0; i < len; ++i) {
#ifdef DEBUG
    for (auto all_iter = m.begin(); all_iter != m.end(); all_iter++) {
      std::cout << all_iter->first << " -> " << all_iter->second << std::endl;
    }
#endif
    auto find_iter = m.find(a[i]);
    if (find_iter == m.end()) {
      // not found in map

      // ensure nothing else maps to b[i]
      for (auto all_iter = m.begin(); all_iter != m.end(); all_iter++) {
        if (all_iter->second == b[i])
          return false;
      }
      m.emplace(a[i], b[i]);
    } else {
      // found in map
      assert(find_iter->first == a[i]);
      if (find_iter->second != b[i])
        return false;
    }
  }

  return true;
}
