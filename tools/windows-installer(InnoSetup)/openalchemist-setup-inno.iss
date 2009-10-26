; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{C4CC94C6-FFDB-4EF0-A45E-4E4D9C375D20}
AppName=OpenAlchemist
AppVerName=OpenAlchemist 1.0 RC 1
AppVersion=1.0rc1
AppPublisher=OpenAlchemist Team
AppPublisherURL=http://www.openalchemist.com
AppSupportURL=http://www.openalchemist.com
AppUpdatesURL=http://www.openalchemist.com
DefaultDirName={pf}\OpenAlchemist
DefaultGroupName=OpenAlchemist
AllowNoIcons=yes
LicenseFile=license.txt
OutputDir=..\..\releases\
OutputBaseFilename=openalchemist-1.0-rc1-win-setup.exe
SetupIconFile=..\..\trunk\data\logo.ico
Compression=lzma
SolidCompression=yes
WizardImageFile=image.bmp
WizardSmallImageFile=small_image.bmp
UsePreviousAppDir=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\..\trunk\OpenAlchemist.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\trunk\Config.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\trunk\data\*"; DestDir: "{app}\data"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\..\trunk\skins\*.zip"; DestDir: "{app}\skins"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\..\trunk\music\*"; DestDir: "{app}\music"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\..\trunk\sounds\*"; DestDir: "{app}\sounds"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\OpenAlchemist"; Filename: "{app}\OpenAlchemist.exe"
Name: "{group}\Config"; Filename: "{app}\Config.exe"
Name: "{group}\{cm:UninstallProgram,OpenAlchemist}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\OpenAlchemist"; Filename: "{app}\OpenAlchemist.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\OpenAlchemist.exe"; Description: "{cm:LaunchProgram,OpenAlchemist}"; Flags: nowait postinstall skipifsilent

