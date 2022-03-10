/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-briq <lle-briq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:32:52 by lle-briq          #+#    #+#             */
/*   Updated: 2022/03/10 16:19:21 by lle-briq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <iostream>
#include "Data.hpp"

uintptr_t	serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data		*deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}

int	main(void)
{
	Data		*data;
	uintptr_t	serialized;
	Data		*deserialized;

	data = new Data();
	std::cout << "data ptr = " << data << std::endl;
	std::cout << "\t value = " << data->getValue() << std::endl;

	serialized = serialize(data);
	std::cout << "serialize(data ptr) = " << serialized << std::endl;

	deserialized = deserialize(serialized);
	std::cout << "deserialize(serialize(data ptr)) = " << deserialized << std::endl;
	std::cout << "\t value = " << deserialized->getValue() << std::endl;

	delete data;
	return (0);
}
