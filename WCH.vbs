'Web-Class-Helper 1.0.8
'This source code file is under MIT License.
'Copyright (c) 2022 Class Tools Develop Team
'Contributors: jsh-jsh ren-yc
Set WshShell = WScript.CreateObject("WScript.Shell")
If WScript.Arguments.Length = 0 Then
    Set ObjShell = CreateObject("Shell.Application")
    ObjShell.ShellExecute "wscript.exe" _
    , """" & WScript.ScriptFullName & """ RunAsAdministrator", , "runas", 1
    WScript.Quit
End if
CurPath = left(WScript.ScriptFullName, instrrev(WScript.ScriptFullName, "\"))
Set WshShell = CreateObject("WScript.Shell")
WshShell.run "cmd.exe"
WScript.sleep 50
s = "cacls """ & CurPath
s1 = StrReverse(s)
s2 = mid(s1, 2)
s = StrReverse(s2)
WshShell.sendkeys s & """ /G Everyone:F" & "{enter}"
WScript.sleep 50
WshShell.sendkeys "Y{enter}"
WshShell.sendkeys "%{F4}"