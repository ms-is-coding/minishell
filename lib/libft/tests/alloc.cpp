/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:24:31 by smamalig          #+#    #+#             */
/*   Updated: 2025/02/27 16:12:19 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"
extern "C" {
#include "libft.h"
}

void test_alloc() {
	describe("alloc");
	test<void *, const char *>("calloc", [](auto res) {
		void *ptr = ft_calloc(10, 1);
		ExpectResult expect = expect_neq((void *)NULL, ptr, "test1");
		ft_free(ptr);
		if (expect.error)
			res.push_back(expect);
	});
	test<int, const char *>("free", [](auto res) {
		(void)res;
		void *ptr = ft_malloc(10);
		ft_free(ptr);
	});
	test<void *, const char *>("malloc", [](auto res) {
		void *ptr = ft_malloc(10);
		ExpectResult expect = expect_neq((void *)NULL, ptr, "test1");
		ft_free(ptr);
		if (expect.error)
			res.push_back(expect);
	});
	test<void *, const char *>("realloc", [](auto res) {
		(void)res;
		char *ptr = (char *)ft_malloc(0x10);
		ft_realloc(ptr, 0x10, 0x400);
		for (int i = 0; i < 0x400; i++)
			ptr[i] = i;
		ft_free(ptr);
	});
}
