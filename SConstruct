# Create an environmnet
env = Environment()

# Tell the compiler to use the mingw toolchain
#Tool('mingw')(env)

# Tell the program that it's to run in debug mode
#env.Append(CPPDEFINES=['DEBUG=10','UNITTEST'])
env.Append(CPPDEFINES=['DEBUG=1'])

# Do the compilation of all the sources
#sources = Glob("DataCenterSim/*.cpp") + Glob("DataCenterSim/*.h")
sources = Glob("DataCenterSim/*.cpp");
env.Program(target = "DataCenterSim/main", source = sources, LIBS=['boost_system-mt','boost_filesystem-mt','boost_regex-mt','libboost_program_options-mt'])