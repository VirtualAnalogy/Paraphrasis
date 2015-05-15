#define MyPlugName "Paraphrasis"
#define MyPlugVersion "1.0.3"
#define MyPlugShortVersion "103"
#define MyPlugPublisher "Virtual Analogy"
#define MyPlugURL "http://www.virtualanalogy.com/"

;#define STAND_ALONE_32 ""
;#define STAND_ALONE_64 ""
#define VST2_32 "..\..\Builds\VisualStudio2013\Release\"
;#define VST2_64 ""
#define VST3_32 "..\..\Builds\VisualStudio2013\Release\"
;#define VST3_64 ""
;#define RTAS_32 ""
;#define MANUAL ""
;#define CHANGE_LOG ""
#define INSTALL_MSVC_REDISTRIBUTABLE

[Setup]
AppId={{35609664-411C-401C-91DF-AF1EE8CE868C}
AppName={#MyPlugName}
AppVersion={#MyPlugVersion}
;AppVerName={#MyPlugName} {#MyPlugVersion}
AppPublisher={#MyPlugPublisher}
AppPublisherURL={#MyPlugURL}
AppSupportURL={#MyPlugURL}
AppUpdatesURL={#MyPlugURL}
DefaultDirName={pf}\{#MyPlugPublisher}\{#MyPlugName}
DefaultGroupName={#MyPlugPublisher}\{#MyPlugName}
OutputBaseFilename={#MyPlugName}_{#MyPlugShortVersion}
OutputDir=.\
Compression=lzma
SolidCompression=yes
#if defined VST2_64 || defined VST3_64
  ArchitecturesInstallIn64BitMode=x64
#endif
LicenseFile=..\LICENSE.txt
InfoBeforeFile=..\README.txt
SetupLogging=yes
WizardImageFile=left.bmp
WizardSmallImageFile=small.bmp

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Types]
Name: "full"; Description: "Full installation"
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[Components]
#ifdef STAND_ALONE
  Name: "app"; Description: "Standalone application (.exe)"; Types: full custom;
#endif
#ifdef VST2_32
  Name: "vst2_32"; Description: "32-bit VST2 Plugin (.dll)"; Types: full custom;
#endif
#ifdef VST2_64
  Name: "vst2_64"; Description: "64-bit VST2 Plugin (.dll)"; Types: full custom; Check: Is64BitInstallMode;
#endif
#ifdef VST3_32
  Name: "vst3_32"; Description: "32-bit VST3 Plugin (.vst3)"; Types: full custom;
#endif
#ifdef VST3_64
  Name: "vst3_64"; Description: "64-bit VST3 Plugin (.vst3)"; Types: full custom; Check: Is64BitInstallMode;
#endif
#ifdef RTAS_32
  Name: "rtas_32"; Description: "32-bit RTAS Plugin (.dpm)"; Types: full custom;
#endif
#ifdef MANUAL
  Name: "manual"; Description: "User guide"; Types: full custom; Flags: fixed
#endif

[Files]
#ifdef STAND_ALONE_32
  Source: "{#STAND_ALONE_32}\{#MyPlugName}.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode; Components:app;
#endif
#ifdef STAND_ALONE_64
  Source: "{#STAND_ALONE_64}\{#MyPlugName}.exe"; DestDir: "{app}"; Check: Is64BitInstallMode; Components:app;
#endif
#ifdef VST2_32
  Source: "{#VST2_32}\{#MyPlugName}.dll"; DestDir: {code:GetVST2Dir_32}; Check: not Is64BitInstallMode; Components:vst2_32;
  Source: "{#VST2_32}\{#MyPlugName}.dll"; DestDir: {code:GetVST2Dir_32}; Check: Is64BitInstallMode; Components:vst2_32;
#endif
#ifdef VST2_64
  Source: "{#VST2_64}\{#MyPlugName}.dll"; DestDir: {code:GetVST2Dir_64}; Check: Is64BitInstallMode; Components:vst2_64;
#endif
#ifdef VST3_32
  Source: "{#VST3_32}\{#MyPlugName}.vst3"; DestDir: "{cf}\VST3\"; Check: not Is64BitInstallMode; Components:vst3_32;
  Source: "{#VST3_32}\{#MyPlugName}.vst3"; DestDir: "{cf32}\VST3\"; Check: Is64BitInstallMode; Components:vst3_32;
#endif
#ifdef VST3_64
  Source: "{#VST3_64}\{#MyPlugName}.vst3"; DestDir: "{cf64}\VST3\"; Check: Is64BitInstallMode; Components:vst3_64;
#endif
#ifdef RTAS_32
  Source: "{#RTAS_32}\{#MyPlugName}.dpm"; DestDir: "{cf32}\Digidesign\DAE\Plug-Ins\"; Components:rtas_32;
  Source: "{#RTAS_32}\{#MyPlugName}.dpm.rsr"; DestDir: "{cf32}\Digidesign\DAE\Plug-Ins\"; Components:rtas_32;
#endif

#ifdef MANUAL
  Source: "{#MANUAL}"; DestDir: "{app}"
#endif
#ifdef CHANGLE_LOG
  Source: "{#CHANGLE_LOG}"; DestDir: "{app}"
#endif
#ifdef README
  Source: "{#README}"; DestDir: "{app}"; Flags: isreadme
#endif

#ifdef INSTALL_MSVC_REDISTRIBUTABLE
  Source: "vcredist_x86.exe"; DestDir: {tmp}; Flags: deleteafterinstall
#endif 

[Icons]
#ifdef STAND_ALONE
  Name: "{group}\{#MyPlugName}"; Filename: "{app}\{#MyPlugExeName}"
  Name: "{commondesktop}\{#MyPlugName}"; Filename: "{app}\{#MyPlugExeName}"; Tasks: desktopicon
#endif
#ifdef MANUAL
  Name: "{group}\User guide"; Filename: "{app}\{#MyPlugName}_manual.pdf"
#endif
Name: "{group}\Un-install {#MyPlugName}"; Filename: "{app}\unins000.exe"


[Tasks]
#ifdef STAND_ALONE
  Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
#endif

[Run]
#ifdef STAND_ALONE
  Filename: "{app}\{#MyPlugExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyPlugName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
#endif
#ifdef INSTALL_MSVC_REDISTRIBUTABLE
  Filename: {tmp}\vcredist_x86.exe; Parameters: "/quiet /passive /install"; StatusMsg: Installing VC++ Redistributables...
#endif


[UninstallDelete]
Type: files; Name: "{app}\InstallationLogFile.log"

[Code]
var
  OkToCopyLog : Boolean;
  VST2DirPage_32: TInputDirWizardPage;
#if defined VST2_64 || defined VST3_64
  VST2DirPage_64: TInputDirWizardPage;
#endif

procedure InitializeWizard;
begin
  if IsWin64 then begin
#if defined VST2_64 || defined VST3_64
    VST2DirPage_64 := CreateInputDirPage(wpSelectDir,
    'Confirm 64-Bit VST2 Plugin Directory', '',
    'Select the folder in which setup should install the 64-bit VST2 Plugin, then click Next.',
    False, '');
    VST2DirPage_64.Add('');
    VST2DirPage_64.Values[0] := ExpandConstant('{reg:HKLM\SOFTWARE\VST,VSTPluginsPath|{pf}\Steinberg\VSTPlugins}\');
#endif
    VST2DirPage_32 := CreateInputDirPage(wpSelectDir,
      'Confirm 32-Bit VST2 Plugin Directory', '',
      'Select the folder in which setup should install the 32-bit VST2 Plugin, then click Next.',
      False, '');
    VST2DirPage_32.Add('');
    VST2DirPage_32.Values[0] := ExpandConstant('{reg:HKLM\SOFTWARE\WOW6432NODE\VST,VSTPluginsPath|{pf32}\Steinberg\VSTPlugins}\');
  end else begin
    VST2DirPage_32 := CreateInputDirPage(wpSelectDir,
      'Confirm 32-Bit VST2 Plugin Directory', '',
      'Select the folder in which setup should install the 32-bit VST2 Plugin, then click Next.',
      False, '');
    VST2DirPage_32.Add('');
    VST2DirPage_32.Values[0] := ExpandConstant('{reg:HKLM\SOFTWARE\VST,VSTPluginsPath|{pf}\Steinberg\VSTPlugins}\');
  end;
end;

function GetVST2Dir_32(Param: String): String;
begin
  Result := VST2DirPage_32.Values[0]
end;

#if defined VST2_64 || defined VST3_64
function GetVST2Dir_64(Param: String): String;
begin
  Result := VST2DirPage_64.Values[0]
end;
#endif

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssDone then
    OkToCopyLog := True;
end;

procedure DeinitializeSetup();
begin
  if OkToCopyLog then
    FileCopy (ExpandConstant ('{log}'), ExpandConstant ('{app}\InstallationLogFile.log'), FALSE);
  RestartReplace (ExpandConstant ('{log}'), '');
end;
