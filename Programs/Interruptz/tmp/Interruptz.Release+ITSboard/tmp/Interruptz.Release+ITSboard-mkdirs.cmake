# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/Interruptz/tmp/Interruptz.Release+ITSboard")
  file(MAKE_DIRECTORY "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/Interruptz/tmp/Interruptz.Release+ITSboard")
endif()
file(MAKE_DIRECTORY
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/Interruptz/tmp/1"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/Interruptz/tmp/Interruptz.Release+ITSboard"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/Interruptz/tmp/Interruptz.Release+ITSboard/tmp"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/Interruptz/tmp/Interruptz.Release+ITSboard/src/Interruptz.Release+ITSboard-stamp"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/Interruptz/tmp/Interruptz.Release+ITSboard/src"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/Interruptz/tmp/Interruptz.Release+ITSboard/src/Interruptz.Release+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/Interruptz/tmp/Interruptz.Release+ITSboard/src/Interruptz.Release+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/Interruptz/tmp/Interruptz.Release+ITSboard/src/Interruptz.Release+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
