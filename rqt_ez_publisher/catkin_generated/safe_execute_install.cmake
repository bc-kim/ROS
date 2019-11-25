execute_process(COMMAND "/home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
