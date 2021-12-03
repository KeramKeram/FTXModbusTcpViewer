from conans import ConanFile, CMake


class SevenIDEConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "catch2/2.13.7"
    generators = "cmake_find_package"
    default_options = {"libpng:shared": True}

