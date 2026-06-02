<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>MainWidgetClass</class>
 <widget class="QMainWindow" name="MainWidgetClass">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>600</width>
    <height>400</height>
   </rect>
  </property>
  <property name="windowTitle">
   <string>MainWidget</string>
  </property>
  <widget class="QWidget" name="centralWidget"/>
  <widget class="QMenuBar" name="menuBar">
   <property name="geometry">
    <rect>
     <x>0</x>
     <y>0</y>
     <width>600</width>
     <height>26</height>
    </rect>
   </property>
   <widget class="QMenu" name="menu">
    <property name="title">
     <string>开始</string>
    </property>
    <addaction name="actionExitGame"/>
   </widget>
   <addaction name="menu"/>
  </widget>
  <action name="actionExitGame">
   <property name="text">
    <string>退出</string>
   </property>
  </action>
 </widget>
 <layoutdefault spacing="6" margin="11"/>
 <resources>
  <include location="MainWidget.qrc"/>
 </resources>
 <connections/>
</ui>
