Import("env")

# Compile pure-data decoder source for native tests
# Use relative path from source root (..) which is the project root
decode_src = env.File("../src/utility/cc3000_decode.cpp")
decode_obj = env.Object(decode_src)
env.Append(LIBS=[decode_obj])

env.Append(
    CCFLAGS=["--coverage"],
    LINKFLAGS=["--coverage"]
)
