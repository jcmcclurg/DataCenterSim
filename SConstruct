# Create an environmnet
env = Environment()

# Tell the compiler to use the mingw toolchain
#Tool('mingw')(env)

# Tell the program that it's to run in debug mode
env.Append(CPPDEFINES=['DEBUG=10'])

# Do the compilation of all the sources
env.Program(target = "DataCenterSim/main", source = Glob("DataCenterSim/*.cpp"))
