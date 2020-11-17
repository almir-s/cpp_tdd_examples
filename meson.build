project('tdd_examples', 'cpp', default_options:['cpp_std=c++14'])

source_dir = files(['src/address_extractor.cpp', 'src/place_description_service.cpp', 'src/address_extractor.cpp', 'src/curl_http.cpp', 'src/portfolio.cpp'])

json_sp = subproject('jsoncpp')
json_dep = json_sp.get_variable('jsoncpp_dep')
boost_dep = dependency('boost')

thread_dep = dependency('threads')
curl_dep = dependency('libcurl')

include_dir = include_directories('include')

project_dep = declare_dependency(include_directories: include_dir, sources: source_dir, dependencies: [thread_dep, json_dep, curl_dep, boost_dep])

gtest_sp = subproject('gtest')

subdir('test')
executable('main', sources: ['src/main.cpp'], dependencies: [project_dep])
