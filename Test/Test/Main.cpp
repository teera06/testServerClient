#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::vector<std::vector<int>> triangleDP;
	int result = 0;

	int n;

	std::cin >> n;

	triangleDP.resize(n);

	for (size_t i = 0; i < n; i++)
	{
		int index = static_cast<int>(i);
		triangleDP[index].resize(index + 1);
		for (size_t j = 0; j < index+1; j++)
		{
			int num;
			std::cin >> num;

			triangleDP[index][static_cast<int>(j)] = num;
		}
	}

	result = triangleDP[0][0];

	for (size_t i = 1; i < n; i++)
	{
		int indexi = static_cast<int>(i);
		for (size_t j = 0; j <=indexi; j++)
		{
			int indexj = static_cast<int>(j);

			if (indexj == 0)
			{
				triangleDP[indexi][indexj] += triangleDP[indexi - 1][indexj];
			}
			else if (indexj == indexi)
			{
				triangleDP[indexi][indexj] += triangleDP[indexi - 1][indexj-1];
			}
			else
			{
				triangleDP[indexi][indexj] += std::max(triangleDP[indexi - 1][indexj], triangleDP[indexi - 1][indexj - 1]);
			}

			if (n - 1 == indexi)
			{
				result = std::max(result, triangleDP[indexi][indexj]);
			}	
		}
	}

	std::cout << result;

}