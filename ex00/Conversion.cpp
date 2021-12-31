/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conversion.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 09:48:32 by lle-briq          #+#    #+#             */
/*   Updated: 2021/12/31 01:10:19 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conversion.hpp"

/*
**		CONSTRUCTORS AND DESTRUCTOR
*/

Conversion::Conversion(void) :
	_charConvOk(false), _intConvOk(false), _floatConvOk(false), _doubleConvOk(false),
	_charValue(0), _intValue(0), _floatValue(0.0f), _doubleValue(0.0f),
	_isLimitBool(false), _limit(""), _stringError(false), _zeroDec(true)
{
	return ;
}

Conversion::Conversion(const char *value) : 
	_charConvOk(false), _intConvOk(false), _floatConvOk(false), _doubleConvOk(false),
	_charValue(0), _intValue(0), _floatValue(0.0f), _doubleValue(0.0f),
	_isLimitBool(false), _limit(""), _stringError(false), _zeroDec(true)
{
	int				type;
	convFunction	conversions[4] = {&Conversion::_convFromChar, &Conversion::_convFromInt,
									&Conversion::_convFromFloat, &Conversion::_convFromDouble};
	if (_isLimit(value))
		return ;
	type = _getType(value);
	if (type == Conversion::wrongType)
		_stringError = true;
	else
		(this->*(conversions[type]))(value);
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
	(void)conversion;
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

int	Conversion::_getType(const char *value)
{
	int		i;
	bool	isInteger = true;
	bool	isFloat = false;

	i = 0;
	if (value[0] && value[1] == '\0')
		return (Conversion::charType);
	if (value[i] == '-' || value[i] == '+')
		i++;
	while (value[i] && value[i] >= '0' && value[i] <= '9')
		i++;
	if (value[i] == '.')
	{
		isInteger = false;
		i++;
		while (value[i] && value[i] >= '0' && value[i] <= '9')
		{
			if (value[i] != '0')
				_zeroDec = false;
			i++;
		}
	}
	if (value[i] == 'f')
	{
		isFloat = true;
		i++;
	}
	if (value[i])
		return (Conversion::wrongType);
	if (isFloat)
		return (Conversion::floatType);
	if (isInteger)
		return (Conversion::intType);
	return (Conversion::doubleType);
}

static bool	isOutOfRange(double value, int type)
{
	if (type == Conversion::floatType)
		return (value < -std::numeric_limits<float>::max() || value > std::numeric_limits<float>::max());
	if (type == Conversion::intType)
		return (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max());
	if (type == Conversion::charType)
		return (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max());
	return (true);
}

void	Conversion::_convFromChar(const char *value)
{
	_charValue = value[0];
	_charConvOk = true;
	_intValue = static_cast<int>(_charValue);
	_intConvOk = true;
	_floatValue = static_cast<float>(_charValue);
	_floatConvOk = true;
	_doubleValue = static_cast<double>(_charValue);
	_doubleConvOk = true;
}

void	Conversion::_convFromInt(const char *value)
{
	if ((strlen(value) == 10 && strcmp(value, "2147483647") > 0)
		|| (value[0] == '-' && strlen(value) == 11 && strcmp(value + 1, "2147483648") > 0)
		|| (value[0] == '+' && strlen(value) == 11 && strcmp(value + 1, "2147483647") > 0))
	{
		_outOfRange = true;
		return ;
	}
	_intValue = atoi(value);
	_intConvOk = true;
	_floatValue = static_cast<float>(_intValue);
	_floatConvOk = true;
	_doubleValue = static_cast<double>(_intValue);
	_doubleConvOk = true;
	if (!isOutOfRange(_doubleValue, Conversion::charType))
	{
		_charValue = static_cast<char>(_intValue);
		_charConvOk = true;
	}
}

void	Conversion::_convFromFloat(const char *value)
{
	char	*end = NULL;

	_floatValue =  std::strtof(value, &end);
	if (value == end)
	{
		_stringError = true;
		return ;
	}
	if (errno == ERANGE)
	{
		_outOfRange = true;
		return ;
	}
	_floatConvOk = true;
	_doubleValue = static_cast<double>(_floatValue);
	_doubleConvOk = true;
	if (!isOutOfRange(_doubleValue, Conversion::intType))
	{
		_intValue = static_cast<int>(_floatValue);
		_intConvOk = true;
	}
	if (!isOutOfRange(_doubleValue, Conversion::charType))
	{
		_charValue = static_cast<char>(_floatValue);
		_charConvOk = true;
	}
}

void	Conversion::_convFromDouble(const char *value)
{
	char	*end;

	_doubleValue = std::strtod(value, &end);
	if (value == end)
	{
		_stringError = true;
		return ;
	}
	if (errno == ERANGE)
	{
		_outOfRange = true;
		return ;
	}
	_doubleConvOk = true;
	if (!isOutOfRange(_doubleValue, Conversion::floatType))
	{
		_floatValue =  static_cast<float>(_doubleValue);
		_floatConvOk = true;
	}
	if (!isOutOfRange(_doubleValue, Conversion::intType))
	{
		_intValue = static_cast<int>(_floatValue);
		_intConvOk = true;
	}
	if (!isOutOfRange(_doubleValue, Conversion::charType))
	{
		_charValue = static_cast<char>(_floatValue);
		_charConvOk = true;
	}
}
