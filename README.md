# Qt/QML/C++ integration example

In this project I would like to build a boilerplate for a code
that accomplishes following:

* Crossplatform app with GUI
    * Tested:
        * [x] Linux
        * [ ] Windows
        * [ ] macOS
        * [x] Android
        * [ ] iOS
    * Build, install and run process documented:
        * [ ] Linux
        * [ ] Windows
        * [ ] macOS
        * [ ] Android
        * [ ] iOS

* [x] UI is implemented in QtWidgets

* [x] There is a list of items
    * e.g. different type of fruit

* [x] There are some item properties that can be accessed individually 
    * e.g. properties of name and price

* [x] An item is implemented in C++ and is not dependent on UI
    * e.g. it is a plain C++ object or Q_OBJECT (preferably plain
      C++ object with Q_OBJECT interface to QML)

* [x] List of item is dynamic
    * Items can be added, removed and modified from UI

* [x] C++ code is aware of dynamic collection of items
    * It can e.g. randomly adjust price of every item independent of UI
