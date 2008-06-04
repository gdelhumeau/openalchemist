object Form1: TForm1
  Left = 418
  Top = 194
  BorderStyle = bsDialog
  Caption = 'OpenAlchemist Configuration'
  ClientHeight = 265
  ClientWidth = 201
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 185
    Height = 81
    Caption = 'Render : '
    TabOrder = 0
    object RadioButton1: TRadioButton
      Left = 16
      Top = 24
      Width = 113
      Height = 17
      Caption = 'SDL'
      TabOrder = 0
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 16
      Top = 48
      Width = 113
      Height = 17
      Caption = 'OpenGL'
      TabOrder = 1
      TabStop = True
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 96
    Width = 185
    Height = 65
    Caption = 'Limit framerate to : '
    TabOrder = 1
    object SpinEdit1: TSpinEdit
      Left = 16
      Top = 24
      Width = 153
      Height = 22
      MaxLength = 1
      MaxValue = 1000
      MinValue = 1
      TabOrder = 0
      Value = 60
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 168
    Width = 185
    Height = 57
    Caption = 'Options : '
    TabOrder = 2
    TabStop = True
    object CheckBox1: TCheckBox
      Left = 16
      Top = 24
      Width = 153
      Height = 17
      Caption = 'Active color blind mode'
      TabOrder = 0
    end
  end
  object Button1: TButton
    Left = 8
    Top = 232
    Width = 185
    Height = 25
    Caption = 'Run game'
    TabOrder = 3
    OnClick = Button1Click
  end
end
