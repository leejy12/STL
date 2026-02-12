// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <cassert>
#include <string>
#include <string_view>
#include <type_traits>

using namespace std;

struct convertible_to_string_view {
public:
    constexpr operator string_view() const {
        return string_view{"world"};
    }
};

constexpr string get_string() {
    return string{"hello"};
}

constexpr bool test() {
    string s{"hello"};
    string_view sv{"world"};
    convertible_to_string_view ctsv{};

    {
        static_assert(is_same_v<decltype(s + sv), string>);
        assert(s + sv == "helloworld");

        static_assert(is_same_v<decltype(s + ctsv), string>);
        assert(s + ctsv == "helloworld");
    }
    {
        static_assert(is_same_v<decltype(get_string() + sv), string>);
        assert(get_string() + sv == "helloworld");

        static_assert(is_same_v<decltype(get_string() + ctsv), string>);
        assert(get_string() + ctsv == "helloworld");
    }
    {
        static_assert(is_same_v<decltype(sv + s), string>);
        assert(sv + s == "worldhello");

        static_assert(is_same_v<decltype(ctsv + s), string>);
        assert(ctsv + s == "worldhello");
    }
    {
        static_assert(is_same_v<decltype(sv + get_string()), string>);
        assert(sv + get_string() == "worldhello");

        static_assert(is_same_v<decltype(ctsv + get_string()), string>);
        assert(ctsv + get_string() == "worldhello");
    }

    return true;
}

int main() {
    static_assert(test());
    test();
}
