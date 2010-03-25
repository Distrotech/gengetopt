#include <string>
#include <iostream>

#include <gm_utils.h>

#include "asserttestexit.h"

using namespace std;

static void show_results(int result, int num_of_newlines) {
    cout << "result: " << result << endl;
    cout << "num_of_newlines: " << num_of_newlines << endl;
}

int main() {

    const string s = "this\n contains \t special chars";
    int num_of_newlines;

    int result = not_newlines(s, num_of_newlines);
    show_results(result, num_of_newlines);

    result = not_newlines("\n\nnew lines in front", num_of_newlines);
    show_results(result, num_of_newlines);

    result = not_newlines("\n", num_of_newlines);
    show_results(result, num_of_newlines);

    result = not_newlines("\\n", num_of_newlines);
    show_results(result, num_of_newlines);

    return 0;
}
