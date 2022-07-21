
add_unit_test(PARALLEL TRUE NAME game.set_coin_count SOURCES set_coin_count.cpp LIBS ${P2_LIB_TARGET})
add_unit_test(PARALLEL TRUE NAME game.set_charm_count SOURCES set_charm_count.cpp LIBS ${P2_LIB_TARGET})
add_unit_test(PARALLEL TRUE NAME game.charm_available SOURCES charm_available.cpp LIBS ${P2_LIB_TARGET})
