// -----------------------------------------------------------
// 
// coroutine task
// 
// Copyright 2023 teacha1025
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// -----------------------------------------------------------

#pragma once

#include <coroutine>

#include "def.h"

namespace suika {
	struct yield_type {
		constexpr yield_type() :count(1) {}
		constexpr yield_type(uint32 c) : count(c) {}
		uint32 count;
	};
	namespace detail {
		struct awaiter {
			virtual ~awaiter() = default;
			virtual bool resume() = 0;
		};
		template<class Handle>
		concept await_handler = requires(Handle handle) {
			requires std::same_as<awaiter*, decltype(handle.promise().pAwaiter)>;
			requires std::convertible_to<Handle, std::coroutine_handle<>>;
		};
		struct yield_awaiter : awaiter {
			yield_awaiter(const yield_type& y) :yield(y) {}
			bool await_ready() const noexcept { return yield.count == 0; }
			template<await_handler handle>
			void await_suspend(handle h) noexcept {
				h.promise().pAwaiter = this;
			}
			void await_resume() {}
			bool resume() override {
				return --yield.count > 0;
			}
			yield_type yield;
		};

		template<typename T>
		struct promise_type;
		template<typename T>
		struct task_awaiter;
	}
}
inline auto operator co_await(const suika::yield_type& y) {
	return suika::detail::yield_awaiter{ y };
}
namespace suika{
	template<typename T = void>
	class task {
	public:
		using handle_type = std::coroutine_handle<detail::promise_type<T>>;
		using promise_type = detail::promise_type<T>;		
	private:
		handle_type handle;
	public:
		task(promise_type* p) : handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}

		task(const task&) = delete;

		task(task&& rhs) :handle(rhs.handle) {
			rhs.handle = nullptr;
		}

		~task() {
			if (handle != nullptr) {
				handle.destroy();
			}
		}

		decltype(auto) value() const {
			return handle.promise().value;
		}

		bool next() {
			if (!handle) {
				return false;
			}
			if (handle.done()) {
				if (handle.promise().exception) {
					std::rethrow_exception(handle.promise().exception);
				}
				return false;
			}
			{
				if (auto& awaiter = handle.promise().p_awaiter) {
					if (!awaiter->resume()) {
						awaiter = nullptr;
					}
					else {
						return true;
					}
				}
			}
			handle.resume();
			return !handle.done();
		}

		bool is_done() const{
			if (!handle) {
				return true;
			}
			return handle.done();
		}
	};
	
	namespace detail {
		template<typename T>
		struct promise_value {
			T value;
			void return_value(const T& v) {
				value = v;
			}
			const T& get() const {
				return value;
			}
		};
		template<>
		struct promise_value<void> {
			void return_void() {}
			void get() const {}
		};
		template<typename T>
		struct promise_type :promise_value<T>{
			awaiter* p_awaiter = nullptr;
			std::exception_ptr exception;
			auto initial_suspend() noexcept { return std::suspend_always{}; }
			auto final_suspend() noexcept { return std::suspend_always{}; }
			auto get_return_object() noexcept { return task<T>(this); }
			void unhandled_exception() noexcept { exception = std::current_exception(); }
			auto yield_value(const yield_type& y) noexcept { return operator co_await(y); }
		};
		template<typename T>
		struct task_awaiter :awaiter {
			task_awaiter(task<T>&& t):task(std::move(t)){}
			bool await_ready() const { return !task.next(); }
			template<await_handler handle>
			void await_suspend(handle h) noexcept {task.handle.promise().p_awaiter = this;}
			decltype(auto) await_resume() const { return task.value(); }
			bool resume() override { return task.next(); }
			task<T> task;
		};
	}
}

template<typename T>
inline auto operator co_await(suika::task<T> other) {
	return suika::detail::task_awaiter(std::move(other));
}
template<typename T>
auto operator co_await(suika::task<T>&& t) {
	struct awaiter {
		suika::task<T>& t;
		bool await_ready() const noexcept { return false; }
		void await_suspend(std::coroutine_handle<> h) noexcept { t.handle.promise().continuation = h; }
		T await_resume() { return t.value(); }
	};
	return suika::detail::awaiter{ t };
}