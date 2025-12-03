#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <ranges>
#include <chrono>

namespace Day03 {
    namespace {
        auto GetParsedInput(const std::string_view input) {
            auto lines = input | std::views::split('\n');

            std::vector<std::vector<int> > result;

            for (auto line: lines) {
                auto view = line | std::views::transform([](auto &character) {
                    return stoi(std::string{character});
                });
                result.emplace_back(view.begin(), view.end());
            }

            return result;
        }
    }

    std::int64_t Part1(const std::string_view input) {
        auto banks = GetParsedInput(input);

        std::int64_t result = 0;
        for (const auto &bank: banks) {
            auto maxIter = std::max_element(bank.begin(), bank.end() - 1);
            auto nextMaxIter = std::max_element(maxIter + 1, bank.end());
            result += (*maxIter * 10) + *nextMaxIter;
        }
        return result;
    }

    std::int64_t Part2(const std::string_view input) {
        auto banks = GetParsedInput(input);

        std::int64_t result = 0;

        for (const auto &bank: banks) {
            constexpr size_t maxBatteries = 12;
            auto iter = bank.begin();
            for (size_t i = 0; i < maxBatteries; ++i) {
                iter = std::max_element(iter, bank.end() - (maxBatteries - (i + 1)));
                result += (*iter) * std::pow(10, maxBatteries - 1 - i);
                ++iter;
            }
        }
        return result;
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

    RunPart(1, &Day03::Part1, inputString.str());
    RunPart(2, &Day03::Part2, inputString.str());

    return 0;
}


