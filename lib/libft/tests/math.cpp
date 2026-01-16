/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:26:23 by smamalig          #+#    #+#             */
/*   Updated: 2025/02/27 16:29:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"
#include <climits>
#include <cstdlib>
#include <math.h>
extern "C" {
#include "libft.h"
}

void test_math() {
	describe("math");
	test<int, int>("abs", [](auto res) {
		(void)res;
		for (int i = -10; i < 10; i++) {
			ExpectResult expect = expect_eq(abs(i), ft_abs(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<int, const char *>("nmax", [](auto res) {
		ExpectResult expect = expect_eq(123, ft_nmax(4, 10, 42, INT_MIN, 123), "test1");
		if (expect.error)
			res.push_back(expect);
	});
	test<int, int>("intlen", [](auto res) {
		for (int i = 1; i < 1000; i++) {
			ExpectResult expect = expect_eq((int)log10(i) + 1, ft_intlen(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
}

