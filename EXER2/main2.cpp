
#include "tests.hpp"

int main(int argc, char **argv, char **env)
{
    cout << "TEST INSERT INT ..." << endl;
    testInsertInt();

    cout << endl
         << "TEST INSERT STRING ..." << endl;
    testInsertString();

    cout << SEPERATOR << endl;
    cout << "MULTI THREADED TEST ..."
         << "\n\n";
    
    // multi threaded test ...
    HashMap<string, int> stringMap;
    thread thread1 (threadFunction1_StringKey, ref(stringMap));
    thread thread2 (threadFunction2_StringKey, ref(stringMap));

    thread1.join();
    thread2.join();

    cout << "main2.cpp -> main() exit ..." << endl;

    return 0;
}