#include "Random.h"
#include <iostream>
#include <vector>

using Numbers = std::vector<int>;

namespace config
{
	constexpr int multiplierMin{ 2 };
	constexpr int multiplierMax{ 4 };
	constexpr int maxWrongDistance{ 4 };
}

Numbers generateNumbers(int start, int count, int multiplier)
{
	Numbers numbers(static_cast<Numbers::size_type>(count));
	int i{ start };
	for (auto& number : numbers)
	{
		number = i * i * multiplier;
		++i;
	}
	return numbers;
}

int findClosest(const Numbers& numbers, int guess)
{
	return *std::min_element(numbers.begin(), numbers.end(),
		[=](int a, int b) {
			return std::abs(a - guess) < std::abs(b - guess);
		});
}

int main()
{
	// before game
	std::cout << "Start where? ";
	int start{};
	std::cin >> start;
	std::cout << "How many? ";
	int count{};
	std::cin >> count;
	int multiplier{ Random::get(config::multiplierMin, config::multiplierMax) };
	std::cout << "I generated " << count << " square numbers. "
		<< "Do you know what each number is after multiplying it by "
		<< multiplier << "?\n";
	Numbers numbers{ generateNumbers(start, count, multiplier) };

	// in game
	while (!numbers.empty())
	{
		std::cout << "> ";
		int guess{};
		std::cin >> guess;
		auto found{ std::find(numbers.begin(), numbers.end(), guess) };
		if (found != numbers.end())
		{
			numbers.erase(found);
			std::cout << "Nice! ";
			if (numbers.empty())
				std::cout << "You found all numbers, good job!\n";
			else
				std::cout << std::ssize(numbers) << " number(s) left.\n";
		}
		else
		{
			std::cout << guess << " is wrong!";
			int closest{ findClosest(numbers, guess) };
			if (std::abs(closest - guess) <= config::maxWrongDistance)
				std::cout << " Try " << closest << " next time.";
			std::cout << '\n';
		}
	}
	return 0;
}