#include <cassert>
#include <string>
#include <string_view>
#include <type_traits>

using namespace std;

string get_string() {
    return string{"hello"};
}

void test() {
    string s{"hello"};
    string_view sv{"world"};

    {
        static_assert(is_same_v<decltype(s + sv), string>);
        assert(s + sv == "helloworld");
    }
    {
        static_assert(is_same_v<decltype(get_string() + sv), string>);
        assert(get_string() + sv == "helloworld");
    }
    {
        static_assert(is_same_v<decltype(sv + s), string>);
        assert(sv + s == "worldhello");
    }
    {
        static_assert(is_same_v<decltype(sv + get_string()), string>);
        assert(sv + get_string() == "worldhello");
    }
}

int main() {
    test();
}
