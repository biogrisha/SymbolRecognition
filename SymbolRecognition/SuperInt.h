#pragma once
#include <vector>
#include <iostream>
#include <math.h>
class SuperInt
{
public:
	SuperInt(int maxSize, int initValue)
	{
		size = maxSize;
		IntBits = std::vector<bool>(maxSize, 0);
		int remainder;
		int i = 0;
		while (initValue > 0)
		{
			DivideWRemainder(initValue,2, initValue, remainder);
			IntBits[i] = remainder;
			i++;
		}
	}

	SuperInt Sum(const SuperInt& b)
	{
		
		int bSize = b.size;
		int maxSize = size < bSize ? bSize : size;

		SuperInt res(maxSize,0);
		bool el1 = false;
		bool el2 = false;
		bool sum = 0;
		bool remainder = 0;
		bool remainderTemp = 0;
		for (int i = 0; i < maxSize; i++)
		{
			if (i >= size)
			{
				el1 = 0;
			}
			else
			{
				el1 = IntBits[i];
			}
			
			if (i >= bSize)
			{
				el2 = 0;
			}
			else
			{
				el2 = b.IntBits[i];
			}

			remainderTemp = el1 && el2;
			
			if (!remainderTemp)
			{
				sum = el1 || el2;
				
				if (!(sum && remainder))
				{
					res.IntBits[i] = sum+ remainder;
					remainder = 0;
					
				}
				else
				{
					res.IntBits[i] = 0;
					remainder = 1;
				}
				

			}
			else
			{
				res.IntBits[i] =remainder;
				remainder = 1;

			}
			//rem = 1
			//0
			//0
			//1 rem 0
		}

		return res;
		
	}

	SuperInt Diff(const SuperInt& b)
	{
		bool biggest = 0;
		bool smallest = 0;

		int bSize = b.size;
		int maxSize = size < bSize ? bSize : size;

		SuperInt res(maxSize, 0);
		bool el1 = false;
		bool el2 = false;
		bool sum = 0;
		bool remainder = 0;
		bool remainderTemp = 0;
		int bBigger = 0;
		for (int i = maxSize-1; i >=0; i--)
		{
			if (i >= size)
			{
				el1 = 0;
			}
			else
			{
				el1 = IntBits[i];
			}

			if (i >= bSize)
			{
				el2 = 0;
			}
			else
			{
				el2 = b.IntBits[i];
			}

			if (el2 > el1)
			{
				bBigger = 1;
				break;
			}else if(el2 < el1)
			{
				bBigger = -1;
				break;
			}
		}
		if (bBigger != 0)
		{
			for (int i = 0; i < maxSize; i++)
			{
				if (i >= size)
				{
					el1 = 0;
				}
				else
				{
					el1 = IntBits[i];
				}

				if (i >= bSize)
				{
					el2 = 0;
				}
				else
				{
					el2 = b.IntBits[i];
				}

				if (bBigger == 1)
				{
					biggest = el2;
					smallest = el1;
				}
				else
				{
					biggest = el1;
					smallest = el2;
				}


				if (!(biggest || smallest))
				{
					if (remainder)
					{
						res.IntBits[i] = 1;
					}
					else
					{
						res.IntBits[i] = 0;
					}
					
				}

				if (biggest > smallest)
				{
					if (remainder)
					{
						res.IntBits[i] = 0;
						remainder = 0;
					}
					else
					{
						res.IntBits[i] = 1;
					}
				}
				else if(biggest < smallest)
				{
					if (remainder)
					{
						res.IntBits[i] = 0;
						remainder = 1;
					}
					else
					{
						res.IntBits[i] = 1;
						remainder = 1;
					}
				}


			}
		}
		return res;
		//rem 1
		//0
		//1
		//0 rem 1
	}

	void PrintBinary()
	{
		for (int i = 0; i < IntBits.size();i++)
		{
			if (IntBits[IntBits.size()-i-1])
				std::cout << 1;
			else
				std::cout << 0;
		}
	}

	void PrintDecimal()
	{
		int sum = 0;
		for (int i = 0; i < IntBits.size();i++)
		{
			if (IntBits[i])
			{
				sum += pow(2, i);
			}
		}

		std::cout << sum;
	}

private:
	std::vector<bool> IntBits;
	int size;
	void DivideWRemainder(int dividend, int divisor, int& quotient, int& remainder)
	{
		quotient = dividend / divisor;
		remainder = dividend % divisor;
		if (dividend < divisor)
		{
			remainder = 1;
		}
	}
};
