#pragma once
#include "type_traits"


template <typename Enum>
constexpr auto to_underLying(Enum e) noexcept {
	return static_cast<std::underlying_type_t<Enum>>(e);
}



enum class PlayerState : Uint16 {
	Idle,
	Idle_to_Jump,
	Jump,
	Fall,
	Idle_to_Run,
	Run,
	Run_to_Idle,
	Idle_to_Down,
	Down,
	Down_to_Idle,
	Attack = 1 << 5,
	Roll = 1 << 6,
	On_ground = 1 << 7,
	Interruptible_mask = Jump | Run | Fall | Attack | Roll | On_ground,
};



enum class ActionState :Uint16 {
	PreAction,
	Action,
	PostAction
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