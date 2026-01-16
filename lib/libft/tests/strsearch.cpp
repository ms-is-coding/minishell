/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsearch.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:30:34 by smamalig          #+#    #+#             */
/*   Updated: 2025/02/25 15:07:18 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"
#include <bsd/string.h>
extern "C" {
#include "libft.h"
}

void test_str_search() {
	describe("str/search");
	test<size_t, std::string>("strnstr", [](auto res) {
		const char *haystack1 = "Hello, World!";
		const char *needle1 = "World";
		for (size_t size = 0; size < ft_strlen(haystack1); size++) {
			ExpectResult expect = expect_eq(
				(size_t)strnstr(haystack1, needle1, size),
				(size_t)ft_strnstr(haystack1, needle1, size),
				"test1-" + std::to_string(size));
			if (expect.error)
				res.push_back(expect);
		}
		const char *haystack2 = "aaaaabc";
		const char *needle2 = "aaaabc";
		for (size_t size = 0; size < ft_strlen(haystack2); size++) {
			ExpectResult expect = expect_eq(
				(size_t)strnstr(haystack2, needle2, size),
				(size_t)ft_strnstr(haystack2, needle2, size),
				"test2-" + std::to_string(size));
			if (expect.error)
				res.push_back(expect);
		}
		const char *haystack3 = "aaaaaabc";
		const char *needle3 = "abc";
		for (size_t size = 0; size < ft_strlen(haystack3); size++) {
			ExpectResult expect = expect_eq(
				(size_t)strnstr(haystack3, needle3, size),
				(size_t)ft_strnstr(haystack3, needle3, size),
				"test3-" + std::to_string(size));
			if (expect.error)
				res.push_back(expect);
		}
	});
}
