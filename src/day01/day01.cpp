#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <ranges>
#include <chrono>

namespace Day01 {
    namespace {
        struct Input {
            bool left;
            std::int32_t count;
        };

        auto GetParsedInput(const std::string_view input) {
            return input | std::views::split('\n') |
                   std::views::filter([](auto &&line) { return !line.empty(); }) |
                   std::views::transform([](auto &&line) {
                       const std::string lineStr{line.begin(), line.end()};
                       return Input{.left = lineStr.at(0) == 'L', .count = std::stoi(lineStr.substr(1))};
                   });
        }
    }

    std::int32_t Part1(const std::string_view input) {
        auto inputs = GetParsedInput(input);
        auto zeroes = 0;
        auto dial = 50;
        for (const auto [left, count]: inputs) {
            const auto turnAmount = left ? -count : count;
            dial += turnAmount;
            dial %= 100;
            if (dial == 0) {
                zeroes++;
            }
        }

        return zeroes;
    }

    std::int32_t Part2(const std::string_view input) {
        auto inputs = GetParsedInput(input);
        auto zeroes = 0;
        auto dial = 50;

        for (const auto [left, count]: inputs) {
            zeroes += count / 100;
            const auto turnAmount = count % 100;
            if (left) {
                dial -= turnAmount;
                if (dial < 0) {
                    if (dial + turnAmount != 0) {
                        zeroes++;
                    }
                    dial += 100;
                } else if (dial == 0) {
                    zeroes++;
                }
            } else {
                dial += turnAmount;
                if (dial >= 100) {
                    zeroes++;
                    dial -= 100;
                }
            }
        }

        return zeroes;
    }
}

auto RunPart(const std::int32_t part, auto function, std::string_view input) {
    using namespace std::chrono;

    const auto startTime = high_resolution_clock::now();
    const auto answer = function(input);
    const auto endTime = high_resolution_clock::now();

    std::println("Part {}: {} ({})", part, answer, duration_cast<microseconds>(endTime - startTime));
}

auto main() -> int {
    std::ifstream inputFile("input.txt");
    std::stringstream inputString;
    inputString << inputFile.rdbuf();

    RunPart(1, &Day01::Part1, inputString.str());
    RunPart(2, &Day01::Part2, inputString.str());

    return 0;
}


