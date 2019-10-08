** DATA DUMP FROM JETSON **
These files are various bits of code, dependencies, libraries, and unknown source files found on the Jetson TX2 from previous years.

# TODO #
- Replace Dependencies with Git Subtree versions of the upstream files
- Improve scripts to run on SystemD with Unit Files, such that failure/crashes can be properly recovered from
- Categorize and split out projects into server-side code, client-side (rover) code, and legacy code. Break into separate repositories on GitHub
- etc.

The following dependencies were removed:
ArduinoHallEffect     Phoenix-api
aruco-3.1.0           Phoenix-Linux-SocketCAN-Example
candlelight           tegra_multimedia_api
jetsonTX2GPIO-master  VisionWorks-SFM-0.90-Samples
JetsonTxLibs          WPILib_Linux-2019.1.1
opencv                ZED_SDK_JTX2_JP3.2_v2.7.1.run
opencv_contrib
