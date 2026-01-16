/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:23:39 by smamalig          #+#    #+#             */
/*   Updated: 2025/03/06 16:21:32 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"
#include <cctype>
extern "C" {
#include "libft.h"
}

void test_checks() {
	describe("checks");
	test<bool, int>("isalnum", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!isalnum(i), !!ft_isalnum(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("isalpha", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!isalpha(i), !!ft_isalpha(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("iscntrl", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!iscntrl(i), !!ft_iscntrl(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("isdigit", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!isdigit(i), !!ft_isdigit(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("isgraph", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!isgraph(i), !!ft_isgraph(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("islower", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!islower(i), !!ft_islower(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("isprint", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!isprint(i), !!ft_isprint(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("ispunct", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!ispunct(i), !!ft_ispunct(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("isspace", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!isspace(i), !!ft_isspace(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("isupper", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!isupper(i), !!ft_isupper(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("isxdigit", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!isxdigit(i), !!ft_isxdigit(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("isascii", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!isascii(i), !!ft_isascii(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
	test<bool, int>("isblank", [](auto res) {
		for (int i = 0; i < 256; i++) {
			ExpectResult expect = expect_eq(!!isblank(i), !!ft_isblank(i), i);
			if (expect.error)
				res.push_back(expect);
		}
	});
}

