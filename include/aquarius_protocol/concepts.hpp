#pragma once
#include <concepts>
#include <vector>
#include <string>
#include <cstdint>

namespace aquarius
{
	template <typename T, typename... Args>
	concept disjunction_same_as = std::disjunction_v<std::is_same<std::remove_cvref_t<T>, Args>...>;

	template <typename T>
	concept integer_t = disjunction_same_as<T, int8_t, int16_t, int32_t, int64_t>;

	template <typename T>
	concept uinteger_t = disjunction_same_as<T, uint8_t, uint16_t, uint32_t, uint64_t>;

	template <typename T>
	concept float_t = disjunction_same_as<std::remove_cvref_t<T>, float, double>;

	template <typename T>
	struct is_vector : std::false_type
	{};

	template <typename T, typename Alloc>
	struct is_vector<std::vector<T, Alloc>> : public std::true_type
	{};

	template <typename T>
	struct is_string : std::false_type
	{};

	template <>
	struct is_string<std::string> : public std::true_type
	{};

	template <typename T>
	concept string_t = is_string<std::remove_cvref_t<T>>::value;

	template <typename T>
	concept repeated_t = is_vector<std::remove_cvref_t<T>>::value;

	template <typename T>
	concept boolean_t = std::same_as<std::remove_cvref_t<T>, bool>;

	template <typename T>
	struct convert_stream_value_type
	{
		using type = T;
	};

	template <>
	struct convert_stream_value_type<char>
	{
		using type = uint8_t;
	};

} // namespace aquarius