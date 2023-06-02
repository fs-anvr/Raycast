#include <iostream>

#include "Engine/Result/Result.hpp"

int main() {
    auto res = fsanvr::Result<int>::Error("hehehe");

    res.Match([](auto value) {
        std::cout << "int: " << value << std::endl;
        }, [](auto error) {
        std::cout << "error: " << error << std::endl;
    });


    return 0;
}
