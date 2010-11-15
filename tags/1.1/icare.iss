#define qtdir "E:\Qt\2010.05"
#define builddir "C:\Users\Marc\icare-algo\Ptut-build-desktop"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{2327313D-8D3C-4264-BC25-5F63DE2AB6DC}
AppName=Icare
AppVersion=1.1
;AppVerName=Icare 1.1
AppPublisher=I.U.T. de Blagnac
AppPublisherURL=http://icare-algo.ath.cx
AppSupportURL=http://icare-algo.ath.cx
AppUpdatesURL=http://icare-algo.ath.cx
DefaultDirName={pf}\Icare
DefaultGroupName=Icare
OutputBaseFilename=Installateur
Compression=lzma/ultra
SolidCompression=yes
WizardSmallImageFile="{#builddir}\..\trunk\Interface\logo.bmp"

[Languages]
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#builddir}\Icare.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#builddir}\Icare-cli.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#builddir}\Analyse.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#builddir}\GUI.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#builddir}\Plugins\*"; DestDir: "{app}\Plugins"; Flags: recursesubdirs createallsubdirs
Source: "{#qtdir}\qt\bin\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#qtdir}\qt\bin\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#qtdir}\qt\bin\QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#qtdir}\qt\bin\QtWebKit4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#qtdir}\qt\bin\QtXmlPatterns4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#qtdir}\qt\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#qtdir}\qt\bin\mingwm10.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#qtdir}\qt\bin\phonon4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#qtdir}\qt\translations\qt_fr.qm"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Icare"; Filename: "{app}\Icare.exe"
Name: "{group}\{cm:UninstallProgram,Icare}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\Icare"; Filename: "{app}\Icare.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Icare"; Filename: "{app}\Icare.exe"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\Icare.exe"; Description: "{cm:LaunchProgram,Icare}"; Flags: nowait postinstall skipifsilent

[Registry]
Root: HKCU; SubKey: SOFTWARE\IUT Blagnac\Icare; ValueData: ""; Flags: UninsDeleteKey; 
Root: HKCU; SubKey: "SOFTWARE\IUT Blagnac"; ValueData: ""; Flags: UninsDeleteKeyIfEmpty;
