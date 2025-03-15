#pragma once
#include "type_traits"


template <typename Enum>
constexpr auto to_underLying(Enum e) noexcept {
	return static_cast<std::underlying_type_t<Enum>>(e);
}



enum class PlayerState : Uint16 {
	Idle = 0,
	Jump = 1 << 0,//0001
	Left = 1 << 1,//0010
	Down = 1 << 2,//0100
	Right = 1 << 3,//1000
	Interruptible_mask = Jump | Left | Down | Right,
	Left_Jump = 1 << 4,
	Right_jump = 1 << 5	
};

namespace std {
	template<>
	struct hash<PlayerState> {
		size_t operator()(PlayerState state) const {
			return std::hash<int>()(static_cast<int>(state));
		}
	};
}

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

//constexpr bool operator==(PlayerState a, PlayerState b) {
//	return a == b;
//}