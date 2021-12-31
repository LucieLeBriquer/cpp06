/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conversion.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 09:23:44 by lle-briq          #+#    #+#             */
/*   Updated: 2021/12/31 01:10:55 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSION_HPP
# define CONVERSION_HPP
# include <iostream>
# include <cstdlib>
# include <cerrno>
# include <limits>
# include <cstring>

class Conversion
{
	private:
		bool		_charConvOk;
		bool		_intConvOk;
		bool		_floatConvOk;
		bool		_doubleConvOk;
		char		_charValue;
		int			_intValue;
		float		_floatValue;
		double		_doubleValue;
		int			_isLimitBool;
		std::string	_limit;
		bool		_stringError;
		bool		_outOfRange;
		bool		_zeroDec;

		Conversion(const Conversion &conversion);
		Conversion	&operator=(const Conversion &conversion);

		bool		_isLimit(const char *value);
		int			_getType(const char *value);
		void		_convFromChar(const char *value);
		void		_convFromInt(const char *value);
		void		_convFromFloat(const char *value);
		void		_convFromDouble(const char *value);

	public:
		Conversion(void);
		Conversion(const char *value);
		virtual ~Conversion();

		void		printChar(void) const;
		void		printInt(void) const;
		void		printFloat(void) const;
		void		printDouble(void) const;
		bool		getOutOfRange(void) const;
		bool		getStringError(void) const;

		static const int	charType = 0;
		static const int	intType = 1;
		static const int	floatType = 2;
		static const int	doubleType = 3;
		static const int	wrongType = 4;
};

std::ostream	&operator<<(std::ostream &o, const Conversion &conversion);

typedef void (Conversion::*convFunction)(const char *);

#endif
