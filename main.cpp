#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#define PROBABILITY 0.03

using namespace std;

int size_of_array(int n){
    return (int)-((double)n * log(PROBABILITY) / pow(log(2), 2));
}

int number_of_hashes(int n, int m){
    return (int)(((double)m / (double)n) * log(2));
}

uint64_t primary_hash(int num){
    auto a = (uint64_t)num;

    a = (a + 0x7ed55d16) + (a << 12);
    a = (a ^ 0xc761c23c) ^ (a >> 19);

    return a;
}

uint64_t secondary_hash(int num){
    auto a = (uint64_t)num;

    a = (a + 0xc761c23c) + (a << 12);
    a = (a ^ 0x7ed55d16) ^ (a >> 19);

    return a;
}

void add(vector<bool> &bloom_filter, int num, int n, int m) {
    uint64_t hash_1 = primary_hash(num);
    uint64_t hash_2 = secondary_hash(num);
    int k = number_of_hashes(n, m);

    for (int i = 0; i < k; ++i) {
        bloom_filter[(hash_1 + i * hash_2) % m] = true;
    }
}

bool check(vector<bool> &bloom_filter, int num, int n, int m) {
    uint64_t hash_1 = primary_hash(num);
    uint64_t hash_2 = secondary_hash(num);
    int k = number_of_hashes(n, m);

    for (int i = 0; i < k; ++i) {
        if (!bloom_filter[(hash_1 + i * hash_2) % m])
            return false;
    }
    return true;
}

void print(const vector<bool> &a) {
    for (auto elem : a) {
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    int n = 5;
    cout << "Enter the amount of numbers" << endl;
    cin >> n;
    int _n = n;
    int m = size_of_array(n);

    vector<bool> bloom_filter(m, false);

    cout << "You can type: \n"
            "add <number> \n"
            "check <number> \n"
            "check_array \n"
            "free" << endl;

    string user_in;
    int temp;
    while (cin >> user_in) {
        if (user_in == "add") {
            if (_n == 0) {
                cout << "The Bloom Filter is out of space!" << endl;
                break;
            }
            cin >> temp;
            add(bloom_filter, temp, n, m);
            _n--;
        }
        if (user_in == "check") {
            cin >> temp;
            if (check(bloom_filter, temp, n, m))
                cout << "Element probably exists" << endl;
            else
                cout << "Element probably does not exists" << endl;
        }
        if (user_in == "check_array") {
            print(bloom_filter);
        }
        if (user_in == "free"){
            cout << _n << endl;
        }
    }

    return 0;
}
