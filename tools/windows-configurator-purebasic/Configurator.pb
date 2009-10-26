XIncludeFile "Common.pb"

Declare main()
Declare run()
Declare initComponents()
Declare readConf()

; ------------
;- Globales
; ------------
Global running = 1
Global openalchemistVersion.s = "svn"

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
        EndSelect
      Case #PB_Event_CloseWindow :
        running = 0
    EndSelect
  Wend
  
EndProcedure

Procedure initComponents()
  SetGadgetState(#RDB_OPENGL, 1)
  SetGadgetState(#RDB_OPENGL2, 0)
  SetGadgetState(#RDB_SOFTWARE, 0)

  readConf()
EndProcedure

Procedure run()
  running = 0
  parameters.s = ""
  
  If(GetGadgetState(#RDB_OPENGL)=1)
    parameters = parameters + " --opengl"
  ElseIf (GetGadgetState(#RDB_OPENGL2)=1)
    parameters = parameters + " --opengl2"
  ElseIf (GetGadgetState(#RDB_SOFTWARE)=1)
    parameters = parameters + " --software"
  EndIf
  
  
  RunProgram("OpenAlchemist.exe", parameters, "")

EndProcedure

Procedure readConf()
  confFile.s = "savedata\preferences-"+openalchemistVersion+".ini"   
  
  If OpenPreferences(confFile) = 0
    confFile = GetEnvironmentVariable("APPDATA") + "\OpenAlchemist\preferences-"+openalchemistVersion+".ini" 
    OpenPreferences(confFile)
  EndIf
  
  PreferenceGroup("Preferences")
  
  ; Reading Render Target conf
  render.s = ReadPreferenceString("Render Target", "OPENGL_1")
  If render = "OPENGL_2"
    SetGadgetState(#RDB_OPENGL, 0)
    SetGadgetState(#RDB_OPENGL2, 1)
    SetGadgetState(#RDB_SOFTWARE, 0)
  ElseIf render = "SOFTWARE"
    SetGadgetState(#RDB_OPENGL, 0)
    SetGadgetState(#RDB_OPENGL2, 0)
    SetGadgetState(#RDB_SOFTWARE, 1)
  Else
    SetGadgetState(#RDB_OPENGL, 1)
    SetGadgetState(#RDB_OPENGL2, 0)
    SetGadgetState(#RDB_SOFTWARE, 0)
  EndIf
  
  
  ClosePreferences()
EndProcedure




; IDE Options = PureBasic 4.31 (Windows - x86)
; CursorPosition = 84
; FirstLine = 60
; Folding = -
; EnableXP
; Executable = C:\Users\Keph\Documents\Visual Studio 2008\Projects\OpenAlchemist\Release\Config.exe
; DisableDebugger