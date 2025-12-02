#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <ranges>
#include <chrono>

namespace Day02 {
    namespace {
        struct Input {
            std::int64_t left;
            std::int64_t right;
        };

        auto GetParsedInput(const std::string_view input) {
            return input | std::views::split(',') | std::views::transform(
                [](auto&& subrange) {
                    std::cout << std::string(subrange.begin(), subrange.end()) << std::endl;
                    auto values = subrange | std::views::split('-') |
                        std::views::transform([](auto &&valRange) {
                            std::cout << std::string(valRange.begin(), valRange.end()) << std::endl;
                            return std::stoi(std::string{valRange.begin(), valRange.end()});
                        }
                    );

                    return Input{
                        .left = *values.begin(),
                        .right = *values.begin() + 1
                    };
                }
            );
        }
    }

    std::int32_t Part1(const std::string_view input) {
        auto inputs = GetParsedInput(input);

        for (auto value : inputs) {
            std::cout << value.left << ", " << value.right << std::endl;
        }

        return 0;
    }

    std::int32_t Part2(const std::string_view input) {
        return 0;
    }
}

auto RunPart(const std::int32_t part, auto function, std::string_view input) {
    using namespace std::chrono;

    const auto startTime = high_resolution_clock::now();
    const auto answer = function(input);
    const auto endTime = high_resolution_clock::now();

    std::println(std::cout, "Part {}: {} ({})", part, answer, duration_cast<microseconds>(endTime - startTime));
}

auto main() -> int {
    std::ifstream inputFile("input.txt");
    std::stringstream inputString;
    inputString << inputFile.rdbuf();

    RunPart(1, &Day02::Part1, inputString.str());
    RunPart(2, &Day02::Part2, inputString.str());

    return 0;
}


