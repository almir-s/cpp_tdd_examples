gtest_srcs= files(['gtest_main.cpp', 'soundex_test.cpp', 'retweet_collection_test.cpp', 'place_description_service_test.cpp', 
'out_parameter_test.cpp', 'portfolio_test.cpp'])


gtest_dep = gtest_sp.get_variable('gtest_dep')
gmock_dep = gtest_sp.get_variable('gmock_dep')

gtest_exec = executable('TddSessionTests', gtest_srcs, 
  dependencies :[gtest_dep, gmock_dep, project_dep])

test('TDD session tests', gtest_exec)
