# CAN TOOLS in CPP

C++ implementation of can tools ...

[![C++ implementation of can tools](http://img.youtube.com/vi/A-CfBD-AQCI/0.jpg)](https://www.youtube.com/watch?v=A-CfBD-AQCI "C++ implementation of can tools")

## Project Structure

```plaintext
cantools_cpp/
├── .vs/                            # Visual Studio settings folder
├── cantools_cpp/                   # currently for parsing CAN Messages, signals, ... from can database
├── cantools_cpp_gui/               # GUI for visualization and interraction with the backend, ...
```

## Dependencies

### Windows

#### Compiler and Tools:

Visual Studio 2022 (Community version)</br>
Visual C++</br>
CMake</br>

#### Third-Party Libraries:
**wxWidgets:** GUI development library. Download the stable release source from wxWidgets https://www.wxwidgets.org/downloads. </br>

Rename the downloaded folder to wxWidgetXXX, and place it in a directory, for example, C:\Users\<username>\wxWidgetXXX.</br>
Add an environment variable with the value C:\Users\username\wxWidgetXXX.</br>

**CycloneDDS:** DDS library.</br>

### Ubuntu
T.B.D

## Compilation Steps:

### Windows

Open Visual Studio 2022.</br>
Select File > Open > Folder.</br>
Choose the cantools_cpp folder.</br>
Build all. </br>

## DBC files 
Taken from https://github.com/EFeru/DbcParser.

## Reference
https://github.com/EFeru/DbcParser
