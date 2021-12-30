/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:32:17 by lle-briq          #+#    #+#             */
/*   Updated: 2021/12/30 09:18:59 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conversion.hpp"


int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Use ./convert litteralValue" << std::endl;
		return (1);
	}

	Conversion	conv(argv[1]);
	std::cout << conv;
	return (0);
}
