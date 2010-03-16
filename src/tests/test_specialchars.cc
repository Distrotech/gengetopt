#include <string>
#include <iostream>

#include <gm_utils.h>

#include "asserttestexit.h"

using namespace std;

int main() {

  const string s = "this\n contains \t special chars";

  bool result = char_is_newline(s);
  assertEquals(false, result);

  result = char_is_newline("\\n");
  assertEquals(true, result);

  return 0;
}
