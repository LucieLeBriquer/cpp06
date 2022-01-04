/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:25:13 by lle-briq          #+#    #+#             */
/*   Updated: 2022/01/04 18:25:13 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

class Data
{
	private:
		int	_value;

		Data(const Data &data);
		Data	&operator=(const Data &data);
		
	public:
		Data(void);
		virtual ~Data();

		int	getValue(void) const;
};

# endif