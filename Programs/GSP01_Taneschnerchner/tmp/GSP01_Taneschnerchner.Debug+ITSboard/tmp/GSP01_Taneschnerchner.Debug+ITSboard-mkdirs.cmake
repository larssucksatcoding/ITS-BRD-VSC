# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/bazzite/Documents/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard"
  "/home/bazzite/Documents/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/1"
  "/home/bazzite/Documents/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard"
  "/home/bazzite/Documents/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/tmp"
  "/home/bazzite/Documents/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/src/GSP01_Taneschnerchner.Debug+ITSboard-stamp"
  "/home/bazzite/Documents/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/src"
  "/home/bazzite/Documents/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/src/GSP01_Taneschnerchner.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/bazzite/Documents/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/src/GSP01_Taneschnerchner.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/bazzite/Documents/ITS-BRD-VSC/Programs/GSP01_Taneschnerchner/tmp/GSP01_Taneschnerchner.Debug+ITSboard/src/GSP01_Taneschnerchner.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
