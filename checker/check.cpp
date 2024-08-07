#include <cstdlib>
#include <string>
using  namespace std;

int main() {
    for (int i = 5; i <= 30; ++i) {
        string maker = "python maker.py > main_input" + to_string(i) + ".txt";
        string checker = "./std < main_input" + to_string(i) + ".txt > main_output" + to_string(i) + ".txt";
        system(maker.c_str());
        system(checker.c_str());
    } 
    return 0;
}
