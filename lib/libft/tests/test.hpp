/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ms <smamalig@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:29:03 by ms                #+#    #+#             */
/*   Updated: 2025/10/28 20:40:36 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H

#include <cstring>
#include <vector>
#include <iostream>
#include <functional>
#include <unistd.h>

/* -------------------------------------------------------------------------- */
/*                                  Test Core                                 */
/* -------------------------------------------------------------------------- */

enum ResultType {
	RESULT_EQ,
	RESULT_NEQ,
	RESULT_LT,
	RESULT_GT,
};

template <typename T, typename K>
struct ExpectResult {
	ResultType	type;
	bool		error{false};
	T			expected{};
	T			got{};
	K			info{};
};

template <typename T, typename K>
class ExpectResults : public std::vector<ExpectResult<T, K>> {
public:
	void add(const ExpectResult<T, K> &x) {
		if (x.error)
			this->push_back(x);
	}
};

/* -------------------------------------------------------------------------- */
/*                                   Expect                                   */
/* -------------------------------------------------------------------------- */

template <typename K>
inline ExpectResult<const char *, K> expect_str_eq(const char *expected, const char *got, K info) {
	ExpectResult<const char *, K> res;
	if (strcmp(expected, got) == 0)
		return res;
	res.info = info;
	res.expected = expected;
	res.got = got;
	res.error = true;
	return res;
}

template <typename T, typename K>
inline ExpectResult<T, K> expect_eq(T expected, T got, K info) {
	ExpectResult<T, K> res;
	if (expected == got)
		return res;
	res.info = info;
	res.expected = expected;
	res.got = got;
	res.error = true;
	return res;
}

template <typename T, typename K>
inline ExpectResult<T, K> expect_neq(T expected, T got, K info) {
	ExpectResult<T, K> res;
	if (expected != got)
		return res;
	res.info = info;
	res.expected = expected;
	res.got = got;
	res.error = true;
	return res;
}

/* -------------------------------------------------------------------------- */
/*                              Test Infrastructure                           */
/* -------------------------------------------------------------------------- */

struct TestStats {
	int total = 0;
	int failed = 0;
};

inline TestStats g_stats;
inline const char *g_current_suite = nullptr;

inline void describe(const char *name) {
	std::cout << "\n\x1b[1m" << name << "\x1b[0m\n";
}

template <typename T, typename K, typename F>
inline void test(const char *desc, F test_fn) {
	g_stats.total++;
	ExpectResults<T, K> res;
	test_fn(res);

	std::string label;
	if (g_current_suite)
		label = std::string(g_current_suite) + "." + desc;
	else
		label = desc;

	if (res.empty()) {
		std::cout << "\x1b[92m[PASS]\x1b[0m " << desc << "\n";
		return;
	}
	g_stats.failed++;
	std::cout << "\x1b[91m[FAIL]\x1b[0m " << desc << "\n";
	for (const auto &x : res)
		std::cout << "\t\t`" << x.info << "`: expected `" << x.expected
		          << "`, got `" << x.got << "`\n";
}

inline void test_summary() {
	std::cout << "\nSummary: "
	          << (g_stats.total - g_stats.failed) << "/" << g_stats.total
	          << " tests passed.\n";
}

/* -------------------------------------------------------------------------- */
/*                                 Test Suites                                */
/* -------------------------------------------------------------------------- */

struct TestSuite {
	const char *name;
	void (*setup)() = nullptr;
	void (*teardown)() = nullptr;
	std::vector<void(*)()> tests;
};

inline void run_suite(const TestSuite &suite) {
	g_current_suite = suite.name;
	if (suite.setup) suite.setup();
	for (auto fn : suite.tests)
		fn();
	if (suite.teardown) suite.teardown();
	g_current_suite = nullptr;
}

/* -------------------------------------------------------------------------- */
/*                                   Helpers                                  */
/* -------------------------------------------------------------------------- */

/* Inline EXPECT_* macros for quick one-offs */
#define EXPECT_EQ(exp, got, info) \
	do { \
		if ((exp) != (got)) { \
			std::cerr << "\x1b[91m[FAIL]\x1b[0m " << info \
			          << " expected " << (exp) << " got " << (got) << "\n"; \
			::g_stats.failed++; \
		} else { \
			std::cout << "\x1b[92m[PASS]\x1b[0m " << info << "\n"; \
		} \
		::g_stats.total++; \
	} while(0)

/* Mock helpers */
struct MockCall {
	const char *name;
	int count = 0;
};

inline void mock_called(MockCall &m) { m.count++; }

/* Fake file helper for pipe-based tests */
struct FakeFile {
	int rd, wr;
	FakeFile(const char *data) {
		int fds[2];
		pipe(fds);
		rd = fds[0]; wr = fds[1];
		dprintf(wr, "%s", data);
		close(wr);
	}
	~FakeFile() { close(rd); }
};

/* Subtest utility for grouping expectations */
inline void subtest(const char *label, const std::function<void()> &fn) {
	std::cout << "\t→ " << label << "\n";
	fn();
}

/* -------------------------------------------------------------------------- */
/*                                   Externs                                  */
/* -------------------------------------------------------------------------- */

extern void test_alloc();
extern void test_checks();
extern void test_convert();
extern void test_io();
extern void test_list();
extern void test_math();
extern void test_mem();
extern void test_file();
extern void test_str_compare();
extern void test_str_concat();
extern void test_str_copy();
extern void test_str_info();
extern void test_str_modify();
extern void test_str_search();
extern void test_vector();

#endif
