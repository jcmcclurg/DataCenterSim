# Create an environmnet
env = Environment()

# Tell the compiler to use the mingw toolchain
#Tool('mingw')(env)

# Tell the program that it's to run in debug mode
#env.Append(CPPDEFINES=['DEBUG=10','UNITTEST'])
env.Append(CPPDEFINES=['DEBUG=4'])

# Do the compilation of all the sources
#sources = Glob("DataCenterSim/*.cpp") + Glob("DataCenterSim/*.h")
sources = Glob("DataCenterSim/*.cpp");
env.Program(target = "DataCenterSim/main", source = sources)