#pragma once
#include "type_traits"


template <typename Enum>
constexpr auto to_underLying(Enum e) noexcept {
	return static_cast<std::underlying_type_t<Enum>>(e);
}

enum class PlayerState : Uint16{
	Idle = 0,
	Jump = 1 << 1,
	Left = 1 << 2,
	Down = 1 << 3,
	Right = 1 << 4,
	Left_Jump = 1 << 5,
	Right_jump = 1 << 6
};

constexpr PlayerState operator&(PlayerState a, PlayerState b) {
	return static_cast<PlayerState>(to_underLying(a) & to_underLying(b));
}

constexpr PlayerState operator|(PlayerState a, PlayerState b) {
	return static_cast<PlayerState>(to_underLying(a) | to_underLying(b));
}

constexpr PlayerState& operator|=(PlayerState& a, PlayerState b) {
	return a = a | b;
}

constexpr PlayerState& operator&=(PlayerState& a, PlayerState b) {
	return a = a & b;
}

constexpr PlayerState operator~(PlayerState a) {
	return static_cast<PlayerState>(~to_underLying(a));
}

