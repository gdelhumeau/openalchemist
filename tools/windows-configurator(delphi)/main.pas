unit main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, IniFiles, StrUtils, ExtActns, Spin;

type
  TForm1 = class(TForm)
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    GroupBox3: TGroupBox;
    Button1: TButton;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    SpinEdit1: TSpinEdit;
    CheckBox1: TCheckBox;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Déclarations privées }
  public
    { Déclarations publiques }
  end;

var
  Form1: TForm1;
  configExecPath : String;
  configParam    : String;

implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
var
  configFile : TIniFile;
  configPath : String;
  i : Integer;
  
begin
  // Chemin de l'application + nom de l'executable
  configPath := Application.ExeName;

  // Récupérer le chemin absolu du répertoire
  i := Length(configPath);
  while i>0 do begin
    if configPath[i] = '\' then begin
      configPath := LeftStr( configPath, i );
      break;
    end;
    Dec(i);
  end;

  // Pour lancer le jeu : configurer le nom de l'executable
  configExecPath := configPath+'OpenAlchemist.exe ';
  configParam    := '';

  // Chemin relatif vers le fichier de configuration
  configPath := configPath + 'savedata\preferences.ini';

  // Ouverture du fichier de configuration
  configFile := TIniFile.Create( configPath );

  // Lecture du mode mal-voyant
  if configFile.ReadString('Preferences', 'Colorblind', 'False' ) = 'True'
    then begin configParam := configParam + '--cb ';   Checkbox1.Checked:=true;  end
    else begin configParam := configParam + '--nocb '; Checkbox1.Checked:=false; end;

  // Lecture du mode OpenGL / SDL
  if configFile.ReadString('Preferences', 'OpenGL', 'True' ) = 'True'
    then begin configParam := configParam + '--opengl '; RadioButton2.Checked := true;  end
    else begin configParam := configParam + '--sdl ';    RadioButton1.Checked := true;  end;

  // Lecture des FPS maximum
  SpinEdit1.Value := configFile.ReadInteger('Preferences', 'MaxFPS', 70 );
  configParam := configParam +'--maxfps '+inttostr(SpinEdit1.Value);

  // Fermeture du fichier de configuration
  configFile.Free;
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  configExec : TFileRun;

begin
  // Création de l'objet "fichier executable externe"
  configExec := TFileRun.Create(self);

  // Chemin du fichier
  configExec.FileName := configExecPath;

  // Paramètres de l'application
  configExec.Parameters := configParam;

  // Opération à executer
  configExec.Operation := 'open';

  // Affichage de l'executable
  configExec.ShowCmd := scShow;

  // Lancement de l'action
  configExec.Execute;

  //  Fermeture de l'application de configuration
  close;
end;

end.
