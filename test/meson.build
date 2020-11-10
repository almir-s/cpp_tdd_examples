gtest_srcs= files(['gtest_main.cpp', 'soundexTest.cpp', 'retweetCollectionTest.cpp'])


gtest_dep = gtest_sp.get_variable('gtest_dep')
gmock_dep = gtest_sp.get_variable('gmock_dep')

gtest_exec = executable('TddSessionTests', gtest_srcs, 
  dependencies :[gtest_dep, gmock_dep, project_dep])

test('TDD session tests', gtest_exec)
