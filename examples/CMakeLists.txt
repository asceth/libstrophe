# Configure examples build

add_executable(active_example active.c)
add_executable(basic_example basic.c)
add_executable(bot_example bot.c)
add_executable(roster_example roster.c)

target_link_libraries(active_example Strophe)
target_link_libraries(basic_example Strophe)
target_link_libraries(bot_example Strophe)
target_link_libraries(roster_example Strophe)

