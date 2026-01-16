/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:29:00 by smamalig          #+#    #+#             */
/*   Updated: 2025/02/25 15:06:50 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"
extern "C" {
#include "libft.h"
}

void test_mem() {
	describe("mem");
	test<char *, char *>("memset", [](auto res) {
		char *test1_a = strdup("Hello");
		char *test1_b = strdup("Hello");
		memset(test1_a, ' ', 4);
		ft_memset(test1_b, ' ', 4);
		ExpectResult expect = expect_str_eq(test1_a, test1_b, (char *)"Hello");
		if (expect.error)
			res.push_back(expect);
	});
  	test<char *, char *>("memmove", [](auto res) {
		char mut[] = "Hello, World! Wow";
		ft_memmove(mut+4, mut, ft_strlen(mut) - 4);
		ExpectResult expect = expect_str_eq(mut+4, (char *)"Hello, World!", (char *)"test1");
		if (expect.error)
			res.push_back(expect);
	});
}
