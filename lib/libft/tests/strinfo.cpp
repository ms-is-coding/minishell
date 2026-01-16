/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strinfo.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:35:11 by smamalig          #+#    #+#             */
/*   Updated: 2025/02/25 15:07:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"
extern "C" {
#include "libft.h"
}

void test_str_info() {
	describe("str/info");
	test<size_t, const char *>("strlen", [](auto res) {
		const char *tests[] = { "Hello", "" };
		for (const auto test : tests) {
			ExpectResult expect = expect_eq(strlen(test), ft_strlen(test), test);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<size_t, const char *>("strnlen", [](auto res) {
		const char *tests[] = { "12345", "42", "abcdefghi" };
		for (size_t i = 0; i < sizeof(tests) / sizeof(char *); i++) {
			ExpectResult expect = expect_eq(strnlen(tests[i], 6), ft_strnlen(tests[i], 6), tests[i]);
			if (expect.error)
				res.push_back(expect);
		}
	});
}
