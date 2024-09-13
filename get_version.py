Import("env")
import os

firmware_version = "1.0.2"

print(f'Using version {firmware_version} for the build')

# Append the version to the build defines so it gets baked into the firmware
env.Append(CPPDEFINES=[
  f'BUILD_VERSION={firmware_version}'
])

# Set the output filename to the name of the board and the version
env.Replace(PROGNAME=f'reset.arduino_{env["PIOENV"]}_{firmware_version.replace(".", "_")}')
