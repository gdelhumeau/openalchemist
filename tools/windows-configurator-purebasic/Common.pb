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
  #RDB_SDL
  #Frame3D_2
  #SPIN_FPS
  #Frame3D_3
  #CB_COLOR_BLIND
  #BT_RUN
EndEnumeration


Procedure Open_MainWindow()
  If OpenWindow(#MainWindow, 441, 68, 214, 287, "OpenAlchemist Config",  #PB_Window_SystemMenu | #PB_Window_TitleBar | #PB_Window_ScreenCentered )
    If CreateGadgetList(WindowID(#MainWindow))
      Frame3DGadget(#Frame3D_0, 10, 10, 190, 80, "Render : ")
      OptionGadget(#RDB_OPENGL, 30, 30, 70, 20, "OpenGL")
      OptionGadget(#RDB_SDL, 30, 60, 120, 20, "SDL (DirectX)")
      Frame3DGadget(#Frame3D_2, 10, 100, 190, 70, "Limit framerate to :")
      SpinGadget(#SPIN_FPS, 30, 130, 150, 20, 0, 10)
      Frame3DGadget(#Frame3D_3, 10, 180, 190, 60, "Options : ")
      CheckBoxGadget(#CB_COLOR_BLIND, 30, 210, 150, 20, "Color Blind")
      ButtonGadget(#BT_RUN, 10, 250, 190, 30, "Run game")
      
    EndIf
  EndIf
EndProcedure

