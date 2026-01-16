/* ************************************************************************** */
/*                                                                            */
/*                                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*   vector.cpp                                            ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                         ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀   */
/*   By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀   */
/*                                                         ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀   */
/*   Created: 2025/06/04 15:41:54 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀   */
/*   Updated: 2025/06/05 14:53:30 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"
#include <assert.h>
#include <unistd.h>
extern "C" {
	#include "libft.h"
}

void print_value(t_value value) {
	if (value.type == TYPE_UNDEFINED) {
		ft_printf("undefined\n");
		return ;
	}
	ft_printf("%lu\n", value.value.u64);
}

void print_internal(t_vector *vec) {
	ft_printf("=== Vector { length = %zu, capacity = %zu, offset = %zu } ===\n",
		vec->length, vec->capacity, vec->offset);
	for (size_t i = 0; i < vec->capacity; i++) {
		ft_printf("- %.16lx\n", vec->data[i].value.u64);
	}
	ft_printf("=== === ===\n");
}

void at_value(t_vector *vec, ssize_t idx) {
	ft_printf("vec[%li] = ", idx);
	t_value value = ft_vector_at(vec, idx);
	print_value(value);
}

void pop_value(t_vector *vec) {
	ft_printf("pop = ");
	t_value value = ft_vector_pop(vec);
	print_value(value);
}

void shift_value(t_vector *vec) {
	ft_printf("shift = ");
	t_value value = ft_vector_shift(vec);
	print_value(value);
}

void print_vector(t_vector *vec) {
	ft_printf("[ ");
	for (int i = 0; i < (int)vec->length - 1; i++)
		ft_printf("%lu, ", ft_vector_at(vec, i).value.u64);
	if (vec->length)
		ft_printf("%lu", ft_vector_at(vec, -1).value.u64);
	ft_printf(" ]\n");
}

void test_vector() {
	describe("vector");
	
	t_vector vec;
	t_vector *ptr = &vec;
	assert(ft_vector_init(ptr, 4) == RESULT_OK);
	assert(ft_vector_push(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 1 })) == RESULT_OK);
	assert(ft_vector_push(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 2 })) == RESULT_OK);
	assert(ft_vector_push(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 3 })) == RESULT_OK);
	print_vector(ptr);
	ft_vector_push(ptr, ft_vector_shift(ptr));
	print_vector(ptr);
	ft_vector_unshift(ptr, ft_vector_pop(ptr));
	print_vector(ptr);
	// assert(ft_vector_unshift(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 42 })) == RESULT_OK);
	// assert(ft_vector_unshift(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 42 })) == RESULT_OK);
	// assert(ft_vector_unshift(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 123 })) == RESULT_OK);
	// assert(ft_vector_unshift(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 21 })) == RESULT_OK);
	// assert(ft_vector_push(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 0xffff })) == RESULT_OK);
	// print_internal(ptr);
	// assert(ft_vector_push(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 0xff })) == RESULT_OK);
	// assert(ft_vector_push(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 0x7f })) == RESULT_OK);
	// print_internal(ptr);
	// assert(ft_vector_unshift(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 0x42 })) == RESULT_OK);
	// assert(ft_vector_unshift(ptr, ft_gen_val(TYPE_OTHER, { .u64 = 0x88 })) == RESULT_OK);
	// assert(ft_vector_push(ptr, ft_gen_val(TYPE_OTHER, { .i32 = -1 })) == RESULT_OK);
	// print_internal(ptr);
	
	// for (int i = -ptr->length; i < (int)ptr->length; i++)
	// 	at_value(ptr, i);
}
