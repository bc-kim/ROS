# CMake generated Testfile for 
# Source directory: /home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel
# Build directory: /home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_rqt_ez_publisher_nosetests_test.function_test.py "/home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/test_results/rqt_ez_publisher/nosetests-test.function_test.py.xml" "--return-code" "/usr/bin/cmake -E make_directory /home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/test_results/rqt_ez_publisher" "/usr/bin/nosetests-2.7 -P --process-timeout=60 /home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/test/function_test.py --with-xunit --xunit-file=/home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/test_results/rqt_ez_publisher/nosetests-test.function_test.py.xml")
add_test(_ctest_rqt_ez_publisher_rostest_test_ros.test "/home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/test_results/rqt_ez_publisher/rostest-test_ros.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel --package=rqt_ez_publisher --results-filename test_ros.xml --results-base-dir \"/home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/test_results\" /home/gripit/catkin_ws/src/rqt_ez_publisher-kinetic-devel/test/ros.test ")
subdirs(gtest)
