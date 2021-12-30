/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conversion.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 09:48:32 by lle-briq          #+#    #+#             */
/*   Updated: 2021/12/30 11:01:03 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conversion.hpp"

/*
**		CONSTRUCTORS AND DESTRUCTOR
*/

Conversion::Conversion(void) :
	_charConvOk(false), _intConvOk(false), _floatConvOk(false), _doubleConvOk(false),
	_charValue(0), _intValue(0), _floatValue(0.0f), _doubleValue(0.0f),
	_isLimitBool(false), _limit(""), _stringError(false), _outOfRange(false),
	_zeroDec(true)
{
	return ;
}

static bool	isOutOfRange(double value, int type)
{
	if (type == FLOAT)
		return (value < -std::numeric_limits<float>::max() || value > std::numeric_limits<float>::max());
	if (type == INT)
		return (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max());
	else
		return (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max());
}

Conversion::Conversion(const char *value) : 
	_charConvOk(false), _intConvOk(false), _floatConvOk(false), _doubleConvOk(false),
	_charValue(0), _intValue(0), _floatValue(0.0f), _doubleValue(0.0f),
	_isLimitBool(false), _limit(""), _stringError(false), _outOfRange(false),
	_zeroDec(true)
{
	char	*end;
	bool	isChar;

	if (_isLimit(value))
		return ;
	isChar = (value[0] && !value[1]);
	if (!isChar)
	{
		_doubleValue = strtod(value, &end);
		if (errno == ERANGE)
		{
			_outOfRange = true;
			return ;
		}
		if (value == end || _badFormat(value))
		{
			_stringError = true;
			return ;
		}
	}
	else
		_doubleValue = static_cast<double>(value[0]);
	_doubleConvOk = true;
	if (!isOutOfRange(_doubleValue, FLOAT))
	{
		_floatValue = static_cast<float>(_doubleValue);
		_floatConvOk = true;
	}
	if (!isOutOfRange(_doubleValue, INT))
	{
		_intValue = static_cast<int>(_doubleValue);
		_intConvOk = true;
	}
	if (!isOutOfRange(_doubleValue, CHAR))
	{
		_charValue = static_cast<char>(_doubleValue);
		_charConvOk = true;
	}

}

Conversion::Conversion(const Conversion &conversion)
{
	*this = conversion;
}

Conversion::~Conversion()
{
	return ;
}

/*
**		OVERLOAD OPERATORS
*/

Conversion	&Conversion::operator=(const Conversion &conversion)
{
	if (this != &conversion)
	{
		_charConvOk = conversion._charConvOk;
		_intConvOk = conversion._intConvOk;
		_floatConvOk = conversion._floatConvOk;
		_doubleConvOk = conversion._doubleConvOk;
		_charValue = conversion._charValue;
		_intValue = conversion._intValue;
		_floatValue = conversion._floatValue;
		_doubleConvOk = conversion._doubleConvOk;
	}
	return (*this);
}

std::ostream	&operator<<(std::ostream &o, const Conversion &conversion)
{
	if (conversion.getOutOfRange())
		std::cerr << "Error: values out of range" << std::endl;
	else if (conversion.getStringError())
		std::cerr << "Error: string format error" << std::endl;
	else
	{
		conversion.printChar();
		conversion.printInt();
		conversion.printFloat();
		conversion.printDouble();
	}
	return (o);
};

/*
**		MEMBER FUNCTIONS
*/

void	Conversion::printChar(void) const
{
	std::cout << "char: ";
	if (!_charConvOk)
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	if (_charValue > 31 && _charValue < 127)
		std::cout << "'" << _charValue << "'" << std::endl;
	else
		std::cout << "non displayable" << std::endl;
}

void	Conversion::printInt(void) const
{
	std::cout << "int: ";
	if (!_intConvOk)
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	std::cout << _intValue << std::endl;
}

void	Conversion::printFloat(void) const
{
	std::cout << "float: ";
	if (!_floatConvOk)
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	if (_isLimitBool)
		std::cout << _limit + "f" << std::endl;
	else
	{
		std::cout << _floatValue;
		if (_zeroDec)
			std::cout << ".0";
		std::cout << "f" << std::endl;
	}
}

void	Conversion::printDouble(void) const
{
	std::cout << "double: ";
	if (!_doubleConvOk)
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	if (_isLimitBool)
		std::cout << _limit << std::endl;
	else
	{
		std::cout << _doubleValue;
		if (_zeroDec)
			std::cout << ".0";
		std::cout << std::endl;
	}
}

bool	Conversion::_isLimit(const char *value)
{

	const std::string	limits[4] = {"inf" , "+inf", "-inf", "nan"};

	for (int i = 0; i < 4; i++)
	{
		if (value == limits[i] || value == (limits[i] + "f"))
		{
			_isLimitBool = true;
			_limit = limits[i];
			_floatConvOk = true;
			_doubleConvOk = true;
			return (true);
		}
	}
	return (false);
}

bool	Conversion::getOutOfRange(void) const
{
	return (_outOfRange);
}

bool	Conversion::getStringError(void) const
{
	return (_stringError);
}

bool	Conversion::_badFormat(const char *value)
{
	int	i;

	i = 0;
	if (value[i] == '-' || value[i] == '+')
		i++;
	while (value[i] && value[i] >= '0' && value[i] <= '9')
		i++;
	if (value[i] == '.')
		i++;
	while (value[i] && value[i] >= '0' && value[i] <= '9')
	{
		if (value[i] != '0')
			_zeroDec = false;
		i++;
	}
	if (value[i] == 'e' && value[i + 1] && value[i + 1] == '+')
		i += 2;
	while (value[i] && value[i] >= '0' && value[i] <= '9')
		i++;
	if (value[i] == 'f')
		i++;
	return (value[i] != '\0');
}
