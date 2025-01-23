
#include "unordered_list.h"
#include <iostream>

int main() {
    std::string input_file = "src/words.txt";
    measure_lists(input_file); 
    
    return 0;
}

/*
#include "../src/unordered_list"
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
*/

/* Example of use

#include <iostream>
using namespace std;
#include "Timer.h"

int main()
{
    Timer t;
    double eTime;
    t.start();
    for (int i=0, j; i<1000000000; i++)
        j++;
    t.elapsedUserTime(eTime);
    cout << eTime << endl;
    return 0;
}
*/

