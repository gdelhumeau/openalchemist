XIncludeFile "Common.pb"

Declare main()
Declare run()
Declare initComponents()
Declare readConf()

; ------------
;- Constantes
; ------------
Global running = 1

; ------------
;- Main
; ------------
main()

; ------------
;- Procedures
; ------------

Procedure main()
  Open_MainWindow()
  initComponents()
  running = 1
  While running
    event = WaitWindowEvent()
    Select event
      Case #PB_Event_Gadget :
        Select EventGadget()
          Case #BT_RUN :
            run()
          Case #SPIN_FPS :
            SetGadgetText(#SPIN_FPS,Str(GetGadgetState(#SPIN_FPS)))
        EndSelect
      Case #PB_Event_CloseWindow :
        running = 0
    EndSelect
  Wend
  
EndProcedure

Procedure initComponents()
  SetGadgetState(#RDB_OPENGL, 1)
  SetGadgetAttribute(#SPIN_FPS, #PB_Spin_Minimum, 20)
  SetGadgetAttribute(#SPIN_FPS, #PB_Spin_Maximum, 200)
  readConf()
EndProcedure

Procedure run()
  running = 0
  parameters.s = ""
  
  If(GetGadgetState(#RDB_OPENGL)=1)
    parameters = parameters + " --opengl"
  Else
    parameters = parameters + " --sdl"
  EndIf
  
  If(GetGadgetState(#CB_COLOR_BLIND)=1)
    parameters = parameters + " --cb"
  Else
    parameters = parameters + " --nocb"
  EndIf
  
  parameters = parameters + " --maxfps " + Str(GetGadgetState(#SPIN_FPS))
  
  RunProgram("OpenAlchemist.exe", parameters, "")

EndProcedure

Procedure readConf()
  confFile.s = GetEnvironmentVariable("APPDATA") + "\OpenAlchemist\preferences.ini"  
  
  If OpenPreferences(confFile) = 0
    confFile = "savedata\preferences.ini"
    OpenPreferences(confFile)
  EndIf
  
  PreferenceGroup("Preferences")
  
  ; Reading OpenGL conf
  opengl.s = ReadPreferenceString("OpenGL", "True")
  If opengl = "True"
    SetGadgetState(#RDB_OPENGL, 1)
    SetGadgetState(#RDB_SDL, 0)
  Else
    SetGadgetState(#RDB_OPENGL, 0)
    SetGadgetState(#RDB_SDL, 1)
  EndIf
  
  ; Reading Framerate
  maxFPS = ReadPreferenceLong("MaxFPS", 65)
  SetGadgetText(#SPIN_FPS, Str(maxFPS))
  SetGadgetState(#SPIN_FPS, maxFPS)
  
  ; Reading ColorBlind
  colorBlind.s = ReadPreferenceString("Colorblind", "False")
  If colorBlind = "True"
    SetGadgetState(#CB_COLOR_BLIND, 1)
  Else
    SetGadgetState(#CB_COLOR_BLIND, 0)
  EndIf
  
  
  ClosePreferences()
EndProcedure




; IDE Options = PureBasic 4.20 (Windows - x86)
; CursorPosition = 75
; FirstLine = 67
; Folding = -
; EnableXP
; Executable = C:\Users\Keph\Documents\Visual Studio 2008\Projects\OpenAlchemist\Release\config.exe
; DisableDebugger