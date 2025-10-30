# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Uni/Desktop/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard"
  "C:/Users/Uni/Desktop/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/1"
  "C:/Users/Uni/Desktop/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard"
  "C:/Users/Uni/Desktop/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/tmp"
  "C:/Users/Uni/Desktop/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/src/GSP01_Taneschnerchner.Debug+ITSboard-stamp"
  "C:/Users/Uni/Desktop/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/src"
  "C:/Users/Uni/Desktop/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/src/GSP01_Taneschnerchner.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Uni/Desktop/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/src/GSP01_Taneschnerchner.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Uni/Desktop/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/src/GSP01_Taneschnerchner.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
