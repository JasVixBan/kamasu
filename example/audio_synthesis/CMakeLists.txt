add_executable(synth-kamasu
  kamasu.cpp
  )
target_link_libraries(synth-kamasu
  resophonic_kamasu
  ${CUDART_LIBRARY}
  ${BOOST_LIBRARIES}
  )

# 
# add_executable(autocorrelation-cpu
#   cpu.cpp
#   )
# target_link_libraries(autocorrelation-cpu
#   ${BOOST_LIBRARIES}
#   )



