/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:28:19 by smamalig          #+#    #+#             */
/*   Updated: 2025/03/19 15:25:50 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"
#include <climits>
extern "C" {
#include "libft.h"
}

void test_convert() {
	describe("convert");
	test<int, int>("toupper", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(toupper(i), ft_toupper(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<int, int>("tolower", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(tolower(i), ft_tolower(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<int, const char *>("atoi", [](auto res) {
		const char *tests[] = { "42", "-2147483648", "123a", "hello", " \t\n\r\v\f+42", " + 1" };
		for (size_t i = 0; i < sizeof(tests) / sizeof(char *); i++) {
			ExpectResult expect = expect_eq(atoi(tests[i]), ft_atoi(tests[i]), tests[i]);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<int, const char *>("atoi_safe", [](auto res) {
		const char *tests[] = {
			"42", "123a", "hello", " \t\n\r\v\f+42", " + 1",
			"-2147483648", "-2147483647", "-2147483649", "-1073741824", "-4294967296",
			"2147483647", "2147483646", "2147483648", "1073741823", "4294967295"
		};
		const int results[] = {
			42, 123, 0, 42, 0,
			INT_MIN, INT_MIN+1, INT_MIN, INT_MIN/2, INT_MIN,
			INT_MAX, INT_MAX-1, INT_MAX, INT_MAX/2, INT_MAX
		};
		for (size_t i = 0; i < sizeof(tests) / sizeof(char *); i++) {
			errno = 0;
			ExpectResult expect = expect_eq(results[i], ft_atoi_safe(tests[i]), tests[i]);
			if (expect.error)
				res.push_back(expect);
		}
	});
	// add atol and atoll !
	// printf("%2$-*3$.*1$g|", 5, 123.456, 10);
}

