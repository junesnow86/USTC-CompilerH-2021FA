add_executable(
  assign_generator
  assign_gen.cpp
)
target_link_libraries(
  assign_generator
  IRLib
)

add_executable(
  func_generator
  func_gen.cpp
)
target_link_libraries(
  func_generator
  IRLib
)

add_executable(
  if_generator
  if_gen.cpp
)
target_link_libraries(
  if_generator
  IRLib
)

add_executable(
  while_generator
  while_gen.cpp
)
target_link_libraries(
  while_generator
  IRLib
)
  