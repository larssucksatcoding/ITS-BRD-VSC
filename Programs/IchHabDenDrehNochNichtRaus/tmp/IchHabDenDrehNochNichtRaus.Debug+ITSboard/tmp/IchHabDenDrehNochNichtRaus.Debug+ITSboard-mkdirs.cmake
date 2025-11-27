# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/IchHabDenDrehNochNichtRaus/tmp/IchHabDenDrehNochNichtRaus.Debug+ITSboard"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/IchHabDenDrehNochNichtRaus/tmp/1"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/IchHabDenDrehNochNichtRaus/tmp/IchHabDenDrehNochNichtRaus.Debug+ITSboard"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/IchHabDenDrehNochNichtRaus/tmp/IchHabDenDrehNochNichtRaus.Debug+ITSboard/tmp"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/IchHabDenDrehNochNichtRaus/tmp/IchHabDenDrehNochNichtRaus.Debug+ITSboard/src/IchHabDenDrehNochNichtRaus.Debug+ITSboard-stamp"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/IchHabDenDrehNochNichtRaus/tmp/IchHabDenDrehNochNichtRaus.Debug+ITSboard/src"
  "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/IchHabDenDrehNochNichtRaus/tmp/IchHabDenDrehNochNichtRaus.Debug+ITSboard/src/IchHabDenDrehNochNichtRaus.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/IchHabDenDrehNochNichtRaus/tmp/IchHabDenDrehNochNichtRaus.Debug+ITSboard/src/IchHabDenDrehNochNichtRaus.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/bazzite/Documents/code projects/uni/gs/Aufgabe1/ITS-BRD-VSC/Programs/IchHabDenDrehNochNichtRaus/tmp/IchHabDenDrehNochNichtRaus.Debug+ITSboard/src/IchHabDenDrehNochNichtRaus.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
