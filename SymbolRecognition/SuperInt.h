#pragma once
#include <vector>
#include <algorithm>
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
			if (remainder == 1)
			{
				biggestPos = i;
			}
			i++;
		}
	}

	SuperInt(const std::vector<bool> &number)
	{
		size = number.size();
		for (int i = size-1; i >=0;i++)
		{
			if (number[i])
			{
				biggestPos = i;
				break;
			}
		}

		IntBits = number;


	}

	SuperInt Sum(const SuperInt& b)
	{
		
		int bSize = b.size;
		int maxSize = biggestPos > b.biggestPos ? biggestPos : b.biggestPos;
		maxSize+=2;

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

			if (res.IntBits[i] == 1)
			{
				res.biggestPos = i;
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
		int maxSize = biggestPos > b.biggestPos ? biggestPos : b.biggestPos;
		maxSize += 2;
		SuperInt res(maxSize, 0);
		bool el1 = false;
		bool el2 = false;
		bool sum = 0;
		bool remainder = 0;
		bool remainderTemp = 0;
		int bBigger = Compare(b);
		
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
					
				}else if (biggest > smallest)
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
				else if(biggest == smallest)
				{
					if (remainder)
					{
						res.IntBits[i] = 1;
						remainder = 1;
					}
					else
					{
						res.IntBits[i] = 0;
						remainder = 0;
					}
				}

				if (res.IntBits[i] == 1)
				{
					res.biggestPos = i;
				}
			}
		}
		return res;
		//rem 1
		//0
		//1
		//0 rem 1
	}

	void Decr(const SuperInt& b)
	{
		bool biggest = 0;
		bool smallest = 0;

		int bSize = b.size;
		int maxSize = biggestPos > b.biggestPos ? biggestPos : b.biggestPos;
		maxSize ++;
		bool el1 = false;
		bool el2 = false;
		bool sum = 0;
		bool remainder = 0;
		bool remainderTemp = 0;
		int bBigger = Compare(b);
		biggestPos = 0;
		if (bBigger < 0)
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
						IntBits[i] = 1;
					}
					else
					{
						IntBits[i] = 0;
					}

				}
				else if (biggest > smallest)
				{
					if (remainder)
					{
						IntBits[i] = 0;
						remainder = 0;
					}
					else
					{
						IntBits[i] = 1;
					}
				}
				else if (biggest < smallest)
				{
					if (remainder)
					{
						IntBits[i] = 0;
						remainder = 1;
					}
					else
					{
						IntBits[i] = 1;
						remainder = 1;
					}
				}
				else if (biggest == smallest)
				{
					if (remainder)
					{
						IntBits[i] = 1;
						remainder = 1;
					}
					else
					{
						IntBits[i] = 0;
						remainder = 0;
					}
				}

				if (IntBits[i] == 1)
				{
					biggestPos = i;
				}
			}
		}
		else if (bBigger == 0)
		{
			std::fill(IntBits.begin(), IntBits.begin() + size, false);
		}
		
		std::fill(IntBits.begin() + biggestPos+1, IntBits.begin() + size, false);
	}

	SuperInt Mult(const SuperInt& b)
	{

		int maxSize = biggestPos > b.biggestPos ? biggestPos : b.biggestPos;
		maxSize++;
		maxSize *= 2;
		SuperInt res(maxSize, 0);
		std::vector<unsigned int> tempRes(maxSize, 0);
		for (int i = 0; i <= b.biggestPos; i++)
		{
			if (b.IntBits[i])
			{
				for (int j = 0; j <= biggestPos; j++)
				{
					tempRes[j + i] += IntBits[j];
				}
			}
		}

		int bit = 0;
		int remainder = 0;

		for (int i = 0; i < maxSize; i++)
		{
			remainder += tempRes[i];
			bit = remainder % 2;
			res.IntBits[i] = bit;
			remainder = (remainder - bit) / 2;
			if (bit == 1)
			{
				res.biggestPos = i;
			}
		}

		if (!res.IntBits.back())
		{
			res.IntBits.erase(res.IntBits.begin() + res.biggestPos+1, res.IntBits.end()-1);
			res.size -= res.size - (res.biggestPos+1);
		}
		return res;
	}

	SuperInt Div(SuperInt b)
	{
		int bBigger = Compare(b);
		int retSize = biggestPos - b.biggestPos;
		if (retSize < 1)
		{
			retSize = 1;
		}
		SuperInt ret(retSize+1, 0);
		SuperInt zero(2, 0);
		if (b > zero)
		{
			ret.biggestPos = 0;
			b.IntBits.insert(b.IntBits.begin(), retSize, false);
			b.biggestPos += retSize;
			b.size += retSize;
			SuperInt temp = *this;

			if (bBigger < 0)
			{
				int i = 0;
				while (retSize>=i)
				{
					bBigger = temp.Compare(b);
					if (bBigger <= 0)
					{
						ret.IntBits[retSize - i] = 1;
						temp.Decr(b);
						if (ret.biggestPos == 0)
						{
							ret.biggestPos = retSize - i;
						}
					}
					else
					{
						ret.IntBits[retSize - i] = 0;
					}
					b.IntBits.erase(b.IntBits.begin());
					b.biggestPos--;
					i++;
				}
			}
			else if (bBigger == 0)
			{
				ret.IntBits[0] = 1;
			}
		}
		return ret;
	}

	int Compare(const SuperInt& b)
	{
		int res = 0;
		if (b.biggestPos > biggestPos)
		{
			res = 1;
		}
		else if (b.biggestPos < biggestPos)
		{
			res = -1;
		}
		else
		{
			for (int i = biggestPos; i >= 0; i--)
			{
				

				if (b.IntBits[i] > IntBits[i])
				{
					res = 1;
					break;
				}
				else if (b.IntBits[i] < IntBits[i])
				{
					res = -1;
					break;
				}
			}
		}
		
		return res;
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


	bool operator>(const SuperInt& b)
	{
		bool res = false;
		int compRes = Compare(b);
		switch (compRes)
		{
		case -1:
			res = true;
			break;
		case 1:
			res = false;
			break;
		default:
			break;
		}
		return res;
	}
private:
	std::vector<bool> IntBits;
	int size;
	int biggestPos;
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
