#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <ranges>
#include <chrono>

namespace Day02 {
    namespace {
        struct Range {
            std::int64_t left;
            std::int64_t right;
        };

        auto GetParsedInput(const std::string_view input) {
            return input | std::views::split(',') | std::views::transform(
                       [](auto &&subrange) {
                           auto values = subrange | std::views::split('-') |
                                         std::views::transform([](auto &&valRange) {
                                                 return std::stol(std::string{valRange.begin(), valRange.end()});
                                             }
                                         );

                           return Range{
                               .left = *values.begin(),
                               .right = *(++values.begin())
                           };
                       }
                   );
        }
    }

    std::int64_t Part1(const std::string_view input) {
        auto inputs = GetParsedInput(input);

        std::int64_t sum = 0;

        for (auto range: inputs) {
            for (std::int64_t tag = range.left; tag <= range.right; ++tag) {
                const std::string tagString = std::to_string(tag);
                if (tagString.size() % 2 == 0) {
                    std::string left = tagString.substr(0, tagString.size() / 2);
                    std::string right = tagString.substr(tagString.size() / 2);
                    if (left == right) {
                        sum += tag;
                    }
                }
            }
        }

        return sum;
        // 82308124 too low
    }

    std::int64_t Part2(const std::string_view input) {
        auto inputs = GetParsedInput(input);
        std::int64_t sum = 0;

        for (auto range: inputs) {
            for (std::int64_t tag = range.left; tag <= range.right; ++tag) {
                const std::string tagString = std::to_string(tag);
                for (auto i = 1; i < tagString.size(); ++i) {
                    if (i <= tagString.size() / 2) {
                        const std::string substring = tagString.substr(0, i);
                        bool invalid = true;
                        for (int j = i; j < tagString.size(); j += i) {
                            if (substring != tagString.substr(j, i)) {
                                invalid = false;
                                break;
                            }
                        }
                        if (invalid) {
                            sum += tag;
                            break;
                        }
                    }
                }
            }
        }

        return sum;
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


