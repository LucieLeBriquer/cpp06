/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:32:24 by lle-briq          #+#    #+#             */
/*   Updated: 2022/01/04 18:32:24 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

/*
**		CONSTRUCTORS AND DESTRUCTOR
*/

Data::Data(void) : _value(42)
{
	return ;
}

Data::Data(const Data &data)
{
	*this = data;
}

Data::~Data()
{
	return ;
}

/*
**		OVERLOAD OPERATORS
*/

Data	&Data::operator=(const Data &data)
{
	if (this != &data)
		this->_value = data._value;
	return (*this);
}

/*
**		MEMBER FUNCTIONS
*/

int	Data::getValue(void) const
{
	return (_value);
}