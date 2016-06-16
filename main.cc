#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include "object.h"


int main()
{
    std::ifstream file("test.txt");

    TextQuery tQuery(file);

    Query q = Query("wind");

    std::cout << q.eval(tQuery);

    return 0;
}
