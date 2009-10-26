; PureBasic Visual Designer v3.95 build 1485 (PB4Code)


;- Window Constants
;
Enumeration
  #MainWindow
EndEnumeration

;- Gadget Constants
;
Enumeration
  #Frame3D_0
  #RDB_OPENGL
  #RDB_OPENGL2
  #RDB_SOFTWARE
  #BT_RUN
EndEnumeration


Procedure Open_MainWindow()
  If OpenWindow(#MainWindow, 389, 74, 220, 174, "OpenAlchemist Config",  #PB_Window_SystemMenu | #PB_Window_TitleBar | #PB_Window_ScreenCentered )
    If CreateGadgetList(WindowID(#MainWindow))
      Frame3DGadget(#Frame3D_0, 10, 10, 190, 110, "Render : ")
      OptionGadget(#RDB_OPENGL, 30, 30, 70, 20, "OpenGL")
      OptionGadget(#RDB_OPENGL2, 30, 60, 120, 20, "OpenGL 2")
      OptionGadget(#RDB_SOFTWARE, 30, 90, 120, 20, "Software")
      ButtonGadget(#BT_RUN, 10, 130, 190, 30, "Run game")
      
    EndIf
  EndIf
EndProcedure

