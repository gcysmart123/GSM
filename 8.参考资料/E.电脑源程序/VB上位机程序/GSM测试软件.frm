VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "GSM���Թ���"
   ClientHeight    =   7110
   ClientLeft      =   45
   ClientTop       =   420
   ClientWidth     =   11535
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7110
   ScaleWidth      =   11535
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  '��Ļ����
   Begin VB.Frame FrameSystem 
      Caption         =   "ϵͳ��Ϣ"
      Height          =   3045
      Left            =   11520
      TabIndex        =   44
      Top             =   7080
      Visible         =   0   'False
      Width           =   1065
      Begin VB.TextBox TextGSMBusiness 
         Height          =   345
         Left            =   240
         TabIndex        =   46
         Text            =   "��"
         Top             =   570
         Width           =   1185
      End
      Begin VB.CommandButton CommandGetSys 
         Caption         =   "��ȡϵͳ��Ϣ"
         Height          =   375
         Left            =   150
         TabIndex        =   45
         Top             =   2520
         Width           =   1365
      End
      Begin VB.Label LabelGSMBusiness 
         Caption         =   "GSM��Ӫ��"
         Height          =   315
         Left            =   450
         TabIndex        =   50
         Top             =   300
         Width           =   1095
      End
      Begin VB.Label LabelSignal 
         Caption         =   "�ź�ǿ��"
         Height          =   225
         Left            =   480
         TabIndex        =   49
         Top             =   1050
         Width           =   885
      End
      Begin VB.Label LabelSystime 
         Height          =   345
         Left            =   480
         TabIndex        =   48
         Top             =   2040
         Width           =   975
      End
      Begin VB.Label Label13 
         Caption         =   "ϵͳʱ��"
         Height          =   195
         Left            =   480
         TabIndex        =   47
         Top             =   1770
         Width           =   765
      End
      Begin VB.Shape ShapeS1 
         BackColor       =   &H8000000F&
         BackStyle       =   1  'Opaque
         BorderColor     =   &H8000000F&
         BorderStyle     =   0  'Transparent
         FillColor       =   &H000000FF&
         FillStyle       =   0  'Solid
         Height          =   345
         Left            =   300
         Top             =   1290
         Width           =   195
      End
      Begin VB.Shape ShapeS2 
         BackColor       =   &H8000000F&
         BackStyle       =   1  'Opaque
         BorderColor     =   &H8000000F&
         BorderStyle     =   0  'Transparent
         FillColor       =   &H000000FF&
         FillStyle       =   0  'Solid
         Height          =   345
         Left            =   480
         Top             =   1290
         Width           =   195
      End
      Begin VB.Shape ShapeS3 
         BackColor       =   &H8000000F&
         BackStyle       =   1  'Opaque
         BorderColor     =   &H8000000F&
         BorderStyle     =   0  'Transparent
         FillColor       =   &H000000FF&
         FillStyle       =   0  'Solid
         Height          =   345
         Left            =   660
         Top             =   1290
         Width           =   195
      End
      Begin VB.Shape ShapeS4 
         BackColor       =   &H8000000F&
         BackStyle       =   1  'Opaque
         BorderColor     =   &H8000000F&
         BorderStyle     =   0  'Transparent
         FillColor       =   &H000000FF&
         FillStyle       =   0  'Solid
         Height          =   345
         Left            =   840
         Top             =   1290
         Width           =   195
      End
      Begin VB.Shape ShapeS5 
         BackColor       =   &H8000000F&
         BackStyle       =   1  'Opaque
         BorderColor     =   &H8000000F&
         BorderStyle     =   0  'Transparent
         FillColor       =   &H000000FF&
         FillStyle       =   0  'Solid
         Height          =   345
         Left            =   1020
         Top             =   1290
         Width           =   195
      End
      Begin VB.Shape ShapeS6 
         BackColor       =   &H8000000F&
         BackStyle       =   1  'Opaque
         BorderColor     =   &H8000000F&
         BorderStyle     =   0  'Transparent
         FillColor       =   &H000000FF&
         FillStyle       =   0  'Solid
         Height          =   345
         Left            =   1200
         Top             =   1290
         Width           =   195
      End
   End
   Begin VB.Timer TimerMSCreceive 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   8310
      Top             =   6690
   End
   Begin MSCommLib.MSComm MSComm 
      Left            =   9000
      Top             =   6540
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.CommandButton CommandExit 
      Caption         =   "�˳�"
      Height          =   375
      Left            =   9840
      TabIndex        =   35
      Top             =   6690
      Width           =   1515
   End
   Begin VB.Frame FrameCall 
      Caption         =   "GSM����"
      Height          =   3375
      Left            =   120
      TabIndex        =   21
      Top             =   3240
      Width           =   4995
      Begin VB.CommandButton CommandNet_Information 
         Caption         =   "������Ϣ"
         Height          =   450
         Left            =   2520
         TabIndex        =   42
         Top             =   960
         Width           =   1140
      End
      Begin VB.CommandButton CommandSignal_Quality 
         Caption         =   "�ź�����"
         Height          =   450
         Left            =   1320
         TabIndex        =   41
         Top             =   960
         Width           =   1140
      End
      Begin VB.CommandButton CommandSim_Status 
         Caption         =   "SIM��״̬"
         Height          =   450
         Left            =   120
         TabIndex        =   40
         Top             =   960
         Width           =   1140
      End
      Begin VB.CommandButton CommandDevice_Init 
         Caption         =   "�豸��ʼ��"
         Height          =   450
         Left            =   3720
         TabIndex        =   39
         Top             =   240
         Width           =   1140
      End
      Begin VB.CommandButton CommandDevice_Number 
         Caption         =   "�豸���"
         Height          =   450
         Left            =   2520
         TabIndex        =   38
         Top             =   240
         Width           =   1140
      End
      Begin VB.CommandButton CommandDevice_Type 
         Caption         =   "�豸����"
         Height          =   450
         Left            =   1320
         TabIndex        =   37
         Top             =   240
         Width           =   1140
      End
      Begin VB.CommandButton CommandProduct 
         Caption         =   "��������"
         Height          =   450
         Left            =   120
         TabIndex        =   36
         Top             =   240
         Width           =   1140
      End
      Begin VB.CommandButton CommandAnswer 
         Caption         =   "�����绰"
         Height          =   450
         Left            =   3720
         TabIndex        =   26
         Top             =   2640
         Width           =   1020
      End
      Begin VB.CommandButton CommandHang 
         Caption         =   "�һ�"
         Height          =   450
         Left            =   1920
         TabIndex        =   25
         Top             =   2640
         Width           =   1140
      End
      Begin VB.CommandButton CommandCall 
         Caption         =   "���Ų���"
         Height          =   465
         Left            =   120
         TabIndex        =   24
         Top             =   2640
         Width           =   1140
      End
      Begin VB.TextBox TextCallNO 
         Height          =   435
         Left            =   1680
         TabIndex        =   22
         Text            =   "10086"
         Top             =   1800
         Width           =   1815
      End
      Begin VB.Label LabelInputNO 
         Caption         =   "���Բ���绰"
         Height          =   315
         Left            =   120
         TabIndex        =   23
         Top             =   1920
         Width           =   1215
      End
   End
   Begin VB.Frame FrameMSC 
      Caption         =   "��������"
      Height          =   6525
      Left            =   5160
      TabIndex        =   6
      Top             =   120
      Width           =   2415
      Begin VB.PictureBox Picture1 
         Height          =   2175
         Left            =   120
         Picture         =   "GSM�������.frx":0000
         ScaleHeight     =   2115
         ScaleWidth      =   2115
         TabIndex        =   43
         Top             =   3960
         Width           =   2175
      End
      Begin VB.ComboBox ComboMSCPort 
         Height          =   300
         Left            =   960
         TabIndex        =   12
         Text            =   "COM1"
         Top             =   480
         Width           =   1215
      End
      Begin VB.CommandButton CommandOpenMSC 
         Caption         =   "�򿪴���"
         Height          =   375
         Left            =   960
         TabIndex        =   11
         Top             =   2880
         Width           =   1215
      End
      Begin VB.ComboBox ComboStopbit 
         Height          =   300
         Left            =   960
         TabIndex        =   10
         Text            =   "1"
         Top             =   2400
         Width           =   1215
      End
      Begin VB.ComboBox ComboDatabits 
         Height          =   300
         Left            =   960
         TabIndex        =   9
         Text            =   "8"
         Top             =   1920
         Width           =   1215
      End
      Begin VB.ComboBox ComboParity 
         Height          =   300
         Left            =   960
         TabIndex        =   8
         Text            =   "None"
         Top             =   1440
         Width           =   1215
      End
      Begin VB.ComboBox ComboMSCBaudrate 
         Height          =   300
         Left            =   960
         TabIndex        =   7
         Text            =   "9600"
         Top             =   960
         Width           =   1215
      End
      Begin VB.Label Label7 
         Caption         =   "ֹͣλ"
         Height          =   300
         Left            =   180
         TabIndex        =   17
         Top             =   2400
         Width           =   705
      End
      Begin VB.Label Label6 
         Caption         =   "����λ"
         Height          =   180
         Left            =   180
         TabIndex        =   16
         Top             =   1920
         Width           =   795
      End
      Begin VB.Label Label5 
         Caption         =   "У��λ"
         Height          =   345
         Left            =   180
         TabIndex        =   15
         Top             =   1440
         Width           =   765
      End
      Begin VB.Label Label4 
         Caption         =   "������"
         Height          =   180
         Left            =   180
         TabIndex        =   14
         Top             =   960
         Width           =   615
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "��  ��"
         Height          =   180
         Left            =   180
         TabIndex        =   13
         Top             =   480
         Width           =   540
      End
      Begin VB.Shape ShapeMSC 
         BackColor       =   &H00000000&
         BorderColor     =   &H00000000&
         FillStyle       =   0  'Solid
         Height          =   375
         Left            =   240
         Shape           =   3  'Circle
         Top             =   2880
         Width           =   375
      End
   End
   Begin VB.Frame FrameAT 
      Caption         =   "ATָ�����"
      Height          =   6495
      Left            =   7680
      TabIndex        =   1
      Top             =   120
      Width           =   3735
      Begin VB.CommandButton Command4 
         Caption         =   "ATָ�"
         Height          =   375
         Left            =   2520
         TabIndex        =   20
         Top             =   5520
         Width           =   1095
      End
      Begin VB.CommandButton CommandMSCSend 
         Caption         =   "����"
         Height          =   375
         Left            =   120
         TabIndex        =   19
         Top             =   5520
         Width           =   1095
      End
      Begin VB.CommandButton CommandMSCClera 
         Caption         =   "���"
         Height          =   375
         Left            =   1320
         TabIndex        =   18
         Top             =   5520
         Width           =   1095
      End
      Begin VB.TextBox TextMSCSend 
         Height          =   615
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   4
         Text            =   "GSM�������.frx":1CF5
         Top             =   4680
         Width           =   3495
      End
      Begin VB.TextBox TextMSCReceive 
         Height          =   3495
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   2
         Top             =   600
         Width           =   3495
      End
      Begin VB.Label Label2 
         Caption         =   "����ָ��"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   4320
         Width           =   855
      End
      Begin VB.Label Label1 
         Caption         =   "������Ϣ"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   360
         Width           =   735
      End
   End
   Begin VB.Frame FrameSMS 
      Caption         =   "���Ų���"
      Height          =   3045
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4935
      Begin VB.CommandButton CommandMSMClear 
         Caption         =   "���"
         Height          =   345
         Left            =   3120
         TabIndex        =   34
         Top             =   2610
         Width           =   1635
      End
      Begin VB.CommandButton CommandSMSSend 
         Caption         =   "���Ͷ���"
         Height          =   345
         Left            =   1440
         TabIndex        =   33
         Top             =   2610
         Width           =   1515
      End
      Begin VB.TextBox TextSMStoNO 
         Height          =   315
         Left            =   2700
         TabIndex        =   32
         Text            =   "10086"
         Top             =   2190
         Width           =   1485
      End
      Begin VB.TextBox TextSMSSend 
         Height          =   1425
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   29
         Text            =   "GSM�������.frx":1CFA
         Top             =   600
         Width           =   4575
      End
      Begin VB.OptionButton OptionSMSChinese 
         Caption         =   "���Ķ���"
         Height          =   255
         Left            =   120
         TabIndex        =   28
         Top             =   2280
         Width           =   1065
      End
      Begin VB.OptionButton OptionSMSEnglish 
         Caption         =   "Ӣ�Ķ���"
         Height          =   255
         Left            =   120
         TabIndex        =   27
         Top             =   2640
         Width           =   1065
      End
      Begin VB.Label Label19 
         Caption         =   "������Ϣ��"
         Height          =   255
         Left            =   1680
         TabIndex        =   31
         Top             =   2250
         Width           =   945
      End
      Begin VB.Label Label18 
         Caption         =   "���Ͷ�������"
         Height          =   285
         Left            =   150
         TabIndex        =   30
         Top             =   360
         Width           =   1575
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim SMSFlag  As Boolean 'TrueΪӢ�Ķ��� FalseΪ���Ķ���
Dim SMSNumber As String     '���ź���
Dim SMSNumberHEX As String  '���ź���16����
Dim SMSNumberLen As String  '���ź��볤��
Dim SMSContent As String    '��������
Dim SMSContentHEX As String '��������16����
Dim SMSContentLen As String '���ų���
Dim SMSCodeLen As String    '�����ܳ���

Function SMSNumToHex(Num As String)
    Dim NumS, Num1, Num2, NumLeft, NumRight As String
    Dim NumLen As Integer
    Dim i As Integer
    NumLen = Len(Num)
    For i = 1 To NumLen
        If (i Mod 2 = 0) Then
            Num1 = Mid(Num, i - 1, 2)
            NumLeft = Left(Num1, 1)
            NumRight = Right(Num1, 1)
            Num2 = NumRight & NumLeft
            NumS = NumS & Num2
        End If
    Next i
    SMSNumToHex = NumS & "F" & Right(Num, 1)
End Function

Function SMSChinese(Text As String)
    Dim Text1, Text2, Text3, TextS As String
    Dim TextLen As Integer
    Dim TextHex As String
    Dim i As Integer
    
    TextLen = Len(Text)
    For i = 1 To TextLen
      Text1 = Mid(Text, i, 1) '��ȡһ���ַ�
      Text2 = AscW(Text1) '�������
      Text3 = Hex(Text2) '���16����
      If Text2 < 128 And Text2 > 0 Then
        Text3 = "00" & Text3
      Else
      End If
      TextS = TextS & Text3
    Next i
    SMSChinese = TextS
End Function
Function SMSChLen(Text As String)
    Dim TextLen, CodeLen As Integer
    Dim TextLenStr As String
    
    TextLen = Len(Text) * 2
    CodeLen = 15 + TextLen
    If TextLen < 15 Then '����Ҫ�����ı��ĳ���
        TextLenStr = "0" + CStr(Hex(TextLen))
    Else
        TextLenStr = CStr(Hex(TextLen))
    End If
    SMSContentLen = TextLenStr
    SMSCodeLen = CStr(CodeLen)
End Function


Sub MSCportsetting()
    Dim i As Integer
    For i = 1 To 16
        ComboMSCPort.AddItem "COM" & Trim$(Str$(i))
    Next i
    
    ComboMSCBaudrate.AddItem "300"
    ComboMSCBaudrate.AddItem "600"
    ComboMSCBaudrate.AddItem "1200"
    ComboMSCBaudrate.AddItem "2400"
    ComboMSCBaudrate.AddItem "4800"
    ComboMSCBaudrate.AddItem "9600"
    ComboMSCBaudrate.AddItem "19200"
    ComboMSCBaudrate.AddItem "38400"
    ComboMSCBaudrate.AddItem "43000"
    ComboMSCBaudrate.AddItem "56000"
    ComboMSCBaudrate.AddItem "57600"
    ComboMSCBaudrate.AddItem "115200"
    ' ������ż��������
    ComboParity.AddItem "None"
    ComboParity.AddItem "Even"
    ComboParity.AddItem "Odd"
    ' ��������λ����
    ComboDatabits.AddItem "6"
    ComboDatabits.AddItem "7"
    ComboDatabits.AddItem "8"
    ' ����ֹͣλ����
    ComboStopbit.AddItem "1"
    ComboStopbit.AddItem "2"
End Sub


Private Sub Command1_Click()

End Sub

Private Sub Command2_Click()

End Sub

Private Sub ComboMSCPort_Change()

End Sub

Private Sub CommandAnswer_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "ata" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandCall_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "atd" & TextCallNO.Text & ";" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandDevice_Init_Click()
  If MSComm.PortOpen = True Then
        MSComm.Output = "ati" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandDevice_Number_Click()
  If MSComm.PortOpen = True Then
        MSComm.Output = "at+cgsn" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandDevice_Type_Click()
  If MSComm.PortOpen = True Then
        MSComm.Output = "at+cgmm" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandExit_Click()
    If (MSComm.PortOpen = True) Then MSComm.PortOpen = False
    End
End Sub

Private Sub CommandGetSys_Click() '��ȡϵͳ��Ϣ
    Dim GetString As String
    Dim SignalTemp As String
    Dim FlagMobile As Integer
    Dim FlagUnite As Integer
    Dim STBit As Integer
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+cops?" & vbCr '��ȡ��Ӫ������
        Sleep (500)
        GetString = MSComm.Input
        TextMSCReceive.Text = TextMSCReceive.Text + GetString
        FlagMobile = InStr(GetString, "CHINA MOBILE")
        FlagUnite = InStr(GetString, "CHINA UNITE")
        If FlagMobile > 0 Then TextGSMBusiness.Text = "�й��ƶ�ͨ��"
        If FlagUnite > 0 Then TextGSMBusiness.Text = "�й���ͨͨ��"
        MSComm.Output = "at+csq" & vbCr '��ȡ�ź�ǿ��
        Sleep (500)
        SignalTemp = MSComm.Input
        TextMSCReceive.Text = TextMSCReceive.Text + SignalTemp
        STBit = InStr(SignalTemp, " ")
        SignalTemp = Mid(SignalTemp, STBit, 3)
        Select Case Val(SignalTemp)
            Case 41 To 100
                MsgBox ("û���ź�,���������Ƿ�����")
                ShapeS1.FillColor = &HFF&
                ShapeS2.FillColor = &HFF&
                ShapeS3.FillColor = &HFF&
                ShapeS4.FillColor = &HFF&
                ShapeS5.FillColor = &HFF&
                ShapeS6.FillColor = &HFF&
            Case 26 To 40
                ShapeS1.FillColor = &HC000&
                ShapeS2.FillColor = &HC000&
                ShapeS3.FillColor = &HC000&
                ShapeS4.FillColor = &HC000&
                ShapeS5.FillColor = &HC000&
                ShapeS6.FillColor = &HC000&
            Case 21 To 25
                ShapeS1.FillColor = &HC000&
                ShapeS2.FillColor = &HC000&
                ShapeS3.FillColor = &HC000&
                ShapeS4.FillColor = &HC000&
                ShapeS5.FillColor = &HC000&
                ShapeS6.FillColor = &HFF&
            Case 16 To 20
                ShapeS1.FillColor = &HC000&
                ShapeS2.FillColor = &HC000&
                ShapeS3.FillColor = &HC000&
                ShapeS4.FillColor = &HC000&
                ShapeS5.FillColor = &HFF&
                ShapeS6.FillColor = &HFF&
            Case 11 To 15
                ShapeS1.FillColor = &HC000&
                ShapeS2.FillColor = &HC000&
                ShapeS3.FillColor = &HC000&
                ShapeS4.FillColor = &HFF&
                ShapeS5.FillColor = &HFF&
                ShapeS6.FillColor = &HFF&
            Case 6 To 10
                ShapeS1.FillColor = &HC000&
                ShapeS2.FillColor = &HC000&
                ShapeS3.FillColor = &HFF&
                ShapeS4.FillColor = &HFF&
                ShapeS5.FillColor = &HFF&
                ShapeS6.FillColor = &HFF&
            Case 1 To 5
                ShapeS1.FillColor = &HC000&
                ShapeS2.FillColor = &HFF&
                ShapeS3.FillColor = &HFF&
                ShapeS4.FillColor = &HFF&
                ShapeS5.FillColor = &HFF&
                ShapeS6.FillColor = &HFF&
        End Select
    Else
        MsgBox ("���ȴ򿪴���")
    End If
    
End Sub

Private Sub CommandGPRSClear_Click()
    TextGPRSSend.Text = ""
End Sub

Private Sub CommandGPRSLink_Click()
    If MSComm.PortOpen = True Then
        If CommandGPRSLink.Caption = "����GPRS" Then
            CommandGPRSLink.Caption = "�Ͽ�GPRS"
            MSComm.Output = "at+clport=" & Chr$(34) & "tcp" & Chr$(34) & "," & Chr$(34) & "2022" & Chr$(34) & vbCr
            Sleep (1000)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
            MSComm.Output = "at+cipstart=" & Chr$(34) & "tcp" & Chr$(34) & "," & Chr$(34) & TextGPRSIP & Chr$(34) & "," & Chr$(34) & TextGPRSPort & Chr$(34) & vbCr
            Sleep (1000)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
            
        Else: CommandGPRSLink.Caption = "����GPRS"
            MSComm.Output = "at+cipclose" & vbCr
            Sleep (100)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
            MSComm.Output = "at+cipshut" & vbCr
            Sleep (100)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
        End If
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandGPRSSend_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+cipsend" & vbCr
        Sleep (100)
        TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
        MSComm.Output = TextGPRSSend.Text & Chr$(26)
        Sleep (100)
        TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandGPRSShut_Click()
    If MSComm.PortOpen = True Then
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandHang_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "ath" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandKey1_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=1" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKey2_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=2" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKey3_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=3" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKey4_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=4" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKey5_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=5" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKey6_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=6" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKey7_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=7" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKey8_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=8" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKey9_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=9" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKey0_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=0" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKeyxing_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=*" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub
Private Sub CommandKeyjing_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+vts=#" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandMSCClera_Click()
    TextMSCReceive.Text = ""
    TextMSCSend.Text = ""
End Sub

Private Sub CommandMSCSend_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = Trim(TextMSCSend.Text)
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandMSMClear_Click()
    TextSMSSend.Text = ""
    TextSMStoNO.Text = ""
End Sub

Private Sub CommandNet_Information_Click()
  If MSComm.PortOpen = True Then
        MSComm.Output = "at+cops?" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandOpenMSC_Click()
    If CommandOpenMSC.Caption = "�򿪴���" Then
        CommandOpenMSC.Caption = "�رմ���"
        ShapeMSC.BackColor = &H8000&
        ShapeMSC.FillColor = &H8000&
        ComboMSCPort.Enabled = False
        ComboDatabits.Enabled = False
        ComboMSCBaudrate.Enabled = False
        ComboParity.Enabled = False
        ComboStopbit.Enabled = False
        MSComm.CommPort = Right(ComboMSCPort.Text, 1)
        MSComm.Settings = Trim$(ComboMSCBaudrate.Text) & "," & Left$(ComboParity.Text, 1) & "," & Trim$(ComboDatabits.Text) & "," & Trim$(ComboStopbit.Text)
        MSComm.InputMode = 0
        MSComm.PortOpen = True
        TimerMSCreceive.Enabled = True
    Else
        CommandOpenMSC.Caption = "�򿪴���"
        ShapeMSC.BackColor = &HFF&
        ShapeMSC.FillColor = &HFF&
        ComboMSCPort.Enabled = True
        ComboDatabits.Enabled = True
        ComboMSCBaudrate.Enabled = True
        ComboParity.Enabled = True
        ComboStopbit.Enabled = True
        MSComm.PortOpen = False
    End If
End Sub

Private Sub CommandSMSRead_Click()
    If MSComm.PortOpen = True Then
        If SMSFlag = True Then '��ȡӢ�Ķ���
            MSComm.Output = "at+cmgf=1" & vbCr
            Sleep (100)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
            MSComm.Output = "at+cmgr=" & TextSMSnumber.Text & vbCr
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
            'Call SMSEnglish
        Else '��ȡ���Ķ���
            MSComm.Output = "at+cmgf=0" & vbCr
            Sleep (100)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
            MSComm.Output = "at+cmgr=" & TextSMSnumber.Text & vbCr
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
            'Call SMSChinese
        End If
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandProduct_Click()
    If MSComm.PortOpen = True Then
        MSComm.Output = "at+cgmi" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandSignal_Quality_Click()
 If MSComm.PortOpen = True Then
        MSComm.Output = "AT+CSQ;+CREG?" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandSim_Status_Click()
 If MSComm.PortOpen = True Then
        MSComm.Output = "at+cpin?" & vbCr
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub CommandSMSSend_Click()
    If MSComm.PortOpen = True Then
        If SMSFlag = True Then 'Ӣ�Ķ���
            MSComm.Output = "at+cmgf=1" & vbCr
            Sleep (100)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
            MSComm.Output = "at+cmgs=" & Chr$(34) & TextSMStoNO.Text & Chr$(34) & vbCr
            Sleep (100)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
            MSComm.Output = TextSMSSend.Text & Chr$(26)
            Sleep (100)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
        Else '���Ķ���
            SMSNumberHEX = SMSNumToHex(TextSMStoNO.Text)
            Call SMSChLen(TextSMSSend.Text)
            SMSContentHEX = SMSChinese(TextSMSSend.Text)
            MSComm.Output = "at+cmgf=0" & vbCr
            Sleep (100)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
           
            MSComm.Output = "at+cmgs=" & SMSCodeLen & vbCr
            Sleep (100)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
            
            MSComm.Output = "001100" & "0D" & "9168" & SMSNumberHEX & "0008A0" & SMSContentLen & SMSContentHEX & Chr$(26)
            '                 ǰ��   | Ŀ�ĺ��볤�� |  ����  | Ŀ���ֻ����� |8λ��ʱ�� |    ���ų���   |   ��������    |��������
            Sleep (100)
            TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
        End If
    Else
        MsgBox ("���ȴ򿪴���")
    End If
End Sub

Private Sub Form_Load()
    Call MSCportsetting
    OptionSMSEnglish.Value = True
    LabelSystime.Caption = Format(Now)
    SMSFlag = True
End Sub



Private Sub OptionSMSChinese_Click()
    OptionSMSChinese.Value = True
    SMSFlag = False
End Sub

Private Sub OptionSMSEnglish_Click()
    OptionSMSEnglish.Value = True
    SMSFlag = True
End Sub

Private Sub TextCallNO_Change()

End Sub

Private Sub TextSMSSend_Change()

End Sub


Private Sub TimerMSCReceive_Timer()
    If MSComm.InBufferCount > 0 Then
        TextMSCReceive.Text = TextMSCReceive.Text + MSComm.Input
    End If
    TextMSCReceive.SelStart = Len(TextMSCReceive.Text)
End Sub

Private Sub TimerSystem_Timer()
    Dim SysTime As String
    SysTime = Format(Now)
    LabelSystime.Caption = SysTime
End Sub
